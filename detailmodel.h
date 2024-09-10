#pragma once
#include "detailitem.h"
#include "helpers/abstracthelper.h"
#include <QAbstractTableModel>
#include <QList>
#include <QVector>
#include <list>
#include <vector>

class DetailModel : public QAbstractTableModel
{
    Q_OBJECT
private:
    // Приватные поля:
    std::vector<DetailItem*> details;
    const std::vector<AbstractHelper*> helpers;
    std::vector<QString> headers;
    const std::vector<void (DetailItem::*)()> detail_signal_names;

public:
    // Конструктор:
    explicit DetailModel(int rows = 0, QObject *parent = nullptr);

    // Публичные методы, rowCount, columnCount, data - обязательны для
    // представления:
    int rowCount(const QModelIndex& parent  = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void insertRow(int row, DetailItem* detail);
    bool removeRow(int row);
    void setHeaderData(int section, const QVariant &value);
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role) const override;
};
