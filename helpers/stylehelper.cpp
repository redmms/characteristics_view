#include "stylehelper.h"

QVariant StyleHelper::getString(DetailItem *detail)
{
    // Строка для Qt::DisplayRole:
    return detail->materialStyleToString();
}

QVariant StyleHelper::getIcon(DetailItem *detail)
{
    // Иконка, либо пустой QVariant для Qt::DecorationRole:
    return QIcon(detail->getMaterialStyleIcon().pixmap(120, 75).copy(0,0,75,75).
                 scaled(30, 30));
}

void StyleHelper::connectDetailSignal(DetailItem *detail)
{
    // Каждая ячейка столбца Угол уведомляет об изменении вначале свой хэлпер:
    connect(detail, &DetailItem::materialStyleChanged, this, &StyleHelper::findChangedIndex);
}
