#include "centerhelper.h"

CenterHelper::CenterHelper(QObject* parent)
{

}

QVariant CenterHelper::getString(DetailItem *detail)
{
    return detail->centerToString();
}

QVariant CenterHelper::getIcon(DetailItem *detail)
{
    return {};
}

