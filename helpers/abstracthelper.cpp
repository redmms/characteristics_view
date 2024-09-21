#include "abstracthelper.h"

AbstractHelper::AbstractHelper(const QVector<PartItem*>& parts_,
                               const QVector<AbstractHelper*>& helpers_,
                               QString header_,
                               QObject *parent) :
    QObject{parent},
    parts(parts_),
    helpers(helpers_),
    header(header_)
{}

void AbstractHelper::setHeader(QString header_)
{
    header = header_;
}

QString AbstractHelper::getHeader()
{
    return header;
}

void AbstractHelper::findChangedIndex()
{
    // Определяем изменившуюся ячейку:
    PartItem* part = qobject_cast<PartItem*>(sender());

    // Находим индекс ячейки:
    // Такой подход не самый быстродейственный, но зато не требует лишнего
    // места и не зависит от добавления/удаления строк в таблице
    int i = parts.indexOf(part);
    int j = helpers.indexOf(this);

    // Отправляем сигнал с нужной сигнатурой представлению:
    QModelIndex idx = (qobject_cast<QAbstractItemModel*>(parent()))->
                      index(i, j);
    QVector<int> roles{int(Qt::DisplayRole)};
    emit dataChanged(idx, idx, roles);
}

