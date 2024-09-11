#include "modenum.h"

// Словари строковых имен enum режима:
const QMap<ModeNum, QString> mode_names{
    {MassMode, "По массе"},
    {DensityMode, "По плотности"},
    {CopyMode, "По данным источника копирования"}
};

const QMap<QString, ModeNum> mode_nums{
    {"По массе", MassMode},
    {"По плотности", DensityMode},
    {"По данным источника копирования", CopyMode}
};

// Словарь путей иконок режима:
const QMap<ModeNum, QString> mode_icon_paths{
    {MassMode, ":/icons/methodbox_icons/calc_1.png"},
    {DensityMode, ":/icons/methodbox_icons/calc_2.png"},
    {CopyMode, ":/icons/methodbox_icons/calc_3.png"}
};
