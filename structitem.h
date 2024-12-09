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

// Класс для сбора данных с контролера. С помощью рефлексии от boost + QVariant
// можно использовать любую 'struct' и менять многие параметры в рантайме
class StructItem : public QObject
{
    Q_OBJECT
    template<typename Struct>
    friend class StructItemBuilder;
public:
    using Validator = std::function<bool(QVariant)>;
    using Stringer = std::function<QString(QVariant)>;
    using Iconizer = std::function<QIcon(QVariant)>;
private:
    // Приватные поля:
    Validator defaultValidator = [](QVariant field){
        return field.isValid();
        };
    Validator defaultIntValidator = [](QVariant field){
        return field.toInt() >= 0;
        };
    Validator defaultQStringValidator = [](QVariant field){
        return !field.toString().isNull();
        };
    Validator defaultQVector3DValidator = [](QVariant field){
        QVector3D vec = field.value<QVector3D>();
        return vec.x() >= 0 && vec.y() >= 0 && vec.z() >= 0;
        };

    Stringer defaultStringer = [](QVariant field){
        return field.toString();
        };
    Stringer defaultFloatStringer = [](QVariant field){
        return QString::number(field.toDouble(), 'f', 7);
        };
    Stringer defaultDoubleStringer = [](QVariant field){
        return QString::number(field.toDouble(), 'f', 15);
        };
    Stringer defaultQVector3DStringer = [](QVariant field){
        QVector3D vec = field.value<QVector3D>();
        QString ret = QString("%0, %1, %2").arg(vec.x()).arg(vec.y()).arg(vec.z());
        return ret;
        };

    Iconizer defaultIconizer = [](QVariant field){
        return QIcon();
        };
    Iconizer defaultQIconIconizer = [](QVariant field){
        return field.value<QIcon>();
        };

    QMap<QString, void*> container_names{
        {"validators", &validators},
        {"stringers", &stringers},
        {"iconizers", &iconizers}
    };

    // Поля не проверяются соответствию режиму ввода FillMode. Это задача
    // UI класса. eval_method исключительно в роли поля способ расчёта.
    int struct_size;
    QVector<QVariant> fields;
    QMap<QString, int> field_names;  // Для удобства сэтапа полей,
    QVector<QVariant> defaults{struct_size, QVariant()};
    QVector<Validator> validators{struct_size, defaultValidator};
    QVector<Stringer> stringers{struct_size, defaultStringer};
    QVector<Iconizer> iconizers{struct_size, defaultIconizer};

    // Методы валидации:
    bool isValidIndex(int idx);
    bool isValidField(int idx, QVariant field);
    // Конструктор:
    explicit StructItem(int struct_size_,
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

    bool isExistingContainer(QString container_name, const std::type_info& return_type);

    bool setDefaults(QVector<QVariant> defaults_);

    bool setDefault(QString field_name, QVariant default_);

signals:
    void changed(int idx);

private:
    template<typename T>
    using Func = std::function<T(QVariant)>;

    template<typename T>
    using Funcs = QVector<Func<T>>;

public:
    // Шаблонные сэттеры:
    template<typename T>
    bool setFunctions(QString container_name, Funcs<T> functions){
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
            for(size_t i = 0; i < struct_size; ++i){
                emit changed(i);
            }
            success = true;
        }
        return success;
    }

    template<typename T>
    bool setFunction(QString container_name, QString field_name, Func<T> func)
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
            auto functions = static_cast<Funcs<T>*>(container);
            (*functions)[field_idx] = func;
            emit changed(field_idx);
            success = true;
        }
        return success;
    }
};




