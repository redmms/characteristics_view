#include "partmodel.h"
#include "helpers/anglehelper.h"
#include "helpers/centerhelper.h"
#include "helpers/densityhelper.h"
#include "helpers/masshelper.h"
#include "helpers/materialhelper.h"
#include "helpers/methodhelper.h"
#include "helpers/stylehelper.h"
#include <QPointer>
#include <QDebug>

PartModel::PartModel(int rows, QObject *parent) :
    QAbstractTableModel(parent),
    parts{rows, {}},
    helpers{
        new MethodHelper(parts, helpers, "способ расчёта", this),
        new MassHelper(parts, helpers, "масса", this),
        new DensityHelper(parts, helpers, "плотность", this),
        new CenterHelper(parts, helpers, "центр масс", this),
        new MaterialHelper(parts, helpers, "материал", this),
        new StyleHelper(parts, helpers, "стиль штриховки", this),
        new AngleHelper(parts, helpers, "угол штриховки", this)
    }
{}

// Проверка индекса строки:
bool PartModel::isValidAccessRow(int row) const
{
    return row >= 0 && row < parts.size();
}

// Проверка индекса строки:
bool PartModel::isValidInsertRow(int row) const
{
    return row >= 0 && row <= parts.size();
}

// Проверка индекса столбца:
bool PartModel::isValidColumn(int column) const
{
    return column >= 0 && column < helpers.size();
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
    return helpers.size();
}

// Метод для отображения ячеек в представлении
QVariant PartModel::data(const QModelIndex &index, int role) const
{ 
    QVariant ret = {};
    if(index.isValid() && isValidAccessRow(index.row()) &&
        isValidColumn(index.column())){  // Проверка индекса:
        int i = index.row();
        int j = index.column();

        // Свой помощник для каждого столбца, своя деталь для каждой строки:
        switch (role) {
        case Qt::DisplayRole:
            ret = helpers[j]->getString(parts[i]);
            break;
        case Qt::ToolTipRole:
            ret = helpers[j]->getHeader();
            break;
        case Qt::DecorationRole:
            ret = helpers[j]->getIcon(parts[i]);
            break;
        default:
            ret = {};
            break;
        }
    }
    return ret;
}

// Метод вставки строки
bool PartModel::insertRow(int row, PartItem *part)
{
    bool success = false;
    if (isValidInsertRow(row) && part){  // Проверяем аргументы:
        // Сразу же забираем владение объектом:
        part->setParent(this);

        // Подключаем сигналы изменения полей детали, они же ячейки:
        for (auto helper : helpers){
            helper->connectPartSignal(part);
            connect(helper, &AbstractHelper::dataChanged,
                    this, &QAbstractItemModel::dataChanged);
        }

        // Подключаем сигнал удаления детали:
        connect(part, &PartItem::destroyed, this, &PartModel::partDeleted);

        // Вставлем строки-детали и уведомляем представление
        beginInsertRows(QModelIndex(), row, row); // "Уведомление"
        parts.insert(row, part);
        endInsertRows();

        success = true;
    }
    return success;
}

// Метод для удобства добавления в конец. Все проверки в insertRow
void PartModel::appendRow(PartItem *part)
{
    int row = parts.size();
    bool success = insertRow(row, part);
    if (!success){
        qDebug() << "appending failed";
    }
}

// Метод удаления строки
bool PartModel::removeRow(int row)
{
    bool success = false;
    if (isValidAccessRow(row)){ // Проверяем аргументы:
        // Удаляем строки-детали и уведомляем представление
        beginRemoveRows(QModelIndex(), row, row);
        QPointer<PartItem> to_delete = parts[row];
        if (to_delete){
            disconnect(to_delete, &PartItem::destroyed, this, &PartModel::partDeleted);
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
        helpers[column]->setHeader(value.toString());
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
        ret = helpers[column]->getHeader();
    }
    return ret;
}

// Очищение строки из-под удаленной по указателю детали:
void PartModel::partDeleted(QObject *object)
{
    bool success = removeRow(parts.indexOf((PartItem*)object));  // Здесь нам не важна валидность
    // указателя, поэтому используем C-style каст, указатель дополнительно
    // проверяется в removeRow();
    if (!success){
        qDebug() << "Couldn't remove a row in partDeleted slot";
    }
}
