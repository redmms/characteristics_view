#include "materialhelper.h"

QVariant MaterialHelper::getString(DetailItem *detail)
{
    // Строка для Qt::DisplayRole:
    return detail->materialShortNameToString();
}

QVariant MaterialHelper::getIcon(DetailItem *detail)
{
    // Иконка, либо пустой QVariant для Qt::DecorationRole:
    return {};
}

void MaterialHelper::connectDetailSignal(DetailItem *detail)
{
    // Каждая ячейка столбца Угол уведомляет об изменении вначале свой хэлпер:
    connect(detail, &DetailItem::materialNameChanged, this, &MaterialHelper::findChangedIndex);
}
