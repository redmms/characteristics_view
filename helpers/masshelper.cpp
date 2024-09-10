#include "masshelper.h"

MassHelper::MassHelper(QObject* parent)
{

}

QVariant MassHelper::getString(DetailItem *detail)
{
    return detail->massToString();
}

QVariant MassHelper::getIcon(DetailItem *detail)
{
    return {};
}

