#pragma once
#include "material.h"
#include <QObject>
#include <QScopedPointer>
#include <QVector3D>
#include <QMap>
#include "enums.h"
#include <QIcon>

class DetailItem : public QObject
{
    Q_OBJECT
private:
    ModeNum eval_method; // doesn't depend on material or mass method
    int mass;
    int density;
    QVector3D mass_center;
    Material material;

    bool isValidNum(int num);

public:
    explicit DetailItem(QObject* parent = nullptr, ModeNum eval_method_ = none_mode,
                        int mass_ = -1, int density_ = -1,
                        QVector3D mass_center_ = {-1, -1, -1},
                        Material material_ = {});

    bool isValidMethod(ModeNum method_);
    bool isValidMass(int mass_);
    bool isValidDensity(int density_);
    bool isValidCoord(int coord);
    bool isValidIcon(QIcon icon_);
    bool isValidCenter(QVector3D mass_center_);

    ModeNum getMethod();
    int getMass();
    int getDensity();
    QVector3D getCenter();
    Material getMaterial();

    bool setMethod(ModeNum eval_method_); // rv bool ok?
    bool setMass(int mass_);
    bool setDensity(int density_);
    bool setCenter(QVector3D mass_center_);
    bool setMaterial(Material material_);
    void setMaterialName(QString material_name_); // should I exclude it?
    bool setMaterialStyle(HatchStyleNum style_);
    bool setMaterialAngle(int angle_);

    QString methodToString();
    QString massToString();
    QString densityToString();
    QString centerToString();
    QString materialNameToString();
    QString materialStyleToString();
    QString materialAngleToString();
    QString materialShortNameToString();

    QIcon getMethodIcon();
    QIcon getMaterialStyleIcon();

signals:
    void methodChanged();
    void massChanged();
    void densityChanged();
    void centerChanged();
    void materialNameChanged();
    void materialStyleChanged();
    void materialAngleChanged();
};
