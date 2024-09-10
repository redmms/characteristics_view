#ifndef METHODHELPER_H
#define METHODHELPER_H

#include <QObject>
#include "abstracthelper.h"

class MethodHelper : public QObject, public AbstractHelper
{
    Q_OBJECT
public:
    explicit MethodHelper(QObject *parent = nullptr);
    QVariant getString(DetailItem* detail) override;
    QVariant getIcon(DetailItem* detail) override;

signals:

};

#endif // METHODHELPER_H
