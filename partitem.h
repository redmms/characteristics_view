#pragma once
#include "modenum.h"
#include "stylenum.h"
#include <QScopedPointer>
#include <QVector3D>
#include <QMap>
#include <QIcon>
#include <functional>
#include <QVariant>
#include <QObject>
#include <QDebug>
#include <type_traits>
#include <boost/pfr.hpp>
#include <QMetaType>

class PartItem : public QObject
{
    Q_OBJECT
    template<typename Struct>
    friend class PartItemBuilder;
private:
    // Приватные поля:
    // Поля не проверяются соответствию режиму ввода FillMode. Это задача
    // UI класса. eval_method исключительно в роли поля способ расчёта.
    int struct_size;
    QVector<QVariant> fields;
    QVector<QVariant> defaults;
    QVector<std::function<bool(QVariant)>> validators;
    QVector<std::function<QString(QVariant)>> stringifiers;
    QVector<std::function<QIcon(QVariant)>> iconizers;
    // Возможна реализация через std::function от шаблона функции
    // Методы валидации:
    bool isValidIndex(int idx);
    bool isValidField(int idx, QVariant field);
    // Конструктор:
    explicit PartItem(int struct_size_,
                      QVector<QVariant> fields_,
                      QVector<QVariant> defaults_,
                      QVector<std::function<bool(QVariant)>> validators_,
                      QVector<std::function<QString(QVariant)>> stringifiers_,
                      QVector<std::function<QIcon(QVariant)>> iconizers_,
                      QObject* parent = nullptr);

public:
    // Методы валидации:
    bool isValid(int idx);
    // Геттеры:
    QVariant Get(int idx);
    // Методы преобразования в строку для каждого поля, даже если оно уже
    // строка. Сделано для удобства вызова из помощников модели.
    QString getString(int idx);
    // Методы получения иконок для Qt::DecorationRole:
    QIcon getIcon(int idx);
    QVariant::Type getType(int idx);
    int getStructureSize();
    // Сэттеры со встроенной валидацией:
    bool Set(int idx, QVariant value);
    // Сэттер для сброса значений в исходные,
    // значения по умолчанию считаются невалидными
    void setDefaults();

signals:
    void changed(int idx);
};

template<typename Struct = std::enable_if_t<std::is_class_v<Struct>>>
class PartItemBuilder
{
private:
    QMap<QString, int> field_names{struct_size};  // Для удобства сэтапа полей,
    // не является полем PartItem
    std::function<bool(QVariant)> defaultValidator = [&](QVariant field){
        return field.isValid();
        };
    std::function<bool(QVariant)> defaultIntValidator = [&](QVariant field){
        return field.toInt() >= 0;
        };
    std::function<bool(QVariant)> defaultQStringValidator = [&](QVariant field){
        return !field.toString().isNull();
        };
    std::function<bool(QVariant)> defaultQVector3DValidator = [&](QVariant field){
        QVector3D vec = field.value<QVector3D>();
        return vec.x() >= 0 && vec.y() >= 0 && vec.z() >= 0;
        };

    std::function<QString(QVariant)> defaultStringifier = [&](QVariant field){
        return field.toString();
        };
//    std::function<QString(QVariant)> defaultQVector3DStringifier = [&](QVariant field){
//        QVector3D vec = qvariant_cast(field);
//        return field.toString();
//        };

    std::function<QIcon(QVariant)> defaultIconizer = [&](QVariant field){
        return QIcon();
        };
    std::function<QIcon(QVariant)> defaultQIconIconizer = [&](QVariant field){
        return field.value<QIcon>();
        };

    static constexpr int struct_size{static_cast<int>(boost::pfr::tuple_size_v<Struct>)};
    QVector<QVariant> fields{struct_size, QVariant()};
    QVector<QVariant> defaults{struct_size, QVariant()};
    QVector<std::function<bool(QVariant)>> validators{struct_size, defaultValidator};
    QVector<std::function<QString(QVariant)>> stringifiers{struct_size, defaultStringifier};
    QVector<std::function<QIcon(QVariant)>> iconizers{struct_size, defaultIconizer};
    QObject* parent = nullptr;

    QVector<QVariant> getFields(const Struct& s) {
        QVector<QVariant> fields(struct_size);
        boost::pfr::for_each_field(s, [&](const auto& field, size_t idx) {
            fields[idx] = field;
        });
        return fields;
    }

    QMap<QString, int> getNames(const Struct& s){
        QMap<QString, int> field_names;
        int i = 0;
        boost::pfr::for_each_field_with_name(s, [&](std::string_view name, const auto& field) {
            field_names[QString::fromStdString(std::string(name))] = i;  // TODO
            ++i;
        });
        return field_names;
    }

public:
    explicit PartItemBuilder(const Struct& structure_ = {}) :
        fields(getFields(structure_)),
        field_names(getNames(structure_))
    {
        for (int i = 0; i < struct_size; ++i){
            switch(static_cast<QMetaType::Type>(fields[i].type())){
            case QMetaType::QString:
                validators[i] = defaultQStringValidator;
                stringifiers[i] = defaultStringifier;
                iconizers[i] = defaultIconizer;
                break;
            case QMetaType::Int:
            case QMetaType::Float:
                validators[i] = defaultIntValidator;
                stringifiers[i] = defaultStringifier;
                iconizers[i] = defaultIconizer;
                break;
            case QMetaType::QIcon:
                validators[i] = defaultValidator;
                stringifiers[i] = defaultStringifier;
                iconizers[i] = defaultQIconIconizer;
                break;
            case QMetaType::QVector3D:
                validators[i] = defaultQVector3DValidator;
                stringifiers[i] = defaultStringifier;  // TODO
                iconizers[i] = defaultQIconIconizer;
                break;
            }
        }
    }

    // Сэттеры:
    PartItemBuilder& setDefaults(QVector<QVariant> defaults_){
        if (defaults_.size() == struct_size){
            for(size_t i = 0; i < struct_size; ++i){
                if (fields[i].type() == defaults_[i].type()){
                    defaults[i] = defaults_[i];
                }
                else {
                    QString message = QString(
                        "Wrong arguments. "
                        "Inner QVariant types should be the same. "
                        "Field QVariant::type: "
                        "%0"
                        "Given default QVariant::type: "
                        "%1"
                    )
                    .arg((fields[i].type()))
                    .arg((defaults_[i].type()));
                    qCritical() << message;
                }
            }
        }
        else{
            qCritical() << "Arguments of wrong size";
        }
        return *this;
    }

    PartItemBuilder& setDefault(QString field_name, QVariant default_){
        int idx = field_names.value(field_name, -1);
        if (idx != -1){
            defaults[idx] = default_;
        }
        else{
            qCritical() << "Wrong field name";
        }
        return *this;
    }

    PartItemBuilder& setValidators(QVector<std::function<bool(QVariant)>> validators_){
        if (validators_.size() == struct_size){
            validators = validators_;
        }
        else {
            qCritical() << "Arguments of wrong size";
        }
        return *this;
    }

    PartItemBuilder& setValidator(QString field_name, std::function<bool(QVariant)> validator){
        int idx = field_names.value(field_name, -1);
        if (idx != -1){
            validators[idx] = validator;
        }
        else{
            qCritical() << "Wrong field name";
        }
        return *this;
    }

    PartItemBuilder& setStringifiers(QVector<std::function<QString(QVariant)>> stringifiers_){
        if (stringifiers_.size() == struct_size){
            stringifiers = stringifiers_;
        }
        else{
            qCritical() << "Arguments of wrong size";
        }
        return *this;
    }

    PartItemBuilder& setStringifier(QString field_name, std::function<QString(QVariant)> stringifier){
        int idx = field_names.value(field_name, -1);
        if (idx != -1){
            stringifiers[idx] = stringifier;
        }
        else{
            qCritical() << "Wrong field name";
        }
        return *this;
    }

    PartItemBuilder& setIconizers(QVector<std::function<QIcon(QVariant)>> iconizers_){
        if (iconizers_.size() == struct_size){
            iconizers = iconizers_;
        }
        else{
            qCritical() << "Arguments of wrong size";
        }
        return *this;
    }

    PartItemBuilder& setIconizer(QString field_name, std::function<QIcon(QVariant)> iconizer){
        int idx = field_names.value(field_name, -1);
        if (idx != -1){
            iconizers[idx] = iconizer;
        }
        else{
            qCritical() << "Wrong field name";
        }
        return *this;
    }

    PartItemBuilder& setParent(QObject* parent_){
        parent = parent_;
        return *this;
    }

    // Основной метод:
    PartItem build() const{
        return PartItem(
            struct_size,
            fields,
            defaults,
            validators,
            stringifiers,
            iconizers,
            parent
        );
    }

    PartItem* buildDynamic() const{
        return new PartItem(
            struct_size,
            fields,
            defaults,
            validators,
            stringifiers,
            iconizers,
            parent
        );
    }

};

