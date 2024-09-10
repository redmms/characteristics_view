#ifndef CENTERHELPER_H
#define CENTERHELPER_H

#include <QObject>
#include "abstracthelper.h"

class CenterHelper : public QObject, public AbstractHelper
{
    Q_OBJECT
public:
    CenterHelper(QObject* parent = nullptr);
    QVariant getString(DetailItem* detail) override;
    QVariant getIcon(DetailItem* detail) override;

signals:
};

#endif // CENTERHELPER_H
