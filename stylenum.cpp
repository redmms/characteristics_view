#include "stylenum.h"
#include <QComboBox>
#include <QDebug>

namespace Ssp{
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

    void checkStyleNames(const QComboBox *box)
    {
        // Проверка на cоответствие UI
        QString metal = style_names[Metal];
        QString nature_soil = style_names[NatureSoil];
        QString bump_soil = style_names[BumpSoil];
        QString stone = style_names[Stone];
        QString enhanced = style_names[EnhancedConcrete];
        QString stressed = style_names[StressedConcrete];
        QStringList all_items = {};
        for (int i = 0; i < box->count(); ++i) {
            all_items << box->itemText(i);  // Собираем имена из UI
        }
        for (auto name : {metal, nature_soil, bump_soil, stone,
                          enhanced, stressed}){
            if (!all_items.contains(name)){
                qWarning() << "QComboBox doesn't contain needed style names";
            }
        }
    }

    void checkStyleNums(const QComboBox *box)
    {
        // Проверка на cоответствие UI
        // Точное сопоставление здесь необязательно, но
        // в будущем позволит легко добавить соответствующую проверку.
        QString metal = style_nums.key(Metal);
        QString nature_soil = style_nums.key(NatureSoil);
        QString bump_soil = style_nums.key(BumpSoil);
        QString stone = style_nums.key(Stone);
        QString enhanced = style_nums.key(EnhancedConcrete);
        QString stressed = style_nums.key(StressedConcrete);
        QStringList all_items = {};
        for (int i = 0; i < box->count(); ++i) {
            all_items << box->itemText(i);  // Собираем имена из UI
        }
        for (auto name : {metal, nature_soil, bump_soil, stone,
                          enhanced, stressed}){
            if (!all_items.contains(name)){
                qWarning() << "QComboBox doesn't contain needed style names";
            }
        }
    }

    void checkStyleIconPaths()
    {
        // Проверка на cоответствие UI
        QString metal = ":/icons/stylebox_icons/hatch_1.png";
        QString nature_soil = ":/icons/stylebox_icons/hatch_2.png";
        QString bump_soil = ":/icons/stylebox_icons/hatch_3.png";
        QString stone = ":/icons/stylebox_icons/hatch_4.png";
        QString enhanced = ":/icons/stylebox_icons/hatch_5.png";
        QString stressed = ":/icons/stylebox_icons/hatch_6.png";
        static const int w = 120;  // Здесь 70 x 70 это размер calc_n.png
        static const int h = 25;
        for (auto name : {metal, nature_soil, bump_soil, stone, enhanced,
             stressed}){
            QIcon icon(name);
            if (icon.isNull() || icon.pixmap(w, h).isNull()){
                qWarning() << "Some style icon paths are incorrect";
            }
        }
    }
}
