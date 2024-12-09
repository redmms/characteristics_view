#include "structmodel.h"
#include <QPointer>
#include <QDebug>

PartModel::PartModel(int rows, int columns, QObject *parent) :
    QAbstractTableModel(parent),
    parts{rows, {}},
    headers{columns, ""},
    column_count(columns)
{}

// Проверка индекса строки:
bool PartModel::isValidAccessRow(int row) const
{
    return row >= 0 && row < rowCount();
}

// Проверка индекса строки:
bool PartModel::isValidInsertRow(int row) const
{
    return row >= 0 && row <= rowCount();
}

// Проверка индекса столбца:
bool PartModel::isValidColumn(int column) const
{
    return column >= 0 && column < columnCount();
}

bool PartModel::isValidItem(StructItem *item) const
{
    return item && item->getStructureSize() == columnCount();
}

// Количество строк:
int PartModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return parts.size();
}

// Количество колонок:
int PartModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return column_count;
}

// Метод для отображения ячеек в представлении
QVariant PartModel::data(const QModelIndex &index, int role) const
{ 
    QVariant ret = {};
    if(index.isValid() && isValidAccessRow(index.row()) &&
        isValidColumn(index.column())){  // Проверка индекса
        // Инициализация локальных переменных:
        int i = index.row();
        int j = index.column();

        // Обработка ролей:
        switch (role) {
        case Qt::DisplayRole:
            ret = parts[i]->getString(j);
            break;
        case Qt::ToolTipRole:
            ret = headers[j];
            break;
        case Qt::DecorationRole:
            ret = parts[i]->getIcon(j);
            break;
        default:
            ret = {};
            break;
        }
    }
    return ret;
}

// Метод вставки строки
bool PartModel::insertRow(int row, StructItem* part)
{
    bool success = false;
    if (isValidInsertRow(row) && isValidItem(part)){  // Проверяем аргументы:
        // Сразу же забираем владение объектом:
        part->setParent(this);

        // Подключаем сигналы изменения и удаления полей детали, они же ячейки:
        connect(part, &StructItem::changed,
                this, &PartModel::findChangedIndex);
        connect(part, &StructItem::destroyed, this, &PartModel::partDeleted);

        // Вставлем строки-детали и уведомляем представление
        beginInsertRows(QModelIndex(), row, row); // "Уведомление"
        parts.insert(row, part);
        endInsertRows();

        success = true;
    }
    return success;
}

// Метод для удобства добавления в конец. Все проверки в insertRow
void PartModel::appendRow(StructItem* part)
{
    int row = parts.size();
    bool success = insertRow(row, part);
    if (!success){
        qDebug() << "Appending failed";
    }
}

// Метод удаления строки
bool PartModel::removeRow(int row)
{
    bool success = false;
    if (isValidAccessRow(row)){ // Проверяем аргументы:
        // Удаляем строки-детали и уведомляем представление
        beginRemoveRows(QModelIndex(), row, row);
        QPointer<StructItem> to_delete = parts[row];
        if (to_delete){
            disconnect(to_delete, &StructItem::destroyed, this, &PartModel::partDeleted);
            to_delete->deleteLater();
        }
        parts.remove(row);
        endRemoveRows();
        success = true;
    }
    return success;
}

// Сэттер для заголовка таблицы
bool PartModel::setHeaderData(int column, const QVariant &value)
{
    bool success = false;
    if (isValidColumn(column)){  // Проверяем аргументы
        // Меняем заголовки:
        headers[column] = value.toString();
        emit headerDataChanged(Qt::Horizontal, column, column);
    }
    return success;
}

// Метод для отображения ячеек заголовка в представлении
QVariant PartModel::headerData(int column, Qt::Orientation orientation,
                                 int role) const
{
    QVariant ret = {};
    if (isValidColumn(column) &&  // Проверяем аргументы
        orientation == Qt::Horizontal &&
        role == Qt::DisplayRole)
    {
        // Получаем заголовок
        ret = headers[column];
    }
    return ret;
}

// Получение указателя на деталь, модель позволяет работать с деталями по указателю
StructItem* PartModel::getPart(int row)
{
    StructItem* ret = nullptr;
    if (isValidAccessRow(row)){
        ret = parts[row];
    }
    return ret;
}

// Очищение строки из-под удаленной по указателю детали:
void PartModel::partDeleted(QObject *object)
{
    bool success = removeRow(parts.indexOf((StructItem*)object));  // Здесь нам не важна валидность
    // указателя, поэтому используем C-style каст, указатель дополнительно
    // проверяется в removeRow();
    if (!success){
        qDebug() << "Couldn't remove a row in partDeleted slot";
    }
}

void PartModel::findChangedIndex(int column)
{
    // Определяем изменившуюся ячейку:
    StructItem* part = qobject_cast<StructItem*>(sender());
    if (!part){
        qDebug() << "qobject_cast<PartItem*>(sender()) failed";
    }

    // Находим индекс ячейки:
    // Такой подход не самый быстродейственный, но зато не требует лишнего
    // места и не зависит от добавления/удаления строк в таблице
    int i = parts.indexOf(part);
    int j = column;

    // Отправляем сигнал с нужной сигнатурой представлению:
    QModelIndex idx = (qobject_cast<QAbstractItemModel*>(parent()))->
                      index(i, j);
    QVector<int> roles{static_cast<int>(Qt::DisplayRole)};
    emit dataChanged(idx, idx, roles);
}
