#include "controllerdialog.h"
#include "ui_controllerdialog.h"
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QStandardItem>
#include <QMessageBox>
#include <list>
#include <QDebug>

ControllerDialog::ControllerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ControllerDialog),
    insertedLine{},
    validator(new QRegularExpressionValidator(QRegularExpression("[0-9]*"), this)),
    current_mode{mass_mode}
{
    ui->setupUi(this);
    modes = {
        {
            mass_mode,
            new Mode(
                {ui->densityFrame},
                {ui->coordBox, ui->massFrame}, // Here we only enlist those widgets that can differ from usual dialog state
                {},
                {},
                {ui->massEdit, ui->xEdit, ui->yEdit, ui->zEdit, ui->angleEdit},
                "0"
                )
        },
            {
                density_mode,
                new Mode(
                    {ui->coordBox, ui->massFrame}, // it is better to make it by Mode::setSomeList();
                    {ui->densityFrame},
                    {},
                    {},
                    {ui->densityEdit, ui->angleEdit},
                    "0"
                    )
            },
        {
            copy_mode,
                new Mode(
                    {ui->coordBox},
                    {ui->massFrame, ui->densityFrame},
                    {},
                    {ui->massEdit, ui->densityEdit, ui->styleBox,
                     ui->angleEdit},
                    {ui->massEdit, ui->densityEdit, ui->angleEdit},
                    "0"
                    )
        }
    };
    for (auto uiptr : {ui->massEdit, ui->xEdit, ui->yEdit, ui->zEdit,
            ui->angleEdit, ui->densityEdit}){
        uiptr->setValidator(validator);
    }
    modes[current_mode]->turnOn();
    modes[current_mode]->fillInDefVals();
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
    // Save text from that QEditLine's from ui which are in the current mode
    // and are being filled with default values by Mode functions
    QMap<QString, QString> input;
    modes[current_mode]->getText(input);

    // Here you need to add conversion into Detail class:
    // initialize with this QStrings converted, or
    // make Detail object and assign/set its members
    // Those column names (left parts of assigning)
    // which depend on the mode will be empty, if they
    // are unused in the mode. This behaviour is
    // guaranted because we specified which
    // QLineEdits to fill with "0"s when we initialized
    // QMap modes, and only those lines will be readed
    // (added into that map by calling Mode::getText())
    QString method = ui->methodBox->currentText();
    QString mass = input.value("massEdit", "");
    QString density = input.value("densityFrame", "");
    QString center = "";
    if (current_mode == mass_mode && ui->coordBox->isChecked()){
        center =    input.value("xEdit", "") + "," +
                    input.value("yEdit", "") + "," +
                    input.value("zEdit", "");
    }
    QString material = ui->materialEdit->text();
    QString style = ui->styleBox->currentText();
    QString angle = input.value("angleEdit", "");

    // Check input for empty values
    if (input.values().contains("") || material == ""){ // is there a better way, to avoid allocating extra memory?
        QMessageBox msg_box(this);
        msg_box.setWindowTitle("Пустые значения");
        msg_box.setText("Не все данные заполнены. Всё равно продолжить?");
        msg_box.setIcon(QMessageBox::Warning);
        msg_box.addButton("Продолжить", QMessageBox::AcceptRole);
        msg_box.addButton("Заполнить", QMessageBox::RejectRole);
        if (msg_box.exec()){
            insertedLine.clear();
            return;
        }
    }

    for (const QString& column_name : {method, mass, density, center, material,
            style, angle}){ // how should I format this line?
        insertedLine.push_back(new QStandardItem(column_name));
    }
    accept();
}

void ControllerDialog::on_methodBox_currentIndexChanged(int index)
{    
    Modenum new_mode = Modenum(index);
    modes[current_mode]->turnOff();
    modes[new_mode]->turnOn();
    modes[new_mode]->fillInDefVals();
    current_mode = new_mode;
}
