#include "stylehelper.h"

QVariant StyleHelper::getString(PartItem *part)
{
    // Строка для Qt::DisplayRole:
    return part->materialStyleToString();
}

QVariant StyleHelper::getIcon(PartItem *part)
{
    // Иконка, либо пустой QVariant для Qt::DecorationRole:
    return QIcon(part->getMaterialStyleIcon().pixmap(120, 75).copy(0,0,75,75).
                 scaled(30, 30));
}

void StyleHelper::connectPartSignal(PartItem *part)
{
    // Каждая ячейка столбца Угол уведомляет об изменении вначале свой хэлпер:
    connect(part, &PartItem::materialStyleChanged, this, &StyleHelper::findChangedIndex);
}
