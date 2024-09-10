#pragma once
#include <QSortFilterProxyModel>

class DetailSortFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    DetailSortFilterModel();
protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override{};
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override{};
};
