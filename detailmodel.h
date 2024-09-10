#pragma once
#include <QAbstractTableModel>
#include <QList>
#include "detailitem.h"
#include <QVector>
#include <list>
#include <vector>
#include "helpers/abstracthelper.h"

class Model : public QAbstractTableModel
{
    Q_OBJECT // should I place Q_OBJECT here or it is already in parent class?
private:
    std::vector<DetailItem*> details;
    const std::vector<AbstractHelper*> helpers;
    std::vector<QString> headers;
    const std::vector<QString> detail_signal_names;

public:
    explicit Model(int rows = 0, QObject *parent = nullptr);
    int rowCount(const QModelIndex& parent  = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void insertRow(int row, DetailItem* detail);
    bool removeRow(int row);
    void setHeaderData(int section, const QVariant &value);
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role) const override;

//    void setItem(int row, );
};
