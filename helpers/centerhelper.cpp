#include "centerhelper.h"

QVariant CenterHelper::getString(DetailItem *detail)
{
    // Строка для Qt::DisplayRole:
    return detail->centerToString();
}

QVariant CenterHelper::getIcon(DetailItem *detail)
{
    // Иконка, либо пустой QVariant для Qt::DecorationRole:
    return {};
}

void CenterHelper::connectDetailSignal(DetailItem *detail)
{
    // Каждая ячейка столбца Угол уведомляет об изменении вначале свой хэлпер:
    connect(detail, &DetailItem::centerChanged, this, &CenterHelper::findChangedIndex);
}

