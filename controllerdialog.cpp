#include "controllerdialog.h"
#include "ui_controllerdialog.h"
#include <QRegularExpressionValidator>  // should I include QRegularExpression
#include <QStandardItem>

ControllerDialog::ControllerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParamDialog),
    insertedLine{},
    validator(new QRegularExpressionValidator(QRegularExpression("[1-9][0-9]*"), this)),
    // checking first digit for zero wasn't required by the task, am I allowed to add this check,
    //or it is better to avoid doing unasked things?
    all{uint32_t(-1)},
    coord{xLabel | xEdit | yLabel | yEdit | zLabel | zEdit},
    center{coord | checkBox}, // is it Ok to have two "center" variables?
    massShow{all & ~densityLabel & ~densityEdit},
    massEnable{all},
    densityShow{all & ~massLabel & ~massEdit & ~center},
    densityEnable{all},
    copyShow{all & ~center},
    copyEnable{0},
    currentShow{massShow},
    currentEnable{massEnable}
{
    ui->setupUi(this);
    uipointers = {  // order should be the same as in statenum
       ui->massLabel,
       ui->massEdit,
       ui->densityLabel,
       ui->densityEdit,
       ui->checkBox,
       ui->xLabel,
       ui->xEdit,
       ui->yLabel,
       ui->yEdit,
       ui->zLabel,
       ui->zEdit,
       ui->styleBox,
       ui->angleEdit
    };
    setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint); // how to divide the line?
    for (auto uiptr : {ui->massEdit, ui->xEdit, ui->yEdit, ui->zEdit, ui->angleEdit, ui->densityEdit}){
             uiptr->setValidator(validator);
    }
    changeRegime(currentShow, currentEnable);
}

ControllerDialog::~ControllerDialog()
{
    delete ui;
}

QList<QStandardItem*> ControllerDialog::getInsertedLine()
{
    return insertedLine;
}

void ControllerDialog::changeRegime(uint32_t showFlags, uint32_t enableFlags)
{
    uint mask = 1u;
    for (auto uiptr : uipointers){
        if (mask & showFlags){
            uiptr->show();
        }
        else{
            uiptr->hide();
        }
        uiptr->setEnabled(mask & enableFlags);
        mask <<= 1;
    }
    currentShow = showFlags;
    currentEnable = enableFlags;
}

void ControllerDialog::on_cancelButton_clicked()
{
    reject();
}

void ControllerDialog::on_checkBox_stateChanged(int coordOn)
{
    if (coordOn){
        changeRegime(currentShow | coord, currentEnable);
    }
    else{
        changeRegime(currentShow & ~coord, currentEnable);
    }
}

void ControllerDialog::on_methodBox_currentIndexChanged(int index)
{    
    switch(index){
    case 0:
        changeRegime(massShow, massEnable);
        break;
    case 1:
        changeRegime(densityShow, densityEnable);
        break;
    case 2:
        changeRegime(copyShow, copyEnable);
        break;
    }
}

void ControllerDialog::on_applyButton_clicked()
{
    QString method = ui->methodBox->currentText();
    QString mass = ui->massEdit->text();
    QString density = ui->densityEdit->text(); // should we check regime?
    QString center = ui->xEdit->text() + "," + ui->yEdit->text() + "," + ui->zEdit->text(); // should I divide the line or 92 chars is Ok?
    QString material = ui->materialEdit->text();
    QString style = ui->styleBox->currentText();
    QString angle = ui->angleEdit->text();
    switch(ui->methodBox->currentIndex()){
    case 0:
        density = "";
        break;
    case 1:
        mass = "";
        break;
    case 2:
        center = "";
        break;
    }
    if (center == ",,"){
        center = "";
    }
    for (auto column_name : {method, mass, density, center, material, style, angle}){
        insertedLine.push_back(new QStandardItem(column_name));
    }
    accept();
}
