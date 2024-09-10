#include "material.h"
#include <QDebug>


Material::Material(QObject *parent, QString name_,
                   HatchStyleNum hatch_style_, int hatch_angle_
                   ) :
    name(name_),
    hatch_style(hatch_style_),
    hatch_angle(hatch_angle_)
{
//    if (!isValidStyle(hatch_style_)){
//        qCritical() << "Wrong hatch_style_ argument";
//    }
//    if (!isValidAngle(hatch_angle_)){
//        qCritical() << "Wrong hatch_angle_ argument";
//    }
}

Material::Material(const Material &other)
{
    name = other.name;
    hatch_style = other.hatch_style;
    hatch_angle = other.hatch_angle;
}

QString Material::getName()
{
    return name;
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
    return style_ >= 0 && style_ < none_style;
}

bool Material::isValidAngle(int angle_)
{
    return angle_ >= 0;
}

bool Material::isValidStyleIcon(QIcon icon_)
{
    return !icon_.isNull() && !icon_.pixmap(120, 25).isNull();
}

bool Material::isValid()
{
    return isValidStyle(hatch_style) && isValidAngle(hatch_angle);
}

void Material::setName(QString name_)
{
    name = name_;
    short_name = name_.split(' ')[0];
    emit nameChanged();
}

bool Material::setStyle(HatchStyleNum style_)
{
    bool success = isValidStyle(style_);
    if (success){
        hatch_style = style_;
        emit styleChanged();
    }
    return success; // is it ok that success only depends on
    // validity here?
}

bool Material::setAngle(int angle_)
{
    bool success = isValidAngle(angle_);
    if (success){
        hatch_angle = angle_;
        emit angleChanged();
    }
    return success; // is it ok that success only depends on
    // validity here?
}

QString Material::nameToString()
{
    return name;
}

QString Material::shortNameToString()
{
    return short_name;
}

QString Material::styleToString()
{
    return isValidStyle(hatch_style) ? style_names[hatch_style] : "";
}

QString Material::angleToString()
{
    return isValidAngle(hatch_angle) ? QString::number(hatch_angle) : "";
}
