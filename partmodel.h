#pragma once
#include "partitem.h"
#include <QAbstractTableModel>
#include <QVector>

class AbstractHelper;
class PartModel : public QAbstractTableModel
{
    Q_OBJECT
private:
    // Приватные поля:
    QVector<PartItem*> parts;  // Данные о деталях, содержимое таблицы
    QVector<QString> headers;
    int column_count;

    // Метод валидации индексов:
    bool isValidAccessRow(int row) const;
    bool isValidInsertRow(int row) const;
    bool isValidColumn(int column) const;
    bool isValidItem(PartItem* item) const;

public:
    // Конструктор:
    explicit PartModel(int rows = 0, int columns = 0, QObject *parent = nullptr);

    // Публичные методы, rowCount, columnCount, data - обязательны для
    // представления:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool insertRow(int row, PartItem* part);
    void appendRow(PartItem* part);  // Метод для удобства
    bool removeRow(int row);
    bool setHeaderData(int column, const QVariant &value);
    QVariant headerData(int column, Qt::Orientation orientation,
                        int role) const override;
    PartItem* getPart(int row);

private slots:
    void partDeleted(QObject* object);   
    // Слот для поиска индекса ячейки в рантайме и перенаправке сигнала
    // представлению c нужной сигнатурой:
    void findChangedIndex(int column);
};
