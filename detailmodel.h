#pragma once
#include "detailitem.h"
#include "helpers/abstracthelper.h"
#include <QAbstractTableModel>
#include <QList>
#include <QVector>
#include <list>
#include <vector>

class DetailModel : public QAbstractTableModel
{
    Q_OBJECT
private:
    // Приватные поля:
    std::vector<DetailItem*> details;  // Данные о деталях, содержимое таблицы
    const std::vector<AbstractHelper*> helpers;  // Вспомогательные объекты
    // для работы с полями по индексу
    std::vector<QString> headers;  // Заголовки таблицы

    // Метод валидации индексов:
    bool isValidRow(int row) const;
    bool isValidColumn(int column) const;

public:
    // Конструктор:
    explicit DetailModel(int rows = 0, QObject *parent = nullptr);

    // Публичные методы, rowCount, columnCount, data - обязательны для
    // представления:
    int rowCount(const QModelIndex& parent  = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool insertRow(int row, DetailItem* detail);
    bool removeRow(int row);
    bool setHeaderData(int section, const QVariant &value);
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role) const override;
};
