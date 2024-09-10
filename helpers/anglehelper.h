#ifndef ANGLEHELPER_H
#define ANGLEHELPER_H

#include <QObject>
#include "abstracthelper.h"

class AngleHelper : public QObject, public AbstractHelper
{
    Q_OBJECT
public:
    explicit AngleHelper(QObject *parent = nullptr);
    QVariant getString(DetailItem* detail) override;
    QVariant getIcon(DetailItem* detail) override;
signals:

};

#endif // ANGLEHELPER_H
