#pragma once
#include <QMap>
#include <QString>

class QComboBox;
namespace Ssp{
    // enum для стиля штриховки. А также словари со строковыми именами.
    enum HatchStyleNum{
        Metal,
        NatureSoil,
        BumpSoil,
        Stone,
        EnhancedConcrete,
        StressedConcrete,
        NoneStyle
    };

    extern const QMap<HatchStyleNum, QString> style_names;

    extern const QMap<QString, HatchStyleNum> style_nums;

    extern const QMap<HatchStyleNum, QString> style_icon_paths;

    // Методы проверки словарей
    void checkStyleNames(QComboBox* box);
    void checkStyleNums(QComboBox* box);
    void checkStyleIconPaths();
}
