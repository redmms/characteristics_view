#pragma once
#include "partitem.h"
#include "helpers/abstracthelper.h"
#include <QAbstractTableModel>
#include <QVector>

class PartModel : public QAbstractTableModel
{
    Q_OBJECT
private:
    // Приватные поля:
    QVector<PartItem*> parts;  // Данные о деталях, содержимое таблицы
    const QVector<AbstractHelper*> helpers;  // Вспомогательные объекты
    // для работы с полями PartItem по индексу
    QVector<QString> headers;  // Заголовки таблицы

    // Метод валидации индексов:
    bool isValidAccessRow(int row) const;
    bool isValidInsertRow(int row) const;
    bool isValidColumn(int column) const;

public:
    // Конструктор:
    explicit PartModel(int rows = 0, QObject *parent = nullptr);

    // Публичные методы, rowCount, columnCount, data - обязательны для
    // представления:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool insertRow(int row, PartItem* part);
    void appendRow(PartItem* part);  // Метод для удобства
    bool removeRow(int row);
    bool setHeaderData(int section, const QVariant &value);
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role) const override;

private slots:
    void partDeleted(QObject* object);
};
