#include "partmodel.h"
#include "material.h"
#include "helpers/anglehelper.h"
#include "helpers/centerhelper.h"
#include "helpers/densityhelper.h"
#include "helpers/masshelper.h"
#include "helpers/materialhelper.h"
#include "helpers/methodhelper.h"
#include "helpers/stylehelper.h"

PartModel::PartModel(int rows, QObject *parent) :
    parts{rows, {}},
    helpers{
        new MethodHelper(parts, helpers, this),
        new MassHelper(parts, helpers, this),
        new DensityHelper(parts, helpers, this),
        new CenterHelper(parts, helpers, this),
        new MaterialHelper(parts, helpers, this),
        new StyleHelper(parts, helpers, this),
        new AngleHelper(parts, helpers, this)
    },
    headers{
        "способ расчёта", // please, add translations for these phrazes
        "масса",
        "плотность",
        "центр масс",
        "материал",
        "стиль штриховки",
        "угол штриховки"
    }
{}

bool PartModel::isValidRow(int row) const
{
    // Проверка индекса строки:
    return row >= 0 && row < parts.size();
}

bool PartModel::isValidColumn(int column) const
{
    // Проверка индекса столбца:
    return column >= 0 && column < helpers.size();
}

int PartModel::rowCount(const QModelIndex& parent) const
{
    // Количество строк:
    Q_UNUSED(parent)
    return parts.size();
}

int PartModel::columnCount(const QModelIndex& parent) const
{
    // Количество колонок:
    Q_UNUSED(parent)
    return helpers.size();
}

QVariant PartModel::data(const QModelIndex &index, int role) const
{
    // Метод для отображения ячеек в представлении

    // Проверка индекса:
    if (!index.isValid() || !isValidRow(index.row()) ||
        !isValidColumn(index.column())){
        return {};
    }

    int i = index.row();
    int j = index.column();

    // Свой хэлпер для каждой колонки, своя деталь для каждой строки:
    switch (role) {
    case Qt::DisplayRole:
        return helpers[j]->getString(parts[i]);
    case Qt::ToolTipRole:
        return headers[j];
    case Qt::DecorationRole:
        return helpers[j]->getIcon(parts[i]);
    default:
        return {};
    }
}

bool PartModel::insertRow(int row, PartItem *part) // should we
// check the pointer before adding, or when using?
{
    // Метод вставки строки
    // Проверяем аргументы:
    if (row < 0 || !part){
        return false;
    }

    // Сразу же забираем владение объектом:
    part->setParent(this);

    // Подключаем сигналы изменения полей детали, они же ячейки:
    for (auto helper : helpers){
        helper->connectPartSignal(part);
        connect(helper, &AbstractHelper::dataChanged, this, &QAbstractItemModel::dataChanged); // should be abstract or not?
    }

    // Подключаем сигнал удаления детали:
    connect(part, &PartItem::destroyed, this, &PartModel::partDeleted);

    // Вставлем строки-детали и уведомляем представление
    beginInsertRows(QModelIndex(), row, row); // "Уведомление"
    parts.insert(row, part);
    endInsertRows();

    return true;
}

bool PartModel::appendRow(PartItem *part)
{
    int row = parts.size();
    insertRow(row, part);
}

bool PartModel::removeRow(int row)
{
    // Метод удаления строки
    // Проверяем аргументы:
    if (!isValidRow(row)){
        return false;
    }

    // Удаляем строки-детали и уведомляем представление
    beginRemoveRows(QModelIndex(), row, row);
    parts.remove(row);
    endRemoveRows();
    return true;
}

bool PartModel::setHeaderData(int section, const QVariant &value)
{
    // Сэттер для заголовка таблицы
    // Проверяем аргументы:
    if (!isValidColumn(section)){
        return false;
    }

    // Меняем заголовки:
    headers[section] = value.toString();
    emit headerDataChanged(Qt::Horizontal, section, section);
    return true;
}

QVariant PartModel::headerData(int section, Qt::Orientation orientation,
                                 int role) const
{
    // Метод для отображения ячеек заголовка в представлении
    // Проверяем аргументы:
    if (!isValidColumn(section)){
        return {};
    }

    // Возвращаем заголовок
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole){
        return headers.at(section);
    }
    else{
        return {};
    }
}

void PartModel::partDeleted(QObject *object)
{
    // Очищаем строку из-под удаленной по указателю детали:
//    PartItem* part = qobject_cast<PartItem*>(object);  // RV - should we check that или это лишнее?

    removeRow(parts.indexOf((PartItem*)object)); // TODO

}


