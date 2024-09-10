#include "stylehelper.h"


QVariant StyleHelper::getString(DetailItem *detail)
{
    return detail->materialStyleToString();
}

QVariant StyleHelper::getIcon(DetailItem *detail)
{
    return QIcon(detail->getMaterialStyleIcon().pixmap(120, 75).copy(0,0,75,75).
                 scaled(30, 30));
}

void StyleHelper::connectDetailSignal(DetailItem *detail)
{
    connect(detail, &DetailItem::materialStyleChanged, this, &StyleHelper::findChangedIndex);

}
