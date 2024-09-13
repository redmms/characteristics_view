#include "anglehelper.h"

QVariant AngleHelper::getString(PartItem *part)
{
    // Строка для Qt::DisplayRole:
    return part->materialAngleToString();
}

QVariant AngleHelper::getIcon(PartItem *part)
{
    // Иконка, либо пустой QVariant для Qt::DecorationRole:
    return {};
}

void AngleHelper::connectPartSignal(PartItem *part)
{
    // Каждая ячейка столбца Угол уведомляет об изменении вначале свой хэлпер:
    connect(part, &PartItem::materialAngleChanged, this, &AngleHelper::findChangedIndex);
}
