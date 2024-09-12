#pragma once
#include "fillmode.h"
#include "modenum.h"
#include "partitem.h"
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
    using InputData = QMap<QObject*, QString>;
private:
    // Приватные поля:
    Ui::ControllerDialog *ui;  // Указатель на UI
    PartItem* part;  // Введенные данные о детали
    QRegularExpressionValidator* validator;  // Валидатор ввода
    QMap<Msp::ModeNum, FillMode> modes;  // Описание каждого режима ввода
    Msp::ModeNum current_mode;  // Текущий режим ввода

    // Методы для обработки данных о детали:
    void setUpPart(InputData input, PartItem* new_part);
    void showEmptyWarningBox(QStringList empty_names);

public:
    // Конструктор, деструктор:
    explicit ControllerDialog(QWidget *parent = nullptr);
    ~ControllerDialog();

    // Публичные методы:
    PartItem* getInsertedLine(QObject* parent);
    bool eventFilter(QObject *object, QEvent *event);

private slots:
    // Автоген слоты для UI:
    void on_cancelButton_clicked();
    void on_methodBox_currentIndexChanged(int index);
    void on_applyButton_clicked();
};
