#include "anglehelper.h"

QVariant AngleHelper::getString(DetailItem *detail)
{
    // Строка для Qt::DisplayRole:
    return detail->materialAngleToString();
}

QVariant AngleHelper::getIcon(DetailItem *detail)
{
    // Иконка, либо пустой QVariant для Qt::DecorationRole:
    return {};
}

void AngleHelper::connectDetailSignal(DetailItem *detail)
{
    // Каждая ячейка столбца Угол уведомляет об изменении вначале свой хэлпер:
    connect(detail, &DetailItem::materialAngleChanged, this, &AngleHelper::findChangedIndex);
}



