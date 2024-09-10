#include "methodhelper.h"

MethodHelper::MethodHelper(QObject *parent)
    : QObject{parent}
{

}

QVariant MethodHelper::getString(DetailItem *detail)
{
    return detail->methodToString();
}

QVariant MethodHelper::getIcon(DetailItem *detail)
{
    return detail->getMethodIcon();
}
