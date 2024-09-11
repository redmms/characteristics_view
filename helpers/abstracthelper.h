#pragma once
#include "../partitem.h"
#include <QVariant>
#include <QObject>
#include <QAbstractItemModel>
#include <QModelIndex>

class AbstractHelper : public QObject
{
    Q_OBJECT
private:
    // Храним ссылки на контейнеры деталей и хэлперов, чтобы находить индексы
    // колонок и столбцов соответственно. Они нужны всем наследникам, поэтому
    // здесь.
    const QVector<PartItem*>& parts;
    const QVector<AbstractHelper*>& helpers;

public:
    // Конструктор:
    AbstractHelper(const QVector<PartItem*>& parts_,
                   const QVector<AbstractHelper*>& helpers_,
                   QObject *parent = nullptr);

    // Виртуальные методы:
    virtual QVariant getString(PartItem* part) = 0;
    virtual QVariant getIcon(PartItem* part) = 0;
    virtual void connectPartSignal(PartItem* part) = 0;

protected slots:
    // Слот для поиска индекса ячейки в рантайме и перенаправке сигнала
    // представлению c нужной сигнатурой:
    void findChangedIndex();

signals:
    // Сигнал с нужной сигнатурой:
    void dataChanged(const QModelIndex &top_left, const QModelIndex &bottom_right,
                     const QVector<int> &roles);
};
