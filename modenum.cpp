#include "modenum.h"
#include <QDebug>
#include <QComboBox>

namespace Msp{
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

    void checkModeNames(const QComboBox* box)
    {
        // Проверка на cоответствие UI
        QString mass = mode_names[MassMode];
        QString density = mode_names[DensityMode];
        QString copy = mode_names[CopyMode];
        QStringList all_items = {};
        for (int i = 0; i < box->count(); ++i) {
            all_items << box->itemText(i);  // Собираем имена из UI
        }
        for (auto name : {mass, density, copy}){
            if (!all_items.contains(name)){
                qWarning() << "QComboBox doesn't contain needed mode names";
            }
        }
    }

    void checkModeNums(const QComboBox* box)
    {
        // Проверка на cоответствие UI
        QString mass = mode_nums.key(MassMode);
        QString density = mode_nums.key(DensityMode);
        QString copy = mode_nums.key(CopyMode);
        QStringList all_items = {};
        for (int i = 0; i < box->count(); ++i) {
            all_items << box->itemText(i); // Собираем имена из UI
        }
        for (auto name : {mass, density, copy}){
            if (!all_items.contains(name)){
                qWarning() << "QComboBox doesn't contain needed mode names";
            }
        }
    }

    void checkModeIconPaths()
    {
        // Проверка на cоответствие UI
        QString mass = ":/icons/methodbox_icons/calc_1.png";
        QString density = ":/icons/methodbox_icons/calc_2.png";
        QString copy = ":/icons/methodbox_icons/calc_3.png";
        static const int w = 70;  // Здесь 70 x 70 это размер calc_n.png
        static const int h = 70;
        for (auto name : {mass, density, copy}){
            QIcon icon(name);
            if (icon.isNull() || icon.pixmap(w, h).isNull()){
                qWarning() << "Some mode icon paths are incorrect";
            }
        }
    }
}
