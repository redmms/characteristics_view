#include "stylenum.h"

// Словари строковых имен enum стиля штриховки:
const QMap<HatchStyleNum, QString> style_names{
    {Metal, "Металл"},
    {NatureSoil, "Естественный грунт"},
    {BumpSoil, "Насыпной грунт"},
    {Stone, "Камень искусственный"},
    {EnhancedConcrete, "Железобетон"},
    {StressedConcrete, "Напряженный железобетон"}
};

const QMap<QString, HatchStyleNum> style_nums{
    {"Металл", Metal},
    {"Естественный грунт", NatureSoil},
    {"Насыпной грунт", BumpSoil},
    {"Камень искусственный", Stone},
    {"Железобетон", EnhancedConcrete},
    {"Напряженный железобетон", StressedConcrete}
};

// Словарь путей иконок стиля штриховки:
const QMap<HatchStyleNum, QString> style_icon_paths{
    {Metal, ":/icons/stylebox_icons/hatch_1.png"},
    {NatureSoil, ":/icons/stylebox_icons/hatch_2.png"},
    {BumpSoil, ":/icons/stylebox_icons/hatch_3.png"},
    {Stone, ":/icons/stylebox_icons/hatch_4.png"},
    {EnhancedConcrete, ":/icons/stylebox_icons/hatch_5.png"},
    {StressedConcrete, ":/icons/stylebox_icons/hatch_6.png"}
};