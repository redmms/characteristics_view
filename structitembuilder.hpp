#pragma once
#include "structitem.h"
#include <type_traits>

// Паттерн билдер, который упрощает инициализацию объектов StructItem, а
// также избавляет StructItem от шаблонных параметров
template<class Struct>
class StructItemBuilder
{
private:
    QMap<QString, int> field_names{struct_size};
    QVector<QVariant> fields{struct_size, QVariant()};
    static constexpr int struct_size{
        static_cast<int>(boost::pfr::tuple_size_v<Struct>)
    };
    QObject* parent = nullptr;

    QVector<QVariant> getFields(const Struct& structure) {
        QVector<QVariant> fields(struct_size);
        boost::pfr::for_each_field(
            structure,
            [&](const auto& field, size_t idx){
                fields[idx] = field;
            }
        );
        return fields;
    }

    QMap<QString, int> getNames(const Struct& structure){
        QMap<QString, int> field_names;
        int i = 0;
        boost::pfr::for_each_field_with_name(
            structure,
            [&](std::string_view name, const auto& field){
                QString key = QString::fromStdString(std::string(name));
                field_names[key] = i;
                ++i;
            }
        );
        return field_names;
    }

public:
    explicit StructItemBuilder(const Struct& structure_ = {},
                               QObject* parent_ = nullptr) :
        fields(getFields(structure_)),
        field_names(getNames(structure_)),
        parent(parent_)
    {}

    // Основной метод:
    StructItem build() const{
        return StructItem(
            struct_size,
            fields,
            field_names,
            parent
        );
    }

    StructItem* buildDynamic() const{
        return new StructItem(
            struct_size,
            fields,
            field_names,
            parent
        );
    }

};
