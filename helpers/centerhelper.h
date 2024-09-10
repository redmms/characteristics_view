#ifndef CENTERHELPER_H
#define CENTERHELPER_H

#include "abstracthelper.h"

class CenterHelper : public AbstractHelper
{
    Q_OBJECT
public:
    CenterHelper(const std::vector<DetailItem *> &details_ , const std::vector<AbstractHelper *> &helpers_, QObject* parent = nullptr) :
        AbstractHelper(details_, helpers_, parent){}
    QVariant getString(DetailItem* detail) override;
    QVariant getIcon(DetailItem* detail) override;
    void connectDetailSignal(DetailItem* detail) override;

};

#endif // CENTERHELPER_H
