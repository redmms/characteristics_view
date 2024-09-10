#include "detailitem.h"
#include <QDebug>

DetailItem::DetailItem(QObject *parent, ModeNum eval_method_, int mass_,
                       int density_, QVector3D mass_center_, Material material_
                       ) :
    eval_method(eval_method_),
    mass(mass_),
    density(density_),
    mass_center(mass_center_),
    material(material_)
{
//    if (!isValidMethod(eval_method_)){
//        qCritical() << "Wrong eval_method_ argument";
//    }
//    if (!isValidMass(mass_)){
//        qCritical() << "Wrong mass_ argument";
//    }
//    if (!isValidDensity(density_)){
//        qCritical() << "Wrong density_ argument";
//    }
//    // is it Ok that QVector3D stores doubles, but we use ints?
//    if (!isValidCenter(mass_center_)){
//        qCritical() << "Wrong mass_center_ argument";
//    }
//    if (!material_.isValid()){
//        qCritical() << "Wrong material_ argument";
//    }
    connect(&material, &Material::nameChanged, this,
            &DetailItem::materialNameChanged);
    connect(&material, &Material::styleChanged, this,
            &DetailItem::materialStyleChanged);
    connect(&material, &Material::angleChanged, this,
            &DetailItem::materialAngleChanged);
}

bool DetailItem::isValidNum(int num)
{
    return num >= 0;
}

bool DetailItem::isValidMethod(ModeNum method_)
{
    return method_ >= 0 && method_ < none_mode;
}

bool DetailItem::isValidMass(int mass_)
{
    return isValidNum(mass_);
}

bool DetailItem::isValidDensity(int density_)
{
    return isValidNum(density_);
}

bool DetailItem::isValidCoord(int coord)
{
    return isValidNum(coord);
}

ModeNum DetailItem::getMethod()
{
    return eval_method;
}

int DetailItem::getMass()
{
    return mass;
}

int DetailItem::getDensity()
{
    return density;
}

QVector3D DetailItem::getCenter()
{
    return mass_center;
}

Material DetailItem::getMaterial()
{
    return material;
}

bool DetailItem::setMethod(ModeNum eval_method_)
{
    bool success = isValidMethod(eval_method_);
    if (success){
        eval_method = eval_method_;
        emit methodChanged();
    }
    return success;
}

bool DetailItem::setMass(int mass_)
{
    bool success = isValidMass(mass_); // add mode checks? no, no need
    if (success){
        mass = mass_;
        emit massChanged();
    }
    return success;
}

bool DetailItem::setDensity(int density_)
{
    bool success = isValidDensity(density_);
    // the problem here is that we cannot set
        // the field empty
        // should this be an option?
    if (success){
        density = density_;
        emit densityChanged();
    }
    return success;
}

bool DetailItem::setCenter(QVector3D mass_center_) // ?
{
    bool success = isValidCenter(mass_center_);
    if (success){
        mass_center = mass_center_;
        emit centerChanged();
    }
    return success;
}

bool DetailItem::setMaterial(Material material_)
{
    setMaterialName(material_.getName());
    return setMaterialAngle(material_.getAngle()) &&
           setMaterialStyle(material_.getStyle());
}

void DetailItem::setMaterialName(QString material_name_)
{
    material.setName(material_name_);
}

bool DetailItem::setMaterialStyle(HatchStyleNum style_)
{
    return material.setStyle(style_);
}

bool DetailItem::setMaterialAngle(int angle_)
{
    return material.setAngle(angle_);
}

QString DetailItem::methodToString()
{
    return isValidMethod(eval_method) ? mode_names[eval_method] : "";
}

QString DetailItem::massToString()
{
    return isValidMass(mass) ? QString::number(mass) : "";
}

QString DetailItem::densityToString()
{
    return isValidDensity(density) ? QString::number(density) : "";
}

QString DetailItem::centerToString()
{
    QString result = "";
    if (isValidCenter(mass_center)){
        QString x = QString::number(int(mass_center.x()));
        QString y = QString::number(int(mass_center.y()));
        QString z = QString::number(int(mass_center.z()));
        result = x + ", " + y + ", " + z;
    }
    return result;
}

QString DetailItem::materialNameToString()
{
    return material.nameToString();
}

QString DetailItem::materialStyleToString()
{
    return material.styleToString();
}

QString DetailItem::materialAngleToString()
{
    return material.angleToString();
}

QString DetailItem::materialShortNameToString()
{
    return material.shortNameToString();
}

bool DetailItem::isValidIcon(QIcon icon_) // should I use const& for everything
// except QString?
{
    return !icon_.isNull() && !icon_.pixmap(70, 70).isNull();
    // here 70 x 70 is calc_n.png size
}

bool DetailItem::isValidCenter(QVector3D mass_center_)
{
    return isValidCoord(mass_center_.x()) &&
           isValidCoord(mass_center_.y()) &&
           isValidCoord(mass_center_.z());
}

QIcon DetailItem::getMethodIcon()
{
    QIcon result(mode_icon_paths[eval_method]);
    if (!isValidIcon(result)){
        qCritical() << "Invalid method icon";
    }
    return result;
}

QIcon DetailItem::getMaterialStyleIcon()
{
    return material.getStyleIcon();
}
