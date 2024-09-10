#include "detailmodel.h"
#include "enums.h"
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

int DetailModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return details.size();
}

int DetailModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return helpers.size();
}

QVariant DetailModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()){
        return {}; // add row check
    }

    int i = index.row();
    int j = index.column(); // TODO: check index for validity

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

void DetailModel::insertRow(int row, DetailItem *detail) // should we
// check the pointer before adding, or when using?
{
    for (auto helper : helpers){
        helper->connectDetailSignal(detail);
        connect(helper, &AbstractHelper::dataChanged, this, &QAbstractItemModel::dataChanged); // should be abstract or not?
    }
    beginInsertRows(QModelIndex(), row, row); // by-one error?
    details.insert(details.begin() + row, detail);
    endInsertRows();
}

bool DetailModel::removeRow(int row)
{
    if (row >= 0 && row < details.size()){
        beginRemoveRows(QModelIndex(), row, row);
        details.erase(details.begin() + row);
        endRemoveRows();
        return true;
    }
    else{
        return false;
    }
}

void DetailModel::setHeaderData(int section, const QVariant &value)
{  // Можно сделать упрощенный вариант чисто для горизонтальных строковых заголовков?
    // Если желательно полный вариант, то как?
    headers[section] = value.toString();
    emit headerDataChanged(Qt::Horizontal, section, section);
}

QVariant DetailModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole){
        return headers.at(section);
    }
    else{
        return QVariant();
    }
}



