#include "methodhelper.h"



QVariant MethodHelper::getString(DetailItem *detail)
{
    return detail->methodToString();
}

QVariant MethodHelper::getIcon(DetailItem *detail)
{
    return detail->getMethodIcon();
}

void MethodHelper::connectDetailSignal(DetailItem *detail)
{
    connect(detail, &DetailItem::methodChanged, this, &MethodHelper::findChangedIndex);

}
