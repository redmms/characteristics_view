#include "structitem.h"

bool StructItem::isValidIndex(int idx){
    return idx >= 0 && idx < struct_size;
}

bool StructItem::isValidField(int idx, QVariant field){
    bool ret = false;
    if (isValidIndex(idx)){
        ret = validators[idx](field);
    }
    return ret;
}

StructItem::StructItem(int struct_size_,
                    QVector<QVariant> fields_,
                    QMap<QString, int> field_names_,
                    QObject *parent) :
    QObject(parent),
    struct_size(struct_size_),
    fields(fields_),
    field_names(field_names_)
{
    for (int i = 0; i < struct_size; ++i){
        switch(static_cast<QMetaType::Type>(fields[i].type())){
        case QMetaType::QString:
            validators[i] = defaultQStringValidator;
            stringers[i] = defaultStringer;
            iconizers[i] = defaultIconizer;
            break;
        case QMetaType::Int:
            validators[i] = defaultIntValidator;
            stringers[i] = defaultStringer;
            iconizers[i] = defaultIconizer;
            break;
        case QMetaType::Float:
            validators[i] = defaultIntValidator;
            stringers[i] = defaultFloatStringer;
            iconizers[i] = defaultIconizer;
            break;
        case QMetaType::Double:
            validators[i] = defaultIntValidator;
            stringers[i] = defaultDoubleStringer;
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
        default:
            validators[i] = defaultValidator;
            stringers[i] = defaultStringer;
            iconizers[i] = defaultIconizer;
            break;
        }
    }
}

bool StructItem::isValid(int idx){
    auto ret = false;
    if (isValidIndex(idx)){
        ret = isValidField(idx, fields[idx]);
    }
    return ret;
}

QVariant StructItem::Get(int idx){
    QVariant ret = {};
    if (isValidIndex(idx)){
        ret = fields[idx];
    }
    return ret;
}

QString StructItem::getString(int idx){
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

QIcon StructItem::getIcon(int idx){
    QIcon ret = {};
    if (isValidIndex(idx)){
        ret = iconizers[idx](fields[idx]);
    }
    return ret;
}

bool StructItem::Set(int idx, QVariant value){
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

void StructItem::fillDefaults(){
    fields = defaults;  // TODO: добавить проверку в билдере, что типы их и размер совпадают внутри
}

bool StructItem::isExistingContainer(QString container_name, const type_info &return_type){
    bool is_error =  container_name == "validators" &&
                        return_type != typeid(bool) ||
                    container_name == "stringers" &&
                        return_type != typeid(QString) ||
                    container_name == "iconizers" &&
                        return_type != typeid(QIcon);
    return !is_error;
}

bool StructItem::setDefaults(QVector<QVariant> defaults_){
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
        for (int i = 0; i < struct_size; ++i){
            emit changed(i);
        }
        success = true;
    }
    else{
        qCritical() << "Arguments of wrong size";
    }
    return success;
}

bool StructItem::setDefault(QString field_name, QVariant default_){
    bool success = false;
    int idx = field_names.value(field_name, -1);
    if (idx != -1){
        defaults[idx] = default_;
        emit changed(idx);
        success = true;
    }
    else{
        qCritical() << "Wrong field name";
    }
    return success;
}

int StructItem::getStructureSize(){
    return struct_size;
}

QVariant::Type StructItem::getType(int idx){
    QVariant::Type ret = {};
    if (isValidIndex(idx)){
        ret = fields[idx].type();
    }
    return ret;
}
