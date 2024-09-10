#include "densityhelper.h"

DensityHelper::DensityHelper(QObject* parent)
{

}

QVariant DensityHelper::getString(DetailItem *detail)
{
    return detail->densityToString();
}

QVariant DensityHelper::getIcon(DetailItem *detail)
{
    return {};
}

