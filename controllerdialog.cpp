#include "controllerdialog.h"
#include "ui_controllerdialog.h"
#include "partitem.h"
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QMessageBox>
#include <QTimer>
#include <QDebug>

ControllerDialog::ControllerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ControllerDialog),
    part{},
    part_item(nullptr),
    validator(new QRegularExpressionValidator(
        QRegularExpression("^[0-9]{0,7}$"), this)),  // До 7 цифр, как во float,
    // не позволяет вводить - и +
    current_mode(Msp::MassMode),
    modes{}
{
    ui->setupUi(this);

    // Описываем режимы ввода:
    modes = {{Msp::MassMode, {FillModeBuilder()
                            .setHide({ui->densityFrame})
                            .setShow({ui->coordBox, ui->massFrame})
                            .setEnable({})
                            .setDisable({})
                            .setEdit({ui->massEdit, ui->xEdit, ui->yEdit,ui->zEdit,
                                      ui->angleEdit})
                            .setDefaultFocusPtr(ui->massEdit)
                            .setDefaultValue("0")
                            .setEventFilterPtr(this)
                            .build()}},
            {Msp::DensityMode, {FillModeBuilder()
                            .setHide({ui->coordBox, ui->massFrame})
                            .setShow({ui->densityFrame})
                            .setEnable({})
                            .setDisable({})
                            .setEdit({ui->densityEdit, ui->angleEdit})
                            .setDefaultFocusPtr(ui->densityEdit)
                            .setDefaultValue("0")
                            .setEventFilterPtr(this)
                            .build()}},
            {Msp::CopyMode, {FillModeBuilder()
                            .setHide({ui->coordBox})
                            .setShow({ui->massFrame, ui->densityFrame})
                            .setEnable({})
                            .setDisable({ui->massEdit, ui->densityEdit, ui->styleBox,
                                         ui->angleEdit, ui->materialEdit})
                            .setEdit({ui->massEdit, ui->densityEdit, ui->angleEdit})
                            .setDefaultFocusPtr(nullptr)
                            .setDefaultValue("0")
                            .setEventFilterPtr(this)
                            .build()}}};

    // Проверяем словари для работы с enum на соответствие UI:
    Msp::checkModeNames(ui->methodBox);
    Msp::checkModeNums(ui->methodBox);
    Msp::checkModeIconPaths();

    Ssp::checkStyleNames(ui->styleBox);
    Ssp::checkStyleNums(ui->styleBox);
    Ssp::checkStyleIconPaths();

    // Устанавливаем валидатор:
    for (auto uiptr : {ui->massEdit, ui->xEdit, ui->yEdit, ui->zEdit,
            ui->angleEdit, ui->densityEdit}){
        uiptr->setValidator(validator);
    }

    // Запускаем режим по умолчанию:
    ui->materialEdit->installEventFilter(this);
    modes[current_mode].turnOn();
    modes[current_mode].fillInDefaultValues();
}

ControllerDialog::~ControllerDialog()
{
    // Освобождаем память:
    delete ui;
}

PartItem* ControllerDialog::getInsertedLine(QObject *parent)
{
    // Получаем введенные данные и передаем владение деталью:
    part_item->setParent(parent);
    return part_item;
}

bool ControllerDialog::eventFilter(QObject *object, QEvent *event)
{
    // Выделяем всю строку для удобства пользователя:
    QLineEdit* edit = qobject_cast<QLineEdit*>(object);
    if(edit && event->type() == QEvent::FocusIn){
        QTimer::singleShot(0, edit, SLOT(selectAll()));
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
    InputData input = modes[current_mode].getText();
    input[ui->materialEdit] = ui->materialEdit->text();

    // Проверяем ввод из полей (не комбобоксов) на пустые значения:
    QList<QObject*> empty_edits;
    if (current_mode != Msp::CopyMode){
        for (auto it = input.begin(); it != input.end(); ++it) {
            QString val = it.value();
            if ((it.key() == ui->xEdit ||
                 it.key() == ui->yEdit ||
                 it.key() == ui->zEdit) &&
                ui->coordBox->isChecked() &&
                val.isEmpty())
            {
                empty_edits.push_back(it.key());  // Отдельная проверка координат
            }
            else if (val.isEmpty()) {
                empty_edits.push_back(it.key()); // Все остальные поля ввода
            }
            else{
                continue;
            }
        }
    }

    // Запоминаем где искать имена каждого поля ввода, видимые пользователю:
    static QMap<QObject*, QLabel*> edit_labels{
        {ui->massEdit, ui->massLabel},
        {ui->densityEdit, ui->densityLabel},
        {ui->xEdit, ui->xLabel},
        {ui->yEdit, ui->yLabel},
        {ui->zEdit, ui->zLabel},
        {ui->materialEdit, ui->materialLabel},
        {ui->angleEdit, ui->angleLabel}
    };

    // Собираем из UI имена пустых полей для предупреждения пользователю:
    QStringList empty_names = {};  // Имена пустых полей
    for (auto empty_edit : empty_edits){
        empty_names.push_back(edit_labels[empty_edit]->text().split(' ').first()
                              .remove(':').remove(','));
    }

    // Показываем предупреждение если есть пустые значения:
    if (!empty_names.isEmpty()){
        showEmptyWarningBox(empty_names);
        return;  // Чтобы не забыть при редактировании
    }
    else{
        // Считываем оставшиеся данные из комбобоксов:
        input[ui->methodBox] = ui->methodBox->currentText();
        input[ui->styleBox] = ui->styleBox->currentText();

        // Заполняем поля детали, которую потом передадим главному окну геттером:
        static auto methodValidator = [](QVariant field){
            Msp::ModeNum eval_method = static_cast<Msp::ModeNum>(field.toInt());
            return eval_method >= 0 && eval_method < Msp::NoneMode;
        };
        static auto styleValidator = [](QVariant field){
            Ssp::HatchStyleNum hatch_style = static_cast<Ssp::HatchStyleNum>(field.toInt());
            return hatch_style >= 0 && hatch_style < Ssp::NoneStyle;
        };
        static auto methodIconizer = [](QVariant field){
            Msp::ModeNum eval_method = static_cast<Msp::ModeNum>(field.toInt());
            return QIcon(Msp::mode_icon_paths[eval_method]);
        };
        static auto styleIconizer = [](QVariant field){
            Ssp::HatchStyleNum hatch_style = static_cast<Ssp::HatchStyleNum>(field.toInt());
            return QIcon(QPixmap(Ssp::style_icon_paths[hatch_style]).copy(0,0,75,75).
                 scaled(30, 30));  // TODO использовать тоже рефлексию
        };
        static auto methodStringifier = [](QVariant field){
            Msp::ModeNum eval_method = static_cast<Msp::ModeNum>(field.toInt());
            return Msp::mode_names[eval_method];
        };
        static auto styleStringifier = [](QVariant field){
            Ssp::HatchStyleNum hatch_style = static_cast<Ssp::HatchStyleNum>(field.toInt());
            return Ssp::style_names[hatch_style];
        };

        setUpPart(input, part);
        part_item = PartItemBuilder<Part>(part)
            .setValidator("eval_method", methodValidator)
            .setIconizer("eval_method", methodIconizer)
            .setStringifier("eval_method", methodStringifier)
            .setValidator("hatch_style", styleValidator)
            .setIconizer("hatch_style", styleIconizer)
            .setStringifier("hatch_style", styleStringifier)
            .setParent(this)
            .buildDynamic();

        // Успех:
        accept();
    }
}

void ControllerDialog::setUpPart(InputData input, Part& new_part)
{
    // Заполняем данные детали:
    switch(current_mode){
    case Msp::MassMode:
        new_part.eval_method = Msp::mode_nums[input.value(ui->methodBox, "!")];
        new_part.mass = input.value(ui->massEdit, "!").toInt();
        if (ui->coordBox->isChecked()){
            QString x = input.value(ui->xEdit, "!");
            QString y = input.value(ui->yEdit, "!");
            QString z = input.value(ui->zEdit, "!");
            QVector3D center{x.toFloat(), y.toFloat(), z.toFloat()};
            new_part.mass_center = center;
        }
        new_part.material_short_name = input.value(ui->materialEdit, "!");
        new_part.hatch_style = Ssp::style_nums[input.value(ui->styleBox, "!")];
        new_part.hatch_angle = input.value(ui->angleEdit, "!").toInt();
        break;
    case Msp::DensityMode:
        new_part.eval_method = Msp::mode_nums[input.value(ui->methodBox, "!")];
        new_part.density = input.value(ui->densityEdit, "!").toInt();
        new_part.material_short_name = input.value(ui->materialEdit, "!");
        new_part.hatch_style = Ssp::style_nums[input.value(ui->styleBox, "!")];
        new_part.hatch_angle = input.value(ui->angleEdit, "!").toInt();
        break;
    case Msp::CopyMode:
        new_part.eval_method = Msp::mode_nums[input.value(ui->methodBox, "!")];
        new_part.mass = input.value(ui->massEdit, "!").toInt();
        new_part.density = input.value(ui->densityEdit, "!").toInt();
        new_part.material_short_name = input.value(ui->materialEdit, "!");
        new_part.hatch_style = Ssp::style_nums[input.value(ui->styleBox, "!")];
        new_part.hatch_angle = input.value(ui->angleEdit, "!").toInt();
        break;
    default:
        qDebug() << "Unhandled fill mode passed as an argument";
        break;
    }
}

void ControllerDialog::showEmptyWarningBox(QStringList empty_names)
{
    // Предупреждаем пользователя о пустых значениях:
    if (!empty_names.isEmpty()){
        // Готовим текст предупреждения пользователю:
        QString inner_text = "";
        for (auto empty_name : empty_names){  // Должен работать COW
            inner_text.push_back("\"");
            inner_text.push_back(empty_name);
            inner_text.push_back("\", ");
        }
        inner_text.chop(2);
        QString warning_text = "";
        if (empty_names.size() > 1){
            warning_text = "Поля " + inner_text + " не заполнены.";
        }
        else{
            warning_text = "Поле " + inner_text + " не заполнено.";
        }

        // Показываем модальное окно предупреждения:
        QMessageBox::warning(this, "Пустые значения", warning_text);
    }
}

void ControllerDialog::on_methodBox_currentIndexChanged(int index)
{
    // Меняем режим ввода:
    Msp::ModeNum new_mode = static_cast<Msp::ModeNum>(index);
    modes[current_mode].turnOff();
    modes[new_mode].turnOn();
    modes[new_mode].fillInDefaultValues();
    modes[new_mode].activateDefaultFocus();
    current_mode = new_mode;
}
