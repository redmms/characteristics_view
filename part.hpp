#pragma once
#include "modenum.h"
#include "stylenum.h"
#include <QVector3D>

struct Part{
    Msp::ModeNum eval_method = Msp::NoneMode;  // Способ расчёта
    int mass = -1;  // Масса
    int density = -1;  // Плотность
    QVector3D mass_center = {-1, -1, -1};  // Координаты центра масс, внутри float'ы
    QString material_short_name = "";  // Сокращенное название
    Ssp::HatchStyleNum hatch_style = Ssp::NoneStyle;  // Стиль штриховки
    int hatch_angle = -1;  // Угол штриховки
};
