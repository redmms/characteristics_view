#ifndef DENSITYHELPER_H
#define DENSITYHELPER_H

#include <QObject>
#include "abstracthelper.h"

class DensityHelper : public QObject, public AbstractHelper
{
    Q_OBJECT
public:
    DensityHelper(QObject* parent = nullptr);
    QVariant getString(DetailItem* detail) override;
    QVariant getIcon(DetailItem* detail) override;
};

#endif // DENSITYHELPER_H
