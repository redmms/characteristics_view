#pragma once
#include "modenum.h"
#include "stylenum.h"
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
    ModeNum eval_method;  // Способ расчёта
    int mass;  // Масса
    int density;  // Плотность
    QVector3D mass_center;  // Координаты центра масс, внутри float'ы
    Material material;  // Материал, стиль и угол штриховки материала

    // Приватные методы:
    bool isValidNum(int num);

public:
    // Конструктор:
    explicit DetailItem(QObject* parent = nullptr, ModeNum eval_method_ = NoneMode,
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
    bool setMethod(ModeNum eval_method_ = NoneMode); // rv bool ok?
    bool setMass(int mass_ = -1);
    bool setDensity(int density_ = -1);
    bool setCenter(QVector3D mass_center_ = {-1, -1, -1});
    bool setMaterial(Material material_ = Material());
    bool setMaterialName(QString material_name_ = ""); // should I exclude it?
    bool setMaterialStyle(HatchStyleNum style_ = NoneStyle);
    bool setMaterialAngle(int angle_ = -1);

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
