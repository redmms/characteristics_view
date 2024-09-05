#pragma once
#include "mode.h"
#include <QDialog>
#include <QList>
// #include <Detail>

enum Modenum{
    mass_mode,
    density_mode,
    copy_mode
};

namespace Ui { class ControllerDialog; }
class QStandardItem;
class QRegularExpressionValidator;
class Mode;
class ControllerDialog : public QDialog
{
    Q_OBJECT
private:
    Ui::ControllerDialog *ui;
    QList<QStandardItem*> insertedLine;
    QRegularExpressionValidator* validator;
    std::unordered_map<Modenum, Mode*> modes;
    Modenum current_mode;

public:
    explicit ControllerDialog(QWidget *parent = nullptr);
    ~ControllerDialog();
    QList<QStandardItem*> getInsertedLine();

private slots:
    void on_cancelButton_clicked();
    void on_methodBox_currentIndexChanged(int index);
    void on_applyButton_clicked();
};
