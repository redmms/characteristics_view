#ifndef MASSHELPER_H
#define MASSHELPER_H

#include <QObject>
#include "abstracthelper.h"

class MassHelper : public QObject, public AbstractHelper
{
    Q_OBJECT
public:
    MassHelper(QObject* parent = nullptr);
    QVariant getString(DetailItem* detail) override;
    QVariant getIcon(DetailItem* detail) override;
};

#endif // MASSHELPER_H
