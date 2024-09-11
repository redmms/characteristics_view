#include "centerhelper.h"

QVariant CenterHelper::getString(PartItem *part)
{
    // Строка для Qt::DisplayRole:
    return part->centerToString();
}

QVariant CenterHelper::getIcon(PartItem *part)
{
    // Иконка, либо пустой QVariant для Qt::DecorationRole:
    return {};
}

void CenterHelper::connectPartSignal(PartItem *part)
{
    // Каждая ячейка столбца Угол уведомляет об изменении вначале свой хэлпер:
    connect(part, &PartItem::centerChanged, this, &CenterHelper::findChangedIndex);
}

