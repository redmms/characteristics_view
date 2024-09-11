#include "abstracthelper.h"

AbstractHelper::AbstractHelper(const QVector<DetailItem *> &details_, const QVector<AbstractHelper *> &helpers_, QObject *parent) :
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
    // места и не зависит от добавления/удаления строк в таблице
    int i = details.indexOf(detail);
    int j = helpers.indexOf(this);

    // Отправляем сигнал с нужной сигнатурой представлению:
    QModelIndex idx = (qobject_cast<QAbstractItemModel*>(parent()))->
                      index(i, j);
    QVector<int> roles{int(Qt::DisplayRole)};
    emit dataChanged(idx, idx, roles);
}

