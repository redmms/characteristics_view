#ifndef MATERIALHELPER_H
#define MATERIALHELPER_H

#include "abstracthelper.h"

class MaterialHelper : public AbstractHelper
{
    Q_OBJECT
public:
    explicit MaterialHelper(const std::vector<DetailItem *> &details_, const std::vector<AbstractHelper *> &helpers_, QObject *parent = nullptr) :
        AbstractHelper( details_, helpers_, parent){}
    QVariant getString(DetailItem* detail) override;
    QVariant getIcon(DetailItem* detail) override;
    void connectDetailSignal(DetailItem* detail) override;

};

#endif // MATERIALHELPER_H
