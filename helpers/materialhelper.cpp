#include "materialhelper.h"

MaterialHelper::MaterialHelper(QObject *parent)
    : QObject{parent}
{

}

QVariant MaterialHelper::getString(DetailItem *detail)
{
    return detail->materialShortNameToString();
}

QVariant MaterialHelper::getIcon(DetailItem *detail)
{
    return {};
}
