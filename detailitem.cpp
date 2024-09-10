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
    // Подключаем слоты Material:
    connect(&material, &Material::nameChanged, this,
            &DetailItem::materialNameChanged);
    connect(&material, &Material::styleChanged, this,
            &DetailItem::materialStyleChanged);
    connect(&material, &Material::angleChanged, this,
            &DetailItem::materialAngleChanged);
}

bool DetailItem::isValidNum(int num)
{
    // Валидация чисел по умолчанию:
    return num >= 0;
}

bool DetailItem::isValidMethod(ModeNum method_)
{
    // Валидация enum:
    return method_ >= 0 && method_ < none_mode;
}

bool DetailItem::isValidMass(int mass_)
{
    // Валидация по умолчанию:
    return isValidNum(mass_);
}

bool DetailItem::isValidDensity(int density_)
{
    // Валидация по умолчанию:
    return isValidNum(density_);
}

bool DetailItem::isValidCoord(int coord)
{
    // Валидация по умолчанию:
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
    // Сэттер способа расчета:
    bool success = isValidMethod(eval_method_);
    if (success){
        eval_method = eval_method_;
        emit methodChanged();
    }
    return success;
}

bool DetailItem::setMass(int mass_)
{
    // Сэттер массы:
    bool success = isValidMass(mass_); // add mode checks? no, no need
    if (success){
        mass = mass_;
        emit massChanged();
    }
    return success;
}

bool DetailItem::setDensity(int density_)
{
    // Сэттер плотности:
    bool success = isValidDensity(density_);
    if (success){
        density = density_;
        emit densityChanged();
    }
    return success;
}

bool DetailItem::setCenter(QVector3D mass_center_) // ?
{
    // Сэттер центра масс:
    bool success = isValidCenter(mass_center_);
    if (success){
        mass_center = mass_center_;
        emit centerChanged();
    }
    return success;
}

bool DetailItem::setMaterial(Material material_)
{
    // Сэттер поля Material:
    setMaterialName(material_.getName());
    return setMaterialAngle(material_.getAngle()) &&
           setMaterialStyle(material_.getStyle());
}

void DetailItem::setMaterialName(QString material_name_)
{
    // Сэттер названия материала:
    material.setName(material_name_);
}

bool DetailItem::setMaterialStyle(HatchStyleNum style_)
{
    // Сэттер стиля штриховки:
    return material.setStyle(style_);
}

bool DetailItem::setMaterialAngle(int angle_)
{
    // Сэттер угла штриховки:
    return material.setAngle(angle_);
}

QString DetailItem::methodToString()
{
    // Преобразование в строку:
    return isValidMethod(eval_method) ? mode_names[eval_method] : "";
}

QString DetailItem::massToString()
{
    // Преобразование в строку:
    return isValidMass(mass) ? QString::number(mass) : "";
}

QString DetailItem::densityToString()
{
    // Преобразование в строку:
    return isValidDensity(density) ? QString::number(density) : "";
}

QString DetailItem::centerToString()
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

QString DetailItem::materialNameToString()
{
    // Преобразование в строку:
    return material.nameToString();
}

QString DetailItem::materialStyleToString()
{
    // Преобразование в строку:
    return material.styleToString();
}

QString DetailItem::materialAngleToString()
{
    // Преобразование в строку:
    return material.angleToString();
}

QString DetailItem::materialShortNameToString()
{
    // Преобразование в строку:
    return material.shortNameToString();
}

bool DetailItem::isValidIcon(QIcon icon_)
{
    // Проверка иконки на пустоту и невалидный путь:
    return !icon_.isNull() && !icon_.pixmap(70, 70).isNull();
    // here 70 x 70 is calc_n.png size
}

bool DetailItem::isValidCenter(QVector3D mass_center_)
{
    // Валидация по умолчанию:
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
