#ifndef DENSITYHELPER_H
#define DENSITYHELPER_H

#include "abstracthelper.h"

class DensityHelper : public AbstractHelper
{
    Q_OBJECT
public:
    DensityHelper(const std::vector<DetailItem *> &details_, const std::vector<AbstractHelper *> &helpers_, QObject *parent = nullptr) :
        AbstractHelper( details_, helpers_, parent){}
    QVariant getString(DetailItem* detail) override;
    QVariant getIcon(DetailItem* detail) override;
    void connectDetailSignal(DetailItem* detail) override;


};

#endif // DENSITYHELPER_H
