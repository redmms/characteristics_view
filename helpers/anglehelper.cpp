#include "anglehelper.h"

QVariant AngleHelper::getString(PartItem *part)
{
    // Строка для Qt::DisplayRole:
    return part->materialAngleToString();
}

QVariant AngleHelper::getIcon(PartItem *part)
{
    // Иконка, либо пустой QVariant для Qt::DecorationRole:
    Q_UNUSED(part)
    return {};
}

void AngleHelper::connectPartSignal(PartItem *part)
{
    // Каждая ячейка столбца Угол уведомляет об изменении вначале свой помощник:
    connect(part, &PartItem::materialAngleChanged, this, &AngleHelper::findChangedIndex);
}
