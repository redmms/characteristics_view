#ifndef STYLEHELPER_H
#define STYLEHELPER_H

#include "abstracthelper.h"

class StyleHelper : public AbstractHelper
{
    Q_OBJECT
public:
    explicit StyleHelper(const std::vector<DetailItem *> &details_, const std::vector<AbstractHelper *> &helpers_, QObject *parent = nullptr) :
        AbstractHelper( details_, helpers_, parent){}
    QVariant getString(DetailItem* detail) override;
    QVariant getIcon(DetailItem* detail) override;
    void connectDetailSignal(DetailItem* detail) override;


};

#endif // STYLEHELPER_H
