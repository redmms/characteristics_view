#include "anglehelper.h"

AngleHelper::AngleHelper(QObject *parent)
    : QObject{parent}
{

}

QVariant AngleHelper::getString(DetailItem *detail)
{
    return detail->materialAngleToString();
}

QVariant AngleHelper::getIcon(DetailItem *detail)
{
    return {};
}
