#pragma once
#include "stylenum.h"
#include <Qstring>
#include <QMap>
#include <QObject>
#include <QIcon>

class Material : public QObject
{
    Q_OBJECT
private:
    // Приватные поля:
    QString name;  // Полное название материала
    QString short_name;  // Сокращенное название
    HatchStyleNum hatch_style;  // Стиль штриховки
    int hatch_angle;  // Угол штриховки

public:
    // Конструкторы:
    explicit Material(QObject* parent = nullptr, QString name_ = "",
                      HatchStyleNum hatch_style_ = NoneStyle,
                      int hatch_angle_ = -1
                      );
    Material(const Material& other);

    // Геттеры:
    QString getName();
    QString getShortName();
    HatchStyleNum getStyle();
    int getAngle();
    QIcon getStyleIcon();

    // Методы валидации:
    bool isValidName(QString name_);
    bool isValidStyle(HatchStyleNum style_);
    bool isValidAngle(int angle_);
    bool isValidStyleIcon(QIcon icon_);
    bool isValid();

    // Сэттеры со встроенной валидацией:
    bool setName(QString name_ = "");
    bool setStyle(HatchStyleNum style_ = NoneStyle);
    bool setAngle(int angle_ = -1);

    // Методы преобразования в строку:
    QString nameToString();
    QString shortNameToString();
    QString styleToString();
    QString angleToString();

signals:
    // Сигналы об изменении полей:
    void nameChanged();
    void styleChanged();
    void angleChanged();
};
