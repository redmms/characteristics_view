#include "paramdialog.h"
#include "ui_paramdialog.h"

void ParamDialog::turnOnMassRegime()
{

}

ParamDialog::ParamDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParamDialog),
    insertedLine{}
{
    ui->setupUi(this);
   // setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
}

ParamDialog::~ParamDialog()
{
    delete ui;
}

QList<QStandardItem*> ParamDialog::getInsertedLine()
{
    return insertedLine;
}

void ParamDialog::on_applyButton_clicked()
{
    insertedLine = {ui->massEdit->text(), ui->, }
    accept();
}


void ParamDialog::on_cancelButton_clicked()
{
    reject();
}

