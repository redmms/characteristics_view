#include "stylehelper.h"

StyleHelper::StyleHelper(QObject *parent)
    : QObject{parent}
{

}

QVariant StyleHelper::getString(DetailItem *detail)
{
    return detail->materialStyleToString();
}

QVariant StyleHelper::getIcon(DetailItem *detail)
{
    return QIcon(detail->getMaterialStyleIcon().pixmap(120, 75).copy(0,0,75,75).
                 scaled(30, 30));
}
