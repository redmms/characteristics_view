#pragma once
#include <QDialog>
#include <QList>

enum Modenum{
    massMode,
    densityMode,
    copyMode
};

namespace Ui { class ParamDialog; }
class QStandardItem;
class QRegularExpressionValidator;
class ControllerDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::ParamDialog *ui;
    QList<QStandardItem*> insertedLine;
    QRegularExpressionValidator* validator;
    void changeMode(Modenum mode);

public:
    explicit ControllerDialog(QWidget *parent = nullptr);
    ~ControllerDialog();
    QList<QStandardItem*> getInsertedLine();

private slots:
    void on_cancelButton_clicked();
    void on_methodBox_currentIndexChanged(int index);
    void on_applyButton_clicked();
};
