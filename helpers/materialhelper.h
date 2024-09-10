#ifndef MATERIALHELPER_H
#define MATERIALHELPER_H

#include <QObject>
#include "abstracthelper.h"

class MaterialHelper : public QObject, public AbstractHelper
{
    Q_OBJECT
public:
    explicit MaterialHelper(QObject *parent = nullptr);
    QVariant getString(DetailItem* detail) override;
    QVariant getIcon(DetailItem* detail) override;
signals:

};

#endif // MATERIALHELPER_H
