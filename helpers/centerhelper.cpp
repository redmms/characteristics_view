#include "centerhelper.h"



QVariant CenterHelper::getString(DetailItem *detail)
{
    return detail->centerToString();
}

QVariant CenterHelper::getIcon(DetailItem *detail)
{
    return {};
}

void CenterHelper::connectDetailSignal(DetailItem *detail)
{
    connect(detail, &DetailItem::centerChanged, this, &CenterHelper::findChangedIndex);
}

