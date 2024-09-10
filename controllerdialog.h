#pragma once
#include "fillmode.h"
#include "enums.h"
#include "detailitem.h"
#include <QDialog>
#include <QList>
#include <QMap>

namespace Ui { class ControllerDialog; }
class QStandardItem;
class QRegularExpressionValidator;
class FillMode;
class ControllerDialog : public QDialog
{
    Q_OBJECT
private:
    // Приватные поля:
    Ui::ControllerDialog *ui;
    DetailItem* detail;
    QRegularExpressionValidator* validator;
    QMap<ModeNum, FillMode*> modes;  // Описание каждого способа расчета
    ModeNum current_mode;

public:
    // Конструктор, деструктор:
    explicit ControllerDialog(QWidget *parent = nullptr);
    ~ControllerDialog();

    // Публичные методы:
    DetailItem* getInsertedLine();
    bool eventFilter(QObject *object, QEvent *event);

private slots:
    // Автоген слоты для UI:
    void on_cancelButton_clicked();
    void on_methodBox_currentIndexChanged(int index);
    void on_applyButton_clicked();
};
