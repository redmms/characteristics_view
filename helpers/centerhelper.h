#pragma once
#include "abstracthelper.h"

class CenterHelper : public AbstractHelper
{
    Q_OBJECT
public:
    // Конструктор:
    explicit CenterHelper(const QVector<PartItem*>& parts_,
                         const QVector<AbstractHelper*>& helpers_,
                         QString header_ = "",
                         QObject* parent = nullptr) :
        AbstractHelper(parts_, helpers_, header_, parent){}

    // Переопределенные методы для каждого столбца:
    QVariant getString(PartItem* part) override;
    QVariant getIcon(PartItem* part) override;
    void connectPartSignal(PartItem* part) override;
};