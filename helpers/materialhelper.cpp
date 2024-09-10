#include "materialhelper.h"



QVariant MaterialHelper::getString(DetailItem *detail)
{
    return detail->materialShortNameToString();
}

QVariant MaterialHelper::getIcon(DetailItem *detail)
{
    return {};
}

void MaterialHelper::connectDetailSignal(DetailItem *detail)
{
    connect(detail, &DetailItem::materialNameChanged, this, &MaterialHelper::findChangedIndex);
}
