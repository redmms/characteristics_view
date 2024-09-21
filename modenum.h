#pragma once
#include <QMap>
#include <QString>

class QComboBox;
namespace Msp{
    // enum для режима заполнения. Каждый режим заполнения соответствует своему
    // способу расчета параметров детали. А также словари со строковыми именами.
    enum ModeNum{
        MassMode,
        DensityMode,
        CopyMode,
        NoneMode
    };

    // Словари строковых имен enum режима:
    static const QMap<ModeNum, QString> mode_names{
        {MassMode, "По массе"},
        {DensityMode, "По плотности"},
        {CopyMode, "По данным источника копирования"}
    };

    static const QMap<QString, ModeNum> mode_nums{
        {"По массе", MassMode},
        {"По плотности", DensityMode},
        {"По данным источника копирования", CopyMode}
    };

    // Словарь путей иконок режима:
    static const QMap<ModeNum, QString> mode_icon_paths{
        {MassMode, ":/icons/methodbox_icons/calc_1.png"},
        {DensityMode, ":/icons/methodbox_icons/calc_2.png"},
        {CopyMode, ":/icons/methodbox_icons/calc_3.png"}
    };

    // Функции проверки словарей
    void checkModeNames(const QComboBox* box);
    void checkModeNums(const QComboBox* box);
    void checkModeIconPaths();
}
