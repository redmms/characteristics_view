#include "controllerdialog.h"
#include "ui_controllerdialog.h"
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QStandardItem>
#include <list>

ControllerDialog::ControllerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParamDialog),
    insertedLine{},
    validator(new QRegularExpressionValidator(QRegularExpression("[0-9]*"), this))
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint |
            Qt::WindowCloseButtonHint);
    for (auto uiptr : {ui->massEdit, ui->xEdit, ui->yEdit, ui->zEdit,
            ui->angleEdit, ui->densityEdit}){
        uiptr->setValidator(validator);
    }
    changeMode(massMode);
}

ControllerDialog::~ControllerDialog()
{
    delete ui;
}

QList<QStandardItem*> ControllerDialog::getInsertedLine()
{
    return insertedLine;
}

void ControllerDialog::on_cancelButton_clicked()
{
    reject();
}

void ControllerDialog::on_applyButton_clicked()
{
    QString method = ui->methodBox->currentText();
    QString mass = ui->massEdit->text();
    QString density = ui->densityEdit->text();
    QString center = ui->xEdit->text() + "," +
                     ui->yEdit->text() + "," +
                     ui->zEdit->text();
    QString material = ui->materialEdit->text();
    QString style = ui->styleBox->currentText();
    QString angle = ui->angleEdit->text();
    switch(modenum(ui->methodBox->currentIndex())){
    case massMode:
        density = "";
        break;
    case densityMode:
        mass = "";
        center = "";
        break;
    case copyMode:
        center = "";
        break;
    }
    for (const QString& column_name : {method, mass, density, center, material,
        style, angle}){
        insertedLine.push_back(new QStandardItem(column_name));
    }
    accept();
}

void ControllerDialog::on_methodBox_currentIndexChanged(int index)
{    
    changeMode(modenum(index));
}

void ControllerDialog::changeMode(modenum mode)
{
    std::list<QWidget*> hideptrs, showptrs, enableptrs, disableptrs;
    switch(mode){
    case massMode:
        hideptrs = {ui->densityFrame};
        showptrs = {ui->coordBox, ui->massFrame};
        enableptrs = {ui->massEdit, ui->densityEdit, ui->styleBox, ui->angleEdit};
        break;
    case densityMode:
        hideptrs = {ui->coordBox, ui->massFrame};
        showptrs = {ui->densityFrame};
        enableptrs = {ui->massEdit, ui->densityEdit, ui->styleBox, ui->angleEdit};
        break;
    case copyMode:
        hideptrs = {ui->coordBox};
        showptrs = {ui->massFrame, ui->densityFrame};
        disableptrs = {ui->massEdit, ui->densityEdit, ui->styleBox, ui->angleEdit};
        break;
    }
    for (auto uiptr : hideptrs){
        uiptr->hide();
    }
    for (auto uiptr : showptrs){
        uiptr->show();
    }
    for (auto uiptr : enableptrs){
        uiptr->setEnabled(true);
    }
    for (auto uiptr : disableptrs){
        uiptr->setEnabled(false);
    }
    for (auto uiptr : {ui->massEdit, ui->densityEdit, ui->angleEdit, ui->xEdit,
            ui->yEdit, ui->zEdit}){
        uiptr->setText("0");
    }
}

