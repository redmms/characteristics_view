#include "partitem.h"

bool PartItem::isValidIndex(int idx){
    return idx >= 0 && idx < struct_size;
}

bool PartItem::isValidField(int idx, QVariant field){
    bool ret = false;
    if (isValidIndex(idx)){
        ret = validators[idx](field);
    }
    return ret;
}

PartItem::PartItem(int struct_size_, QVector<QVariant> fields_, QVector<QVariant> defaults_, QVector<std::function<bool (QVariant)> > validators_, QVector<std::function<QString (QVariant)> > stringifiers_, QVector<std::function<QIcon (QVariant)> > iconizers_, QObject *parent) :
    QObject(parent),
    struct_size(struct_size_),
    fields(fields_),
    defaults(defaults_),
    validators(validators_),
    stringifiers(stringifiers_),
    iconizers(iconizers_)
{}

bool PartItem::isValid(int idx){
    auto ret = false;
    if (isValidIndex(idx)){
        ret = isValidField(idx, fields[idx]);
    }
    return ret;
}

QVariant PartItem::Get(int idx){
    QVariant ret = {};
    if (isValidIndex(idx)){
        ret = fields[idx];
    }
    return ret;
}

QString PartItem::getString(int idx){
    QString ret = {};
    if (isValidIndex(idx) && isValid(idx)){
        // Если невалидное поле - возможно, стоит значение по умолчанию, оставляем ячейку
        // пустой.
        // Возможна реализация другого способа отображения невалидных значений.
        // Для исходного ТЗ определение способа отображения невалидных значений
        // с помощью параметра не требовалось.
        ret = stringifiers[idx](fields[idx]);
    }
    return ret;
}

QIcon PartItem::getIcon(int idx){
    QIcon ret = {};
    if (isValidIndex(idx)){
        ret = iconizers[idx](fields[idx]);
    }
    return ret;
}

bool PartItem::Set(int idx, QVariant value){
    bool success = false;
    if (isValidIndex(idx) &&
        isValidField(idx, value) &&
        value.type() == fields[idx].type())
    {
        fields[idx] = value;
        emit changed(idx);
        success = true;
    }
    return success;
}

void PartItem::setDefaults(){
    fields = defaults;  // TODO: добавить проверку в билдере, что типы их и размер совпадают внутри
}

int PartItem::getStructureSize(){
    return struct_size;
}

QVariant::Type PartItem::getType(int idx){
    QVariant::Type ret = {};
    if (isValidIndex(idx)){
        ret = fields[idx].type();
    }
    return ret;
}
