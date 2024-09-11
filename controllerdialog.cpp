#include "controllerdialog.h"
#include "ui_controllerdialog.h"
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QStandardItem>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>

ControllerDialog::ControllerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ControllerDialog),
    part(nullptr),
    validator(new QRegularExpressionValidator(
        QRegularExpression("^[0-9]{0,7}$"), this)),  // До 7 цифр, как во float,
    // не позволяет вводить - и +
    current_mode{MassMode}
{
    ui->setupUi(this);

    // Описываем режимы ввода:
    modes = {{MassMode, {}},
             {DensityMode, {}},
             {CopyMode, {}}};

    modes[MassMode].setHide({ui->densityFrame});
    modes[MassMode].setShow({ui->coordBox, ui->massFrame});
    modes[MassMode].setEnable({});
    modes[MassMode].setDisable({});
    modes[MassMode].setEdit({ui->massEdit, ui->xEdit, ui->yEdit,ui->zEdit,
                             ui->angleEdit});
    modes[MassMode].setDefaultFocusPtr(ui->massEdit);
    modes[MassMode].fillInDefaultValue("0");
    modes[MassMode].setEventFilterPtr(this);

    modes[DensityMode].setHide({ui->coordBox, ui->massFrame});
    modes[DensityMode].setShow({ui->densityFrame});
    modes[DensityMode].setEnable({});
    modes[DensityMode].setDisable({});
    modes[DensityMode].setEdit({ui->densityEdit, ui->angleEdit});
    modes[DensityMode].setDefaultFocusPtr(ui->densityEdit);
    modes[DensityMode].fillInDefaultValue("0");
    modes[DensityMode].setEventFilterPtr(this);

    modes[CopyMode].setHide({ui->coordBox});
    modes[CopyMode].setShow({ui->massFrame, ui->densityFrame});
    modes[CopyMode].setEnable({});
    modes[CopyMode].setDisable({ui->massEdit, ui->densityEdit, ui->styleBox,
                                ui->angleEdit, ui->materialEdit});
    modes[CopyMode].setEdit({ui->massEdit, ui->densityEdit, ui->angleEdit});
    modes[CopyMode].setDefaultFocusPtr(nullptr);
    modes[CopyMode].fillInDefaultValue("0");
    modes[CopyMode].setEventFilterPtr(this);

    // Устанавливаем валидатор:
    for (auto uiptr : {ui->massEdit, ui->xEdit, ui->yEdit, ui->zEdit,
            ui->angleEdit, ui->densityEdit}){
        uiptr->setValidator(validator);
    }

    // Запускаем дефолтный режим:
    ui->materialEdit->installEventFilter(this);
    modes[current_mode].turnOn();
    modes[current_mode].fillInDefaultValues();
}

ControllerDialog::~ControllerDialog()
{
    // Освобождаем память:
    delete ui;
}

PartItem *ControllerDialog::getInsertedLine(QObject *parent)
{
    // Получаем введенные данные и передаем владение:
    part->setParent(parent);
    return part;
}

bool ControllerDialog::eventFilter(QObject *object, QEvent *event)
{
    // Выделяем всю строку для удобства пользователя:
    QLineEdit* edit = static_cast<QLineEdit*>(object);
    if(edit && event->type() == QEvent::FocusIn){ // RV: should I cast QEvent to some QMouseEvent?
        QTimer::singleShot(0,edit,SLOT(selectAll()));
    }
    return QDialog::eventFilter(object, event);
}

void ControllerDialog::on_cancelButton_clicked()
{
    // Закрываем окно без изменений:
    reject();
}

void ControllerDialog::on_applyButton_clicked()
{
    // Считываем поля UI, зависимые от способа расчёта:
    QMap<QLineEdit*, QString> input =  modes[current_mode].getText();

    // Считываем статичные поля:
    QString method = ui->methodBox->currentText();
    QString material = ui->materialEdit->text();
    QString style = ui->styleBox->currentText();

    // Запоминаем где искать имена каждого поля ввода, видимые пользователю
    QMap<QLineEdit*, QLabel*> edit_labels{
        {ui->massEdit, ui->massLabel},
        {ui->densityEdit, ui->densityLabel},
        {ui->xEdit, ui->xLabel},
        {ui->yEdit, ui->yLabel},
        {ui->zEdit, ui->zLabel},
        {ui->materialEdit, ui->materialLabel},
        {ui->angleEdit, ui->angleLabel}
    };

    // Проверяем ввод на пустые значения:
    QList<QLineEdit*> empty_edits;
    if (current_mode != CopyMode){
        for (auto it = input.begin(); it != input.end(); ++it) {
            QString val = it.value();
            if (it.key() == ui->xEdit || it.key() == ui->yEdit ||
                it.key() == ui->zEdit){
                if (ui->coordBox->isChecked() && val.isEmpty()){
                    empty_edits.push_back(it.key());  // Отдельная проверка координат
                }
            }
            else if (val.isEmpty()) {
                empty_edits.push_back(it.key()); // Все остальные поля ввода
            }
        }

        // Отдельная проверка имени материала:
        if (material == ""){
            empty_edits.push_back(ui->materialEdit);
        }
    }

    // Готовим предупреждение пользователю:
    QString empty_names = "";
    for (auto empty_edit : empty_edits){
        empty_names.push_back("\"");
        empty_names.push_back(edit_labels[empty_edit]->text().split(' ').first().remove(':').remove(','));
        empty_names.push_back("\", ");
    }
    empty_names.chop(2);

    // Предупреждаем пользователя о пустых значениях:
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
    // Диалог контроллера не динамический в MainWindow, поэтому не устанавливаем
    // пока родителя для PartItem(), это произойдет в PartModel
    part = new PartItem();

    // Заполняем данные детали:
    switch(current_mode){
    case MassMode:
        part->setMethod(mode_nums[method]);
        part->setMass(input.value(ui->massEdit, "!").toInt());
        if (ui->coordBox->isChecked()){
            QString x = input.value(ui->xEdit, "!");
            QString y = input.value(ui->yEdit, "!");
            QString z = input.value(ui->zEdit, "!");
            QVector3D center{x.toFloat(), y.toFloat(), z.toFloat()};
            part->setCenter(center);
        }
        part->setMaterialName(material);
        part->setMaterialStyle(style_nums[style]);
        part->setMaterialAngle(input.value(ui->angleEdit, "!").toInt());
        break;
    case DensityMode:
        part->setMethod(mode_nums[method]);
        part->setDensity(input.value(ui->densityEdit, "!").toInt());
        part->setMaterialName(material);
        part->setMaterialStyle(style_nums[style]);
        part->setMaterialAngle(input.value(ui->angleEdit, "!").toInt());
        break;
    case CopyMode:
        part->setMethod(mode_nums[method]);
        part->setMass(input.value(ui->massEdit, "!").toInt());
        part->setDensity(input.value(ui->densityEdit, "!").toInt());
        part->setMaterialName(material);
        part->setMaterialStyle(style_nums[style]);
        part->setMaterialAngle(input.value(ui->angleEdit, "!").toInt());
        break;
    }
    accept();
}

void ControllerDialog::on_methodBox_currentIndexChanged(int index)
{
    // Меняем режим ввода:
    ModeNum new_mode = ModeNum(index);
    modes[current_mode].turnOff();
    modes[new_mode].turnOn();
    modes[new_mode].fillInDefaultValues();
    modes[new_mode].activateDefaultFocus();
    current_mode = new_mode;
}



