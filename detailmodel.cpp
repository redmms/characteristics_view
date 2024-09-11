#include "detailmodel.h"
#include "material.h"
#include "helpers/anglehelper.h"
#include "helpers/centerhelper.h"
#include "helpers/densityhelper.h"
#include "helpers/masshelper.h"
#include "helpers/materialhelper.h"
#include "helpers/methodhelper.h"
#include "helpers/stylehelper.h"

DetailModel::DetailModel(int rows, QObject *parent) :
    details{rows, {}},
    helpers{
        new MethodHelper(details, helpers, this),
        new MassHelper(details, helpers, this),
        new DensityHelper(details, helpers, this),
        new CenterHelper(details, helpers, this),
        new MaterialHelper(details, helpers, this),
        new StyleHelper(details, helpers, this),
        new AngleHelper(details, helpers, this)
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

bool DetailModel::isValidRow(int row) const
{
    // Проверка индекса строки:
    return row >= 0 && row < details.size();
}

bool DetailModel::isValidColumn(int column) const
{
    // Проверка индекса столбца:
    return column >= 0 && column < helpers.size();
}

int DetailModel::rowCount(const QModelIndex& parent) const
{
    // Количество строк:
    Q_UNUSED(parent)
    return details.size();
}

int DetailModel::columnCount(const QModelIndex& parent) const
{
    // Количество колонок:
    Q_UNUSED(parent)
    return helpers.size();
}

QVariant DetailModel::data(const QModelIndex &index, int role) const
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
        return helpers[j]->getString(details[i]);
    case Qt::ToolTipRole:
        return headers[j];
    case Qt::DecorationRole:
        return helpers[j]->getIcon(details[i]);
    default:
        return {};
    }
}

bool DetailModel::insertRow(int row, DetailItem *detail) // should we
// check the pointer before adding, or when using?
{
    // Метод вставки строки
    // Проверяем аргументы:
    if (row < 0 || !detail){
        return false;
    }

    // Сразу же забираем владение объектом:
    detail->setParent(this);

    // Подключаем сигналы изменения полей детали, они же ячейки:
    for (auto helper : helpers){
        helper->connectDetailSignal(detail);
        connect(helper, &AbstractHelper::dataChanged, this, &QAbstractItemModel::dataChanged); // should be abstract or not?
    }

    // Подключаем сигнал удаления детали:
    connect(detail, &DetailItem::destroyed, this, &DetailModel::detailDeleted);

    // Вставлем строки-детали и уведомляем представление
    beginInsertRows(QModelIndex(), row, row); // "Уведомление"
    details.insert(row, detail);
    endInsertRows();

    return true;
}

bool DetailModel::removeRow(int row)
{
    // Метод удаления строки
    // Проверяем аргументы:
    if (!isValidRow(row)){
        return false;
    }

    // Удаляем строки-детали и уведомляем представление
    beginRemoveRows(QModelIndex(), row, row);
    details.remove(row);
    endRemoveRows();
    return true;
}

bool DetailModel::setHeaderData(int section, const QVariant &value)
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

QVariant DetailModel::headerData(int section, Qt::Orientation orientation,
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

void DetailModel::detailDeleted(QObject *object)
{
    // Очищаем строку из-под удаленной по указателю детали:
//    DetailItem* detail = qobject_cast<DetailItem*>(object);  // RV - should we check that или это лишнее?

    removeRow(details.indexOf((DetailItem*)object)); // TODO

}



