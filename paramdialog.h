#ifndef PARAMDIALOG_H
#define PARAMDIALOG_H

#include <QDialog>
#include <QList>
#include <QStandardItem>

enum regime{
    mass_regime,
    density_regime,
    copy_regime
};

namespace Ui {
    class ParamDialog;
}

class QIntValidator;
class ParamDialog : public QDialog
{
    Q_OBJECT
    QList<QStandardItem*> insertedLine;
    Ui::ParamDialog *ui;
    QIntValidator* validator;

public:
    explicit ParamDialog(QWidget *parent = nullptr);
    ~ParamDialog();
    QList<QStandardItem*> getInsertedLine();

private slots:
    void on_cancelButton_clicked();
    void on_checkBox_stateChanged(int state);
    void on_evalMethodBox_currentIndexChanged(int index);
    void on_evalMethodBox_4_currentIndexChanged(int index);
    void on_evalMethodBox_3_currentIndexChanged(int index);
    void on_massApplyButton_clicked();
    void on_densityApplyButton_clicked();
    void on_copyApplyButton_clicked();
};

#endif // PARAMDIALOG_H
