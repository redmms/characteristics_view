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
    detail(nullptr),
    validator(new QRegularExpressionValidator(QRegularExpression("^[0-9]{0,9}$"), this)),
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

DetailItem* ControllerDialog::getInsertedLine()
{
    return detail;
}

void ControllerDialog::on_cancelButton_clicked()
{
    reject();
}

void ControllerDialog::on_applyButton_clicked()
{
    // Save text from that QEditLine's from ui which are in the current mode
    // and are being filled with default values by Mode functions

    // initialize with this QStrings converted, or
    // make Detail object and assign/set its members
    // Those column names (left parts of assigning)
    // which depend on the mode will be empty, if they
    // are unused in the mode. This behaviour is
    // guaranted because we specified which
    // QLineEdits to fill with "0"s when we initialized
    // QMap modes, and only those lines will be readed
    // (added into that map by calling Mode::getText())

    // Считываем ввод из UI
    QMap<QString, QString> input;
    modes[current_mode]->getText(input);  // Считываем поля, зависимые от способа расчёта
    QString method = ui->methodBox->currentText();  // Считываем статичные поля
    QString material = ui->materialEdit->text();
    QString style = ui->styleBox->currentText();

    // Проверяем ввод на пустые значения
    if (input.values().contains("") || material == ""){ // is there a better way, to avoid allocating extra memory?
        QMessageBox msg_box(this);
        msg_box.setWindowTitle("Пустые значения");
        msg_box.setText("Не все данные заполнены.");
        msg_box.setIcon(QMessageBox::Warning);
        msg_box.addButton("Заполнить", QMessageBox::AcceptRole);
        msg_box.exec();
        return;
    }

    // Заполняем поля детали, которую потом передадим главному окну методом get
    detail = new DetailItem(this);
    switch(current_mode){
    case mass_mode:
        detail->setMethod(mode_nums[method]);
        detail->setMass(input.value("massEdit", "!").toInt());
        if (ui->coordBox->isChecked()){
            QString x = input.value("xEdit", "!");
            QString y = input.value("yEdit", "!");
            QString z = input.value("zEdit", "!");
            QVector3D center{x.toInt(), y.toInt(), z.toInt()};
            detail->setCenter(center);
        }
        detail->setMaterialName(material);
        detail->setMaterialStyle(style_nums[style]);
        detail->setMaterialAngle(input.value("angleEdit", "!").toInt());
        break;
    case density_mode:
        detail->setMethod(mode_nums[method]);
        detail->setDensity(input.value("densityEdit", "!").toInt());
        detail->setMaterialName(material);
        detail->setMaterialStyle(style_nums[style]);
        detail->setMaterialAngle(input.value("angleEdit", "!").toInt());
        break;
    case copy_mode:
        detail->setMethod(mode_nums[method]);
        detail->setMass(input.value("massEdit", "!").toInt());
        detail->setDensity(input.value("densityEdit", "!").toInt());
        detail->setMaterialName(material);
        detail->setMaterialStyle(style_nums[style]);
        detail->setMaterialAngle(input.value("angleEdit", "!").toInt());
        break;
    }
    accept();
}

void ControllerDialog::on_methodBox_currentIndexChanged(int index)
{    
    ModeNum new_mode = ModeNum(index);
    modes[current_mode]->turnOff();
    modes[new_mode]->turnOn();
    modes[new_mode]->fillInDefVals();
    current_mode = new_mode;
}
