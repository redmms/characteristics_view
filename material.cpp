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

bool Material::isValidName(QString name_)
{
    // Валидация имени:
    return !name_.split(' ').isEmpty();
}

bool Material::isValidStyle(HatchStyleNum style_)
{
    // Валидация enum'a:
    return style_ >= 0 && style_ < NoneStyle;
}

bool Material::isValidAngle(int angle_)
{
    // Валидация по умолчанию:
    return angle_ >= 0;
}

bool Material::isValidStyleIcon(QIcon icon_)
{
    // Проверка иконки на пустоту и неверный путь:
    static const int w = 120;  // here 120 x 25 is hatch_n.png size
    static const int h = 25;
    return !icon_.isNull() && !icon_.pixmap(w, h).isNull();
}

bool Material::isValid()
{
    // Проверка объекта класса:
    return isValidStyle(hatch_style) && isValidAngle(hatch_angle);
}

bool Material::setName(QString name_)
{
    // Сэттер со встроенной валидацией:
    bool success = name != name_ && isValidName(name_);
    if (success){
        name = name_;
        short_name = name_.split(' ')[0];
        emit nameChanged();
    }
    return success;
}

bool Material::setStyle(HatchStyleNum style_)
{
    // Сэттер со встроенной валидацией:
    bool success = hatch_style != style_ && isValidStyle(style_);
    if (success){
        hatch_style = style_;
        emit styleChanged();
    }
    return success;
}

bool Material::setAngle(int angle_)
{
    // Сэттер со встроенной валидацией:
    bool success = hatch_angle != angle_ && isValidAngle(angle_);
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