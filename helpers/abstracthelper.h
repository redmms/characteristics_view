#pragma once
#include "../detailitem.h"
#include <QVariant>
#include <QObject>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <functional>

class AbstractHelper : public QObject
{
    Q_OBJECT
private:
    // Храним ссылки на контейнеры деталей и хэлперов, чтобы находить индексы
    // колонок и столбцов соответственно. Они нужны всем наследникам, поэтому
    // здесь.
    const std::vector<DetailItem*>& details;
    const std::vector<AbstractHelper*>& helpers;

public:
    // Конструктор:
    AbstractHelper(const std::vector<DetailItem*>& details_,
                   const std::vector<AbstractHelper*>& helpers_,
                   QObject *parent = nullptr);

    // Виртуальные методы:
    virtual QVariant getString(DetailItem* detail) = 0;
    virtual QVariant getIcon(DetailItem* detail) = 0;
    virtual void connectDetailSignal(DetailItem* detail) = 0;

protected slots:
    // Слот для поиска индекса ячейки в рантайме и перенаправке сигнала
    // представлению c нужной сигнатурой:
    void findChangedIndex();

signals:
    // Сигнал с нужной сигнатурой:
    void dataChanged(const QModelIndex &top_left, const QModelIndex &bottom_right,
                     const QVector<int> &roles);
};
