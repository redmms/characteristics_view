#include "methodhelper.h"

QVariant MethodHelper::getString(DetailItem *detail)
{
    // Строка для Qt::DisplayRole:
    return detail->methodToString();
}

QVariant MethodHelper::getIcon(DetailItem *detail)
{
    // Иконка, либо пустой QVariant для Qt::DecorationRole:
    return detail->getMethodIcon();
}

void MethodHelper::connectDetailSignal(DetailItem *detail)
{
    // Каждая ячейка столбца Угол уведомляет об изменении вначале свой хэлпер:
    connect(detail, &DetailItem::methodChanged, this, &MethodHelper::findChangedIndex);
}
