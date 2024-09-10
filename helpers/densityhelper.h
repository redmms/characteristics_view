#pragma once
#include "abstracthelper.h"

class DensityHelper : public AbstractHelper
{
    Q_OBJECT
public:
    // Конструктор:
    DensityHelper(const std::vector<DetailItem *> &details_, const std::vector<AbstractHelper *> &helpers_, QObject *parent = nullptr) :
        AbstractHelper( details_, helpers_, parent){}

    // Переопределенные методы для каждого столбца:
    QVariant getString(DetailItem* detail) override;
    QVariant getIcon(DetailItem* detail) override;
    void connectDetailSignal(DetailItem* detail) override;
};
