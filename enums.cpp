#include "enums.h"

// Словари строковых имен enum режима:
const QMap<ModeNum, QString> mode_names{
                                  {mass_mode, "По массе"},
                                  {density_mode, "По плотности"},
                                  {copy_mode, "По данным источника копирования"}
};

const QMap<QString, ModeNum> mode_nums{
    {"По массе", mass_mode},
            {"По плотности", density_mode},
             {"По данным источника копирования", copy_mode}
            };

// Словарь путей иконок режима:
const QMap<ModeNum, QString> mode_icon_paths{
    {mass_mode, ":/icons/methodbox_icons/calc_1.png"},
    {density_mode, ":/icons/methodbox_icons/calc_2.png"},
    {copy_mode, ":/icons/methodbox_icons/calc_3.png"}
};

// Словари строковых имен enum стиля штриховки:
const QMap<HatchStyleNum, QString> style_names{
    {metal, "Металл"},
    {nature_soil, "Естественный грунт"},
    {bump_soil, "Насыпной грунт"},
    {stone, "Камень искусственный"},
    {enhanced_concrete, "Железобетон"},
    {stressed_concrete, "Напряженный железобетон"}
};

const QMap<QString, HatchStyleNum> style_nums{
    {"Металл", metal},
    {"Естественный грунт", nature_soil},
    {"Насыпной грунт", bump_soil},
    {"Камень искусственный", stone},
    {"Железобетон", enhanced_concrete},
    {"Напряженный железобетон", stressed_concrete}
};

// Словарь путей иконок стиля штриховки:
const QMap<HatchStyleNum, QString> style_icon_paths{
    {metal, ":/icons/stylebox_icons/hatch_1.png"},
    {nature_soil, ":/icons/stylebox_icons/hatch_2.png"},
    {bump_soil, ":/icons/stylebox_icons/hatch_3.png"},
    {stone, ":/icons/stylebox_icons/hatch_4.png"},
    {enhanced_concrete, ":/icons/stylebox_icons/hatch_5.png"},
    {stressed_concrete, ":/icons/stylebox_icons/hatch_6.png"}
};
