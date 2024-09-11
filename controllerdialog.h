#pragma once
#include "fillmode.h"
#include "modenum.h"
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
    Ui::ControllerDialog *ui;  // Указатель на UI
    DetailItem* detail;  // Введенные данные о детали
    QRegularExpressionValidator* validator;  // Валидатор ввода
    QMap<ModeNum, FillMode> modes;  // Описание каждого режима ввода
    ModeNum current_mode;  // Текущий режим ввода

public:
    // Конструктор, деструктор:
    explicit ControllerDialog(QWidget *parent = nullptr);
    ~ControllerDialog();

    // Публичные методы:
    DetailItem* getInsertedLine(QObject* parent);
    bool eventFilter(QObject *object, QEvent *event);

private slots:
    // Автоген слоты для UI:
    void on_cancelButton_clicked();
    void on_methodBox_currentIndexChanged(int index);
    void on_applyButton_clicked();
};
