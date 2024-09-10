#include "masshelper.h"



QVariant MassHelper::getString(DetailItem *detail)
{
    return detail->massToString();
}

QVariant MassHelper::getIcon(DetailItem *detail)
{
    return {};
}

void MassHelper::connectDetailSignal(DetailItem *detail)
{
    connect(detail, &DetailItem::massChanged, this, &MassHelper::findChangedIndex);

}

