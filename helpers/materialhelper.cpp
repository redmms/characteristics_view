#include "materialhelper.h"

QVariant MaterialHelper::getString(PartItem *part)
{
    // Строка для Qt::DisplayRole:
    return part->materialShortNameToString();
}

QVariant MaterialHelper::getIcon(PartItem *part)
{
    // Иконка, либо пустой QVariant для Qt::DecorationRole:
    return {};
}

void MaterialHelper::connectPartSignal(PartItem *part)
{
    // Каждая ячейка столбца Угол уведомляет об изменении вначале свой хэлпер:
    connect(part, &PartItem::materialNameChanged, this, &MaterialHelper::findChangedIndex);
}
