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

Model::Model(int rows, QObject *parent) :
    details{rows, {}},
    helpers{
        new MethodHelper(this),
        new MassHelper(this),
        new DensityHelper(this),
        new CenterHelper(this),
        new MaterialHelper(this),
        new StyleHelper(this),
        new AngleHelper(this)
    },
    headers{
        "способ расчёта", // please, add translations for these phrazes
        "масса",
        "плотность",
        "центр масс",
        "материал",
        "стиль штриховки",
        "угол штриховки"
    },
    detail_signal_names{
        "methodChanged",
        "massChanged",
        "densityChanged",
        "centerChanged",
        "materialNameChanged",
        "materialStyleChanged",
        "materialAngleChanged"
    }
{}

int Model::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return details.size();
}

int Model::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return helpers.size();
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()){
        return {};
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

void Model::insertRow(int row, DetailItem *detail) // should we
// check the pointer before adding, or when using?
{
//    for (int j = 0; j < detail_signal_names.size(); ++j){
//        QString signal = detail_signal_names[j];
//        connect(detail, signal.toStdString().c_str(), [&](){
//            int i = details.indexOf(detail); // not efficient
//            QModelIndex idx = createIndex(i, j);
//            QList<int> roles = QList{int(Qt::DisplayRole)};
//            emit QAbstractItemModel::dataChanged(idx, idx, roles);
//        };
//    }
    beginInsertRows(QModelIndex(), row, row); // by-one error?
    details.insert(details.begin() + row, detail);
    endInsertRows();
}

bool Model::removeRow(int row)
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

void Model::setHeaderData(int section, const QVariant &value)
{  // Можно сделать упрощенный вариант чисто для горизонтальных строковых заголовков?
    // Если желательно полный вариант, то как?
    headers[section] = value.toString();
    emit headerDataChanged(Qt::Horizontal, section, section);
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole){
        return headers.at(section);
    }
    else{
        return QVariant();
    }
}



