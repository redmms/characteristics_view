#include "material.h"
#include <QDebug>


Material::Material(QObject *parent, QString name_,
                   HatchStyleNum hatch_style_, int hatch_angle_
                   ) :
    name(name_),
    hatch_style(hatch_style_),
    hatch_angle(hatch_angle_)
{}

Material::Material(const Material &other)
{
    // Конструктор копирования для содержимого, без сигналов
    name = other.name;
    hatch_style = other.hatch_style;
    hatch_angle = other.hatch_angle;
}

QString Material::getName()
{
    return name;
}

QString Material::getShortName()
{
    return short_name;
}

HatchStyleNum Material::getStyle()
{
    return hatch_style;
}

int Material::getAngle()
{
    return hatch_angle;
}

QIcon Material::getStyleIcon()
{
    QIcon result(style_icon_paths[hatch_style]);
    if (!isValidStyleIcon(result)){
        qCritical() << "Invalid style icon";
    }
    return result;
}

bool Material::isValidStyle(HatchStyleNum style_)
{
    // Валидация enum'a
    return style_ >= 0 && style_ < none_style;
}

bool Material::isValidAngle(int angle_)
{
    // Валидация по умолчанию:
    return angle_ >= 0;
}

bool Material::isValidStyleIcon(QIcon icon_)
{
    // Проверка иконки на пустоту и неверный путь:
    return !icon_.isNull() && !icon_.pixmap(120, 25).isNull();
}

bool Material::isValid()
{
    // Проверка объекта класса:
    return isValidStyle(hatch_style) && isValidAngle(hatch_angle);
}

void Material::setName(QString name_)
{
    // Сэттер со встроенной валидацией:
    name = name_;
    short_name = name_.split(' ')[0];
    emit nameChanged();
}

bool Material::setStyle(HatchStyleNum style_)
{
    // Сэттер со встроенной валидацией:
    bool success = isValidStyle(style_);
    if (success){
        hatch_style = style_;
        emit styleChanged();
    }
    return success;
}

bool Material::setAngle(int angle_)
{
    // Сэттер со встроенной валидацией:
    bool success = isValidAngle(angle_);
    if (success){
        hatch_angle = angle_;
        emit angleChanged();
    }
    return success;
}

QString Material::nameToString()
{
    // Метод преобразования в строку:
    return name;
}

QString Material::shortNameToString()
{
    // Метод преобразования в строку:
    return short_name;
}

QString Material::styleToString()
{
    // Метод преобразования в строку:
    return isValidStyle(hatch_style) ? style_names[hatch_style] : "";
}

QString Material::angleToString()
{
    // Метод преобразования в строку:
    return isValidAngle(hatch_angle) ? QString::number(hatch_angle) : "";
}
