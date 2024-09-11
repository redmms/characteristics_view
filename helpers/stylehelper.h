#pragma once
#include "abstracthelper.h"

class StyleHelper : public AbstractHelper
{
    Q_OBJECT
public:
    // Конструктор:
    explicit StyleHelper(const QVector<PartItem *> &parts_, const QVector<AbstractHelper *> &helpers_, QObject *parent = nullptr) :
        AbstractHelper( parts_, helpers_, parent){}

    // Переопределенные методы для каждого столбца:
    QVariant getString(PartItem* part) override;
    QVariant getIcon(PartItem* part) override;
    void connectPartSignal(PartItem* part) override;
};
