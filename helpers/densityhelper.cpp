#include "densityhelper.h"

QVariant DensityHelper::getString(PartItem *part)
{
    // Строка для Qt::DisplayRole:
    return part->densityToString();
}

QVariant DensityHelper::getIcon(PartItem *part)
{
    // Иконка, либо пустой QVariant для Qt::DecorationRole:
    Q_UNUSED(part)
    return {};
}

void DensityHelper::connectPartSignal(PartItem *part)
{
    // Каждая ячейка столбца Угол уведомляет об изменении вначале свой помощник:
    connect(part, &PartItem::densityChanged, this, &DensityHelper::findChangedIndex);
}

