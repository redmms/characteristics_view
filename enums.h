#pragma once
#include <QMap>
#include <QString>

// enum для режима заполнения. Каждый режим заполнения соответствует своему
// способу расчета параметров детали. А также словари со строковыми именами.
enum ModeNum{
    mass_mode,
    density_mode,
    copy_mode,
    none_mode
};

enum HatchStyleNum{
    metal,
    nature_soil,
    bump_soil,
    stone,
    enhanced_concrete,
    stressed_concrete,
    none_style
};

extern const QMap<ModeNum, QString> mode_names;

extern const QMap<QString, ModeNum> mode_nums;

extern const QMap<ModeNum, QString> mode_icon_paths;

extern const QMap<HatchStyleNum, QString> style_names;

extern const QMap<QString, HatchStyleNum> style_nums;

extern const QMap<HatchStyleNum, QString> style_icon_paths;
