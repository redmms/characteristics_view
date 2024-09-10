#include "densityhelper.h"

QVariant DensityHelper::getString(DetailItem *detail)
{
    // Строка для Qt::DisplayRole:
    return detail->densityToString();
}

QVariant DensityHelper::getIcon(DetailItem *detail)
{
    // Иконка, либо пустой QVariant для Qt::DecorationRole:
    return {};
}

void DensityHelper::connectDetailSignal(DetailItem *detail)
{
    // Каждая ячейка столбца Угол уведомляет об изменении вначале свой хэлпер:
    connect(detail, &DetailItem::densityChanged, this, &DensityHelper::findChangedIndex);
}

