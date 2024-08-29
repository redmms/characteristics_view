#include "paramdialog.h"
#include "ui_paramdialog.h"
#include <QIntValidator>
#include <limits.h>

ParamDialog::ParamDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParamDialog),
    insertedLine{},
    validator(new QIntValidator(0, LONG_MAX, this))
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    ui->massEdit->setValidator(validator);
    ui->xEdit->setValidator(validator);
    ui->yEdit->setValidator(validator);
    ui->zEdit->setValidator(validator);
    ui->angleEdit->setValidator(validator);
    ui->densityEdit_1->setValidator(validator);
    ui->angleEdit_3->setValidator(validator);
    ui->densityEdit_2->setValidator(validator);
    ui->massEdit_4->setValidator(validator);
    ui->angleEdit_4->setValidator(validator);
}

ParamDialog::~ParamDialog()
{
    delete ui;
}

QList<QStandardItem*> ParamDialog::getInsertedLine()
{
    return insertedLine;
}

void ParamDialog::on_cancelButton_clicked()
{
    reject();
}

void ParamDialog::on_checkBox_stateChanged(int state)
{
    if (state){
        ui->xEdit->show();
        ui->yEdit->show();
        ui->zEdit->show();
        ui->xLabel->show();
        ui->yLabel->show();
        ui->zLabel->show();
    }
    else{
        ui->xEdit->hide();
        ui->yEdit->hide();
        ui->zEdit->hide();
        ui->xLabel->hide();
        ui->yLabel->hide();
        ui->zLabel->hide();
    }
}

void ParamDialog::on_evalMethodBox_currentIndexChanged(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
    ui->evalMethodBox->setCurrentIndex(index);
    ui->evalMethodBox_3->setCurrentIndex(index);
    ui->evalMethodBox_4->setCurrentIndex(index);
}

void ParamDialog::on_evalMethodBox_4_currentIndexChanged(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
    ui->evalMethodBox->setCurrentIndex(index);
    ui->evalMethodBox_3->setCurrentIndex(index);
    ui->evalMethodBox_4->setCurrentIndex(index);
}

void ParamDialog::on_evalMethodBox_3_currentIndexChanged(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
    ui->evalMethodBox->setCurrentIndex(index);
    ui->evalMethodBox_3->setCurrentIndex(index);
    ui->evalMethodBox_4->setCurrentIndex(index);
}

void ParamDialog::on_massApplyButton_clicked()
{
    QString method = ui->evalMethodBox->currentText();
    QString mass = ui->massEdit->text();
    QString density = "";
    QString center = ui->xEdit->text() + "," + ui->yEdit->text() + "," + ui->zEdit->text();
    QString material = ui->materialEdit->text().split(" ")[0];
    QString style = ui->lineStyleBox->currentText();
    QString angle = ui->angleEdit->text();
    for (auto str : {method, mass, density, center, material, style, angle}){
        insertedLine.push_back(new QStandardItem(str));
    }
    accept();
}


void ParamDialog::on_densityApplyButton_clicked()
{
    QString method = ui->evalMethodBox->currentText();
    QString mass = "";
    QString density = ui->densityEdit_1->text();
    QString center = "";
    QString material = ui->materialEdit_3->text().split(" ")[0];
    QString style = ui->lineStyleBox_3->currentText();
    QString angle = ui->angleEdit_3->text();
    for (auto str : {method, mass, density, center, material, style, angle}){
        insertedLine.push_back(new QStandardItem(str));
    }
    accept();
}


void ParamDialog::on_copyApplyButton_clicked()
{
    QString method = ui->evalMethodBox->currentText();
    QString mass = "";
    QString density = ui->densityEdit_1->text();
    QString center = "";
    QString material = ui->materialEdit_3->text().split(" ")[0];
    QString style = ui->lineStyleBox_3->currentText();
    QString angle = ui->angleEdit_3->text();
    for (auto str : {method, mass, density, center, material, style, angle}){
        insertedLine.push_back(new QStandardItem(str));
    }
    accept();
}

