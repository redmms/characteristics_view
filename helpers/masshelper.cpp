#include "masshelper.h"

QVariant MassHelper::getString(PartItem *part)
{
    // Строка для Qt::DisplayRole:
    return part->massToString();
}

QVariant MassHelper::getIcon(PartItem *part)
{
    // Иконка, либо пустой QVariant для Qt::DecorationRole:
    Q_UNUSED(part)
    return {};
}

void MassHelper::connectPartSignal(PartItem *part)
{
    // Каждая ячейка столбца Угол уведомляет об изменении вначале свой помощник:
    connect(part, &PartItem::massChanged, this, &MassHelper::findChangedIndex);
}

