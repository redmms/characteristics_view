#include "modenum.h"
#include <QDebug>
#include <QComboBox>

namespace Msp{
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
