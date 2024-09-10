#include "controllerdialog.h"
#include "ui_controllerdialog.h"
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QStandardItem>
#include <QMessageBox>
#include <list>
#include <QDebug>
#include <QTimer>

ControllerDialog::ControllerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ControllerDialog),
    detail(nullptr),
    validator(new QRegularExpressionValidator(QRegularExpression("^[0-9]{0,7}$"), this)),
    current_mode{mass_mode}
{
    ui->setupUi(this);
    modes = {
        {
            mass_mode,
            new FillMode(
                {ui->densityFrame},
                {ui->coordBox, ui->massFrame}, // Here we only enlist those widgets that can differ from usual dialog state
                {},
                {},
                {ui->massEdit, ui->xEdit, ui->yEdit, ui->zEdit, ui->angleEdit},
                ui->massEdit,
                "0",
                this
                )
        },
            {
                density_mode,
                new FillMode(
                    {ui->coordBox, ui->massFrame}, // it is better to make it by Mode::setSomeList();
                    {ui->densityFrame},
                    {},
                    {},
                    {ui->densityEdit, ui->angleEdit},
                    ui->densityEdit,
                    "0",
                this
                    )
            },
        {
            copy_mode,
                new FillMode(
                    {ui->coordBox},
                    {ui->massFrame, ui->densityFrame},
                    {},
                    {ui->massEdit, ui->densityEdit, ui->styleBox,
                     ui->angleEdit},
                    {ui->massEdit, ui->densityEdit, ui->angleEdit},
                    ui->materialEdit,
                    "0",
                this
                    )
        }
    };
    for (auto uiptr : {ui->massEdit, ui->xEdit, ui->yEdit, ui->zEdit,
            ui->angleEdit, ui->densityEdit}){
        uiptr->setValidator(validator);
    }
    ui->materialEdit->installEventFilter(this);
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

bool ControllerDialog::eventFilter(QObject *object, QEvent *event)
{
    QLineEdit* edit = static_cast<QLineEdit*>(object);
    if(edit && event->type() == QEvent::FocusIn){ // RV: should I cast QEvent to some QMouseEvent?
        QTimer::singleShot(0,edit,SLOT(selectAll()));
    }
    return QDialog::eventFilter(object, event);
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
    QMap<QLineEdit*, QString> input = modes[current_mode]->getText();  // Считываем поля, зависимые от способа расчёта
    QString method = ui->methodBox->currentText();  // Считываем статичные поля
    QString material = ui->materialEdit->text();
    QString style = ui->styleBox->currentText();

    QMap<QLineEdit*, QLabel*> edit_labels{
        {ui->massEdit, ui->massLabel},
        {ui->densityEdit, ui->densityLabel},
        {ui->xEdit, ui->xLabel},
        {ui->yEdit, ui->yLabel},
        {ui->zEdit, ui->zLabel},
        {ui->materialEdit, ui->materialLabel},
        {ui->angleEdit, ui->angleLabel}
    };

    // Проверяем ввод на пустые значения
    QList<QLineEdit*> empty_edits;
    for (auto it = input.begin(); it != input.end(); ++it) {
        QString val = it.value();
        if (it.key() == ui->xEdit || it.key() == ui->yEdit || it.key() == ui->zEdit){
            if (ui->coordBox->isChecked() && val.isEmpty()){
                empty_edits.push_back(it.key());
            }
        }
        else if (val.isEmpty()) {  // Проверка значения на пустую строку
            empty_edits.push_back(it.key());
        }
    }
    if (material == ""){
        empty_edits.push_back(ui->materialEdit);
    }

    QString empty_names = "";
    for (auto empty_edit : empty_edits){
        empty_names.push_back("\"");
        empty_names.push_back(edit_labels[empty_edit]->text().split(' ').first().remove(':').remove(','));
        empty_names.push_back("\", ");
    }
    empty_names.chop(2);


    if (!empty_edits.isEmpty()){ // is there a better way, to avoid allocating extra memory?
        QMessageBox msg_box(this);
        msg_box.setWindowTitle("Пустые значения");
        QString inner_text = "";
        if (empty_edits.size() > 1){
            inner_text = "Поля " + empty_names + " не заполнены.";
        }
        else{
            inner_text = "Поле " + empty_names + " не заполнено.";
        }
        msg_box.setText(inner_text);
        msg_box.setIcon(QMessageBox::Warning);
        msg_box.addButton("Заполнить", QMessageBox::AcceptRole);
        msg_box.exec();
        return;
    }

    // Заполняем поля детали, которую потом передадим главному окну методом get
    detail = new DetailItem();
    // Диалог контроллера не динамический в MainWindow, поэтому не устанавливаем
    // пока родителя для DetailItem(), это произойдет в DetailModel



    switch(current_mode){
    case mass_mode:
        detail->setMethod(mode_nums[method]);
        detail->setMass(input.value(ui->massEdit, "!").toInt());
        if (ui->coordBox->isChecked()){
            QString x = input.value(ui->xEdit, "!");
            QString y = input.value(ui->yEdit, "!");
            QString z = input.value(ui->zEdit, "!");
            QVector3D center{x.toFloat(), y.toFloat(), z.toFloat()};
            detail->setCenter(center);
        }
        detail->setMaterialName(material);
        detail->setMaterialStyle(style_nums[style]);
        detail->setMaterialAngle(input.value(ui->angleEdit, "!").toInt());
        break;
    case density_mode:
        detail->setMethod(mode_nums[method]);
        detail->setDensity(input.value(ui->densityEdit, "!").toInt());
        detail->setMaterialName(material);
        detail->setMaterialStyle(style_nums[style]);
        detail->setMaterialAngle(input.value(ui->angleEdit, "!").toInt());
        break;
    case copy_mode:
        detail->setMethod(mode_nums[method]);
        detail->setMass(input.value(ui->massEdit, "!").toInt());
        detail->setDensity(input.value(ui->densityEdit, "!").toInt());
        detail->setMaterialName(material);
        detail->setMaterialStyle(style_nums[style]);
        detail->setMaterialAngle(input.value(ui->angleEdit, "!").toInt());
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
    modes[new_mode]->setDefFocus();
    current_mode = new_mode;
}



