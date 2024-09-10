#pragma once
#include "enums.h"
#include "material.h"
#include <QObject>
#include <QScopedPointer>
#include <QVector3D>
#include <QMap>
#include <QIcon>

class DetailItem : public QObject
{
    Q_OBJECT
private:
    // Приватные поля:
    // Поля не проверяются соответствию режиму ввода FillMode. Это задача
    // UI класса. eval_method исключительно в роли поля способ расчёта.
    ModeNum eval_method;
    int mass;
    int density;
    QVector3D mass_center;  // Внутри float'ы
    Material material;

    // Приватные методы:
    bool isValidNum(int num);

public:
    // Конструктор:
    explicit DetailItem(QObject* parent = nullptr, ModeNum eval_method_ = none_mode,
                        int mass_ = -1, int density_ = -1,
                        QVector3D mass_center_ = {-1, -1, -1},
                        Material material_ = Material());

    // Методы валидации:
    bool isValidMethod(ModeNum method_);
    bool isValidMass(int mass_);
    bool isValidDensity(int density_);
    bool isValidCoord(int coord);
    bool isValidIcon(QIcon icon_);
    bool isValidCenter(QVector3D mass_center_);

    // Геттеры:
    ModeNum getMethod();
    int getMass();
    int getDensity();
    QVector3D getCenter();
    Material getMaterial();

    // Сэттеры со встроенной валидацией:
    bool setMethod(ModeNum eval_method_); // rv bool ok?
    bool setMass(int mass_);
    bool setDensity(int density_);
    bool setCenter(QVector3D mass_center_);
    bool setMaterial(Material material_);
    void setMaterialName(QString material_name_); // should I exclude it?
    bool setMaterialStyle(HatchStyleNum style_);
    bool setMaterialAngle(int angle_);

    // Методы преобразования в строку для каждого поля, даже если оно уже
    // строка. Сделано для удобства вызова из хэлперов модели.
    QString methodToString();
    QString massToString();
    QString densityToString();
    QString centerToString();
    QString materialNameToString();  // Не используется в модели
    QString materialShortNameToString();
    QString materialStyleToString();
    QString materialAngleToString();

    // Методы получения иконок для Qt::DecorationRole:
    QIcon getMethodIcon();
    QIcon getMaterialStyleIcon();

signals:
    // Сигналы об измении полей, чтобы можно было работать с деталью по
    // указателю:
    void methodChanged();
    void massChanged();
    void densityChanged();
    void centerChanged();
    void materialNameChanged();
    void materialStyleChanged();
    void materialAngleChanged();
};
