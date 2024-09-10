#ifndef MASSHELPER_H
#define MASSHELPER_H

#include "abstracthelper.h"

class MassHelper : public AbstractHelper
{
    Q_OBJECT
public:
    MassHelper( const std::vector<DetailItem *> &details_, const std::vector<AbstractHelper *> &helpers_, QObject *parent = nullptr) :
        AbstractHelper( details_, helpers_, parent){}
    QVariant getString(DetailItem* detail) override;
    QVariant getIcon(DetailItem* detail) override;
    void connectDetailSignal(DetailItem* detail) override;


};

#endif // MASSHELPER_H
