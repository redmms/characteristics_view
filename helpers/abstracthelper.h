#ifndef ABSTRACTHELPER_H
#define ABSTRACTHELPER_H
#include <QVariant>
#include "../detailitem.h"

class AbstractHelper
{
public:
    AbstractHelper() = default;
    virtual QVariant getString(DetailItem* detail) = 0;
    virtual QVariant getIcon(DetailItem* detail) = 0;
};

#endif // ABSTRACTHELPER_H
