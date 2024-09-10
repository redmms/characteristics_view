#include "anglehelper.h"

QVariant AngleHelper::getString(DetailItem *detail)
{
    return detail->materialAngleToString();
}

QVariant AngleHelper::getIcon(DetailItem *detail)
{
    return {};
}

void AngleHelper::connectDetailSignal(DetailItem *detail)
{
    connect(detail, &DetailItem::materialAngleChanged, this, &AngleHelper::findChangedIndex);
}



