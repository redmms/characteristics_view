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
    Ssp::HatchStyleNum hatch_style;  // Стиль штриховки
    int hatch_angle;  // Угол штриховки

public:
    // Конструкторы:
    Material(QObject* parent = nullptr, QString name_ = "",
                      Ssp::HatchStyleNum hatch_style_ = Ssp::NoneStyle,
                      int hatch_angle_ = -1);
    Material(const Material& other);

    // Оператор копирования полей без сигналов:
    Material& operator=(const Material& other);

    // Геттеры:
    QString getName();
    QString getShortName();
    Ssp::HatchStyleNum getStyle();
    int getAngle();
    QIcon getStyleIcon();

    // Методы валидации:
    bool isValidName(QString name_);
    bool isValidStyle(Ssp::HatchStyleNum style_);
    bool isValidAngle(int angle_);
    bool isValid();

    // Сэттер для сброса значений на по умолчанию.
    // Значения по умолчанию считаются невалидными.
    void setDetaultValues();

    // Сэттеры со встроенной валидацией:
    bool setName(QString name_ = "");
    bool setStyle(Ssp::HatchStyleNum style_ = Ssp::NoneStyle);
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
