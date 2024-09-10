#ifndef METHODHELPER_H
#define METHODHELPER_H

#include "abstracthelper.h"

class MethodHelper : public AbstractHelper
{
    Q_OBJECT
public:
    explicit MethodHelper(const std::vector<DetailItem *> &details_, const std::vector<AbstractHelper *> &helpers_, QObject *parent = nullptr) :
        AbstractHelper( details_, helpers_, parent){}
    QVariant getString(DetailItem* detail) override;
    QVariant getIcon(DetailItem* detail) override;
    void connectDetailSignal(DetailItem* detail) override;


};

#endif // METHODHELPER_H
