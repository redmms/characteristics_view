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

PartItem::PartItem(int struct_size_,
                    QVector<QVariant> fields_,
                    QMap<QString, int> field_names_,
                    QObject *parent) :
    QObject(parent),
    struct_size(struct_size_),
    fields(fields_),
    field_names(field_names_)
{
    validators.resize(struct_size);
    stringers.resize(struct_size);
    iconizers.resize(struct_size);
    for (int i = 0; i < struct_size; ++i){
        switch(static_cast<QMetaType::Type>(fields[i].type())){
        case QMetaType::QString:
            validators[i] = defaultQStringValidator;
            stringers[i] = defaultStringer;
            iconizers[i] = defaultIconizer;
            break;
        case QMetaType::Int:
        case QMetaType::Float:
            validators[i] = defaultIntValidator;
            stringers[i] = defaultStringer;
            iconizers[i] = defaultIconizer;
            break;
        case QMetaType::QIcon:
            validators[i] = defaultValidator;
            stringers[i] = defaultStringer;
            iconizers[i] = defaultQIconIconizer;
            break;
        case QMetaType::QVector3D:
            validators[i] = defaultQVector3DValidator;
            stringers[i] = defaultQVector3DStringer;
            iconizers[i] = defaultQIconIconizer;
            break;
        }
    }
}

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
        ret = stringers[idx](fields[idx]);
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

void PartItem::fillDefaults(){
    fields = defaults;  // TODO: добавить проверку в билдере, что типы их и размер совпадают внутри
}

bool PartItem::setDefaults(QVector<QVariant> defaults_){
    bool success = false;
    if (defaults_.size() == struct_size){
        for(int i = 0; i < struct_size; ++i){
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
                                      .arg(fields[i].type())
                                      .arg(defaults_[i].type());
                qCritical() << message;
            }
        }
        success = true;
    }
    else{
        qCritical() << "Arguments of wrong size";
    }
    return success;
}

bool PartItem::setDefault(QString field_name, QVariant default_){
    bool success = false;
    int idx = field_names.value(field_name, -1);
    if (idx != -1){
        defaults[idx] = default_;
        success = true;
    }
    else{
        qCritical() << "Wrong field name";
    }
    return success;
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
