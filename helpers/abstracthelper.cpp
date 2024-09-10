#include "abstracthelper.h"

AbstractHelper::AbstractHelper(const std::vector<DetailItem *> &details_, const std::vector<AbstractHelper *> &helpers_, QObject *parent) :
    QObject{parent},
    details(details_),
    helpers(helpers_)
{}

void AbstractHelper::findChangedIndex()
{
    // Определяем изменившуюся ячейку:
    DetailItem* detail = qobject_cast<DetailItem*>(sender());

    // Находим индекс ячейки:
    // Такой подход не самый быстродейственный, но зато не требует лишнего
    // места под второй контейнер с деталями, либо под индексы для каждой
    // детали.
    int i = std::distance(details.begin(), std::find(details.begin(),
                                                     details.end(), detail)); // not efficient
    int j = std::distance(helpers.begin(), std::find(helpers.begin(),
                                                     helpers.end(), this));

    // Отправляем сигнал с нужной сигнатурой представлению:
    QModelIndex idx = (qobject_cast<QAbstractItemModel*>(parent()))->
                      index(i, j);
    QVector<int> roles{int(Qt::DisplayRole)};
    emit dataChanged(idx, idx, roles);
}

