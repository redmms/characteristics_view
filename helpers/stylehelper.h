#ifndef STYLEHELPER_H
#define STYLEHELPER_H

#include <QObject>
#include "abstracthelper.h"

class StyleHelper : public QObject, public AbstractHelper
{
    Q_OBJECT
public:
    explicit StyleHelper(QObject *parent = nullptr);
    QVariant getString(DetailItem* detail) override;
    QVariant getIcon(DetailItem* detail) override;
signals:

};

#endif // STYLEHELPER_H
