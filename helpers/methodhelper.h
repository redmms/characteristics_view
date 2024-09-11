#pragma once
#include "abstracthelper.h"

class MethodHelper : public AbstractHelper
{
    Q_OBJECT
public:
    // Конструктор:
    explicit MethodHelper(const QVector<DetailItem *> &details_, const QVector<AbstractHelper *> &helpers_, QObject *parent = nullptr) :
        AbstractHelper( details_, helpers_, parent){}

    // Переопределенные методы для каждого столбца:
    QVariant getString(DetailItem* detail) override;
    QVariant getIcon(DetailItem* detail) override;
    void connectDetailSignal(DetailItem* detail) override;
};
