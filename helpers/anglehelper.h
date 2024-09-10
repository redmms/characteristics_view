#ifndef ANGLEHELPER_H
#define ANGLEHELPER_H

#include "abstracthelper.h"

class AngleHelper : public AbstractHelper
{
    Q_OBJECT
public:
    explicit AngleHelper(const std::vector<DetailItem*>& details_ = {}, const std::vector<AbstractHelper*>& helpers_ = {}, QObject *parent = nullptr) :
        AbstractHelper(details_, helpers_, parent){}
    QVariant getString(DetailItem* detail) override;
    QVariant getIcon(DetailItem* detail) override;
    void connectDetailSignal(DetailItem* detail) override;

};

#endif // ANGLEHELPER_H
