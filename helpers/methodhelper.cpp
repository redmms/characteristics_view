#include "methodhelper.h"

QVariant MethodHelper::getString(PartItem *part)
{
    // Строка для Qt::DisplayRole:
    return part->methodToString();
}

QVariant MethodHelper::getIcon(PartItem *part)
{
    // Иконка, либо пустой QVariant для Qt::DecorationRole:
    return part->getMethodIcon();
}

void MethodHelper::connectPartSignal(PartItem *part)
{
    // Каждая ячейка столбца Угол уведомляет об изменении вначале свой помощник:
    connect(part, &PartItem::methodChanged, this, &MethodHelper::findChangedIndex);
}
