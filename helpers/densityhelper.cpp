#include "densityhelper.h"



QVariant DensityHelper::getString(DetailItem *detail)
{
    return detail->densityToString();
}

QVariant DensityHelper::getIcon(DetailItem *detail)
{
    return {};
}

void DensityHelper::connectDetailSignal(DetailItem *detail)
{
    connect(detail, &DetailItem::densityChanged, this, &DensityHelper::findChangedIndex);

}

