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
#include <QVector>

class PartItem : public QObject
{
    Q_OBJECT
    template<typename Struct>
    friend class PartItemBuilder;
public:
    using Validator = std::function<bool(QVariant)>;
    using Stringer = std::function<QString(QVariant)>;
    using Iconizer = std::function<QIcon(QVariant)>;
private:
    // Приватные поля:
    // Поля не проверяются соответствию режиму ввода FillMode. Это задача
    // UI класса. eval_method исключительно в роли поля способ расчёта.


    Validator defaultValidator = [&](QVariant field){
        return field.isValid();
        };
    Validator defaultIntValidator = [&](QVariant field){
        return field.toInt() >= 0;
        };
    Validator defaultQStringValidator = [&](QVariant field){
        return !field.toString().isNull();
        };
    Validator defaultQVector3DValidator = [&](QVariant field){
        QVector3D vec = field.value<QVector3D>();
        return vec.x() >= 0 && vec.y() >= 0 && vec.z() >= 0;
        };

    Stringer defaultStringer = [&](QVariant field){
        return field.toString();
        };
    Stringer defaultQVector3DStringer = [&](QVariant field){
        QVector3D vec = field.value<QVector3D>();
        QString ret = QString("%0, %1, %2").arg(vec.x()).arg(vec.y()).arg(vec.z());
        return ret;
        };

    Iconizer defaultIconizer = [&](QVariant field){
        return QIcon();
        };
    Iconizer defaultQIconIconizer = [&](QVariant field){
        return field.value<QIcon>();
        };

    QMap<QString, void*> container_names{
        {"validators", &validators},
        {"stringers", &stringers},
        {"iconizers", &iconizers}
    };

    int struct_size;
    QVector<QVariant> fields;
    QMap<QString, int> field_names;  // Для удобства сэтапа полей,
    QVector<QVariant> defaults{struct_size, QVariant()};
    QVector<Validator> validators{struct_size, defaultValidator};
    QVector<Stringer> stringers{struct_size, defaultStringer};
    QVector<Iconizer> iconizers{struct_size, defaultIconizer};
    // Возможна реализация через std::function от шаблона функции

    // Методы валидации:
    bool isValidIndex(int idx);
    bool isValidField(int idx, QVariant field);
    // Конструктор:
    explicit PartItem(int struct_size_,
                      QVector<QVariant> fields_,
                      QMap<QString, int> field_names_,
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
    void fillDefaults();

    bool isExistingContainer(QString container_name, const std::type_info& return_type){
        bool is_error =  container_name == "validators" &&
                return_type != typeid(bool) ||
                container_name == "stringers" &&
                return_type != typeid(QString) ||
                container_name == "iconizers" &&
                return_type != typeid(QIcon);
        return !is_error;
    }

    // Сэттеры:
    template<typename T, typename Funcs = QVector<std::function<T(QVariant)>>>
    bool setFunctions(QString container_name, Funcs functions){
        bool success = false;
        void* container = container_names.value(container_name, nullptr);
        if (!container){
            qCritical() << "Wrong container name";
        }
        else if(!isExistingContainer(container_name, typeid(T)))
        {
            qCritical() << "Wrong functions type";
        }
        else if (functions.size() != struct_size){
            qCritical() << "Argument of wrong size";
        }
        else {
            *container = functions;
            success = true;
        }
        return success;
    }

    template<typename T, typename Func = std::function<T(QVariant)>, typename Funcs = QVector<Func>>
    bool setFunction(QString container_name, QString field_name, Func func)
    {
        bool success = false;
        void* container = container_names.value(container_name, nullptr);
        int field_idx = field_names.value(field_name, -1);
        if(!container){
            qCritical() << "Wrong container name";
        }
        else if (field_idx == -1){
            qCritical() << "Wrong field name";
        }
        else if(!isExistingContainer(container_name, typeid(T)))
        {
            qCritical() << "Wrong func type";
        }
        else{
            auto vec = static_cast<Funcs*>(container);
            (*vec)[field_idx] = func;
            success = true;
        }
        return success;
    }


    bool setDefaults(QVector<QVariant> defaults_);


    bool setDefault(QString field_name, QVariant default_);


signals:
    void changed(int idx);
};


template<typename Struct/* = std::enable_if_t<std::is_class_v<Struct>>*/>
class PartItemBuilder
{
private:
    QMap<QString, int> field_names{struct_size};  // Для удобства сэтапа полей,
    // не является полем PartItem
    QVector<QVariant> fields{struct_size, QVariant()};
    static constexpr int struct_size{static_cast<int>(boost::pfr::tuple_size_v<Struct>)};
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
    explicit PartItemBuilder(const Struct& structure_ = {}, QObject* parent_ = nullptr) :
        fields(getFields(structure_)),
        field_names(getNames(structure_)),
        parent(parent_)
    {

    }

    // Основной метод:
    PartItem build() const{
        return PartItem(
            struct_size,
            fields,
            field_names,
            parent
        );
    }

    PartItem* buildDynamic() const{
        return new PartItem(
            struct_size,
            fields,
            field_names,
            parent
        );
    }

};

