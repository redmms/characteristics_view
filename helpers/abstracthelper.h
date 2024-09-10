#ifndef ABSTRACTHELPER_H
#define ABSTRACTHELPER_H
#include <QVariant>
#include "../detailitem.h"
#include <functional>
#include <QObject>
#include <QAbstractItemModel>
#include <QModelIndex>

class AbstractHelper : public QObject
{
    Q_OBJECT
    const std::vector<DetailItem*>& details;
    const std::vector<AbstractHelper*>& helpers;

public:
    AbstractHelper(const std::vector<DetailItem*>& details_, const std::vector<AbstractHelper*>& helpers_, QObject *parent = nullptr) :
        QObject{parent},
        details(details_),
        helpers(helpers_)
    {}
    virtual QVariant getString(DetailItem* detail) = 0;
    virtual QVariant getIcon(DetailItem* detail) = 0;
    virtual void connectDetailSignal(DetailItem* detail) = 0;

protected slots:
    virtual void findChangedIndex()
    {
        DetailItem* detail = (DetailItem*) sender();
        int i = std::distance(details.begin(), std::find(details.begin(),
                                                         details.end(), detail)); // not efficient
        int j = std::distance(helpers.begin(), std::find(helpers.begin(),
                                                         helpers.end(), this));

        QModelIndex idx = ((QAbstractItemModel*) parent())->index(i, j);
        QVector<int> roles{int(Qt::DisplayRole)};
        emit dataChanged(idx, idx, roles);
    }
    // or maybe it should be bool?
signals:
    virtual void dataChanged(const QModelIndex &top_left, const QModelIndex &bottom_right, const QVector<int> &roles); // is it OK to make signal virtual?
    // or it will slow it down
};

#endif // ABSTRACTHELPER_H
