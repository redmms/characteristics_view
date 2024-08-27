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

class ParamDialog : public QDialog
{
    Q_OBJECT

    QList<QStandardItem*> insertedLine;
    void turnOnMassRegime();
    void turnOnDensityRegime();
    void turnOnCopyRegime();

public:
    explicit ParamDialog(QWidget *parent = nullptr);
    ~ParamDialog();

    QList<QStandardItem*> getInsertedLine();

private slots:
    void on_applyButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::ParamDialog *ui;
};

#endif // PARAMDIALOG_H
