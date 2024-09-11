#pragma once
#include <QMap>
#include <QString>

// enum для режима заполнения. Каждый режим заполнения соответствует своему
// способу расчета параметров детали. А также словари со строковыми именами.
enum ModeNum{
    MassMode,
    DensityMode,
    CopyMode,
    NoneMode
};

extern const QMap<ModeNum, QString> mode_names;

extern const QMap<QString, ModeNum> mode_nums;

extern const QMap<ModeNum, QString> mode_icon_paths;
