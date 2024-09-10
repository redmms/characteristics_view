#include "masshelper.h"

QVariant MassHelper::getString(DetailItem *detail)
{
    // Строка для Qt::DisplayRole:
    return detail->massToString();
}

QVariant MassHelper::getIcon(DetailItem *detail)
{
    // Иконка, либо пустой QVariant для Qt::DecorationRole:
    return {};
}

void MassHelper::connectDetailSignal(DetailItem *detail)
{
    // Каждая ячейка столбца Угол уведомляет об изменении вначале свой хэлпер:
    connect(detail, &DetailItem::massChanged, this, &MassHelper::findChangedIndex);
}

