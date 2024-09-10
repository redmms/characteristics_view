#pragma once
#include <Qstring>
#include <QMap>
#include "enums.h"
#include <QObject>
#include <QIcon>

class Material : public QObject
{
    Q_OBJECT
private:
    QString name;
    QString short_name;
    HatchStyleNum hatch_style;
    int hatch_angle;

public:
    explicit Material(QObject* parent = nullptr, QString name_ = "",
                      HatchStyleNum hatch_style_ = none_style,
                      int hatch_angle_ = -1
                      );
    Material(const Material& other);

    QString getName();
    QString getShortName();
    HatchStyleNum getStyle();
    int getAngle();
    QIcon getStyleIcon();  //

    bool isValidStyle(HatchStyleNum style_);
    bool isValidAngle(int angle_);
    bool isValidStyleIcon(QIcon icon_);
    bool isValid();

    void setName(QString name_);
    bool setStyle(HatchStyleNum style_);
    bool setAngle(int angle_);

    QString nameToString();
    QString shortNameToString();
    QString styleToString();
    QString angleToString();

signals:
    void nameChanged();
    void styleChanged();
    void angleChanged();
};
