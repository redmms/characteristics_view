#include "partitem.h"
#include <QDebug>

PartItem::PartItem(QObject *parent, Msp::ModeNum eval_method_, int mass_,
                       int density_, QVector3D mass_center_, Material material_
                       ) :
    QObject(parent),
    eval_method(eval_method_),
    mass(mass_),
    density(density_),
    mass_center(mass_center_),
    material(material_)
{
    // Подключаем слоты Material:
    connect(&material, &Material::nameChanged, this,
            &PartItem::materialNameChanged);
    connect(&material, &Material::styleChanged, this,
            &PartItem::materialStyleChanged);
    connect(&material, &Material::angleChanged, this,
            &PartItem::materialAngleChanged);
}

bool PartItem::isValidNum(int num)
{
    // Валидация чисел по умолчанию:
    return num >= 0;
}

bool PartItem::isValidMethod(Msp::ModeNum method_)
{
    // Валидация enum:
    return method_ >= 0 && method_ < Msp::NoneMode;
}

bool PartItem::isValidMass(int mass_)
{
    // Валидация по умолчанию:
    return isValidNum(mass_);
}

bool PartItem::isValidDensity(int density_)
{
    // Валидация по умолчанию:
    return isValidNum(density_);
}

bool PartItem::isValidCoord(int coord)
{
    // Валидация по умолчанию:
    return isValidNum(coord);
}

bool PartItem::isValidCenter(QVector3D mass_center_)
{
    // Валидация по умолчанию:
    return isValidCoord(mass_center_.x()) &&
           isValidCoord(mass_center_.y()) &&
           isValidCoord(mass_center_.z());
}

Msp::ModeNum PartItem::getMethod()
{
    return eval_method;
}

int PartItem::getMass()
{
    return mass;
}

int PartItem::getDensity()
{
    return density;
}

QVector3D PartItem::getCenter()
{
    return mass_center;
}

Material PartItem::getMaterial()
{
    return material;
}

void PartItem::setDefaultValues()
{
    // Сэттер для сброса значений в исходные.
    // Значения по умолчанию считаются невалидными
    eval_method = Msp::NoneMode;
    emit methodChanged();
    mass = -1;
    emit massChanged();
    density = -1;
    emit densityChanged();
    mass_center = {-1, -1, -1};
    emit centerChanged();
    material.setDetaultValues();  // Важно, чтобы сигналы Material были подключены
}

bool PartItem::setMethod(Msp::ModeNum eval_method_)
{
    // Сэттер способа расчета:
    bool success = eval_method != eval_method_ && isValidMethod(eval_method_);
    if (success){
        eval_method = eval_method_;
        emit methodChanged();
    }
    return success;
}

bool PartItem::setMass(int mass_)
{
    // Сэттер массы:
    bool success = mass != mass_ && isValidMass(mass_);
    if (success){
        mass = mass_;
        emit massChanged();
    }
    return success;
}

bool PartItem::setDensity(int density_)
{
    // Сэттер плотности:
    bool success = density != density_ && isValidDensity(density_);
    if (success){
        density = density_;
        emit densityChanged();
    }
    return success;
}

bool PartItem::setCenter(QVector3D mass_center_)
{
    // Сэттер центра масс:
    bool success = mass_center != mass_center_ && isValidCenter(mass_center_);
    if (success){
        mass_center = mass_center_;
        emit centerChanged();
    }
    return success;
}

bool PartItem::setMaterial(Material material_)
{
    // Сэттер поля Material:
    return setMaterialName(material_.getName()) &&
           setMaterialAngle(material_.getAngle()) &&
           setMaterialStyle(material_.getStyle());
}

bool PartItem::setMaterialName(QString material_name_)
{
    // Сэттер названия материала:
    return material.setName(material_name_);
}

bool PartItem::setMaterialStyle(Ssp::HatchStyleNum style_)
{
    // Сэттер стиля штриховки:
    return material.setStyle(style_);
}

bool PartItem::setMaterialAngle(int angle_)
{
    // Сэттер угла штриховки:
    return material.setAngle(angle_);
}

QString PartItem::methodToString()
{
    // Преобразование в строку:
    return isValidMethod(eval_method) ? Msp::mode_names[eval_method] : "";
}

QString PartItem::massToString()
{
    // Преобразование в строку:
    return isValidMass(mass) ? QString::number(mass) : "";
}

QString PartItem::densityToString()
{
    // Преобразование в строку:
    return isValidDensity(density) ? QString::number(density) : "";
}

QString PartItem::centerToString()
{
    // Преобразование в строку:
    QString result = "";
    if (isValidCenter(mass_center)){
        QString x = QString::number(int(mass_center.x()));
        QString y = QString::number(int(mass_center.y()));
        QString z = QString::number(int(mass_center.z()));
        result = x + ", " + y + ", " + z;
    }
    return result;
}

QString PartItem::materialNameToString()
{
    // Преобразование в строку:
    return material.nameToString();
}

QString PartItem::materialStyleToString()
{
    // Преобразование в строку:
    return material.styleToString();
}

QString PartItem::materialAngleToString()
{
    // Преобразование в строку:
    return material.angleToString();
}

QString PartItem::materialShortNameToString()
{
    // Преобразование в строку:
    return material.shortNameToString();
}

QIcon PartItem::getMethodIcon()
{
    return QIcon(Msp::mode_icon_paths[eval_method]);
}

QIcon PartItem::getMaterialStyleIcon()
{
    return material.getStyleIcon();
}
