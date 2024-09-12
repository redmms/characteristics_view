#include "fillmode.h"
#include "ui_mainwindow.h"
#include <QLineEdit>
#include <QWidget>

FillMode::FillMode( const QList<QWidget *> &hide_ptrs_,
                    const QList<QWidget *> &show_ptrs_,
                    const QList<QWidget *> &enable_ptrs_,
                    const QList<QWidget *> &disable_ptrs_,
                    const QList<QLineEdit *> &edit_ptrs_,
                    QLineEdit* const default_focus_ptr_,
                    QString default_value_,
                    QObject* event_filter_) :
    hide_ptrs(hide_ptrs_),
    show_ptrs(show_ptrs_),
    enable_ptrs(enable_ptrs_),
    disable_ptrs(disable_ptrs_),
    edit_ptrs(edit_ptrs_),
    default_focus_ptr(default_focus_ptr_),
    default_value(default_value_),
    event_filter(event_filter_)
{}

FillMode::FillMode()
{}

void FillMode::turnOn()
{
    // Включение режима:
    // Использовать только после turnOff() предыдущего режима
    for (auto uiptr : hide_ptrs){
        uiptr->hide();
    }
    for (auto uiptr : show_ptrs){
        uiptr->show();
    }
    for (auto uiptr : enable_ptrs){
        uiptr->setEnabled(true);
    }
    for (auto uiptr : disable_ptrs){
        uiptr->setEnabled(false);
    }

    // Установка фильтра событий для выделения ввода из полей UI, но можно
    // использовать и для другого:
    if (event_filter){
        for (auto uiptr : edit_ptrs){
            if (uiptr->isEnabled()){
                uiptr->installEventFilter(event_filter);
            }
            else{
                uiptr->removeEventFilter(event_filter);
            }
        }
    }
}

void FillMode::turnOff()
{
    // Отключение режима:
    for (auto uiptr : hide_ptrs){
        uiptr->show();
    }
    for (auto uiptr : show_ptrs){
        uiptr->hide();
    }
    for (auto uiptr : enable_ptrs){
        uiptr->setEnabled(false);
    }
    for (auto uiptr : disable_ptrs){
        uiptr->setEnabled(true);
    }

    // Отключения всех фильтров событий, что могли установить ранее:
    if (event_filter){
        for (auto uiptr : edit_ptrs){
            uiptr->removeEventFilter(event_filter);
        }
    }
}

FillMode::InputData FillMode::getText()
{
    // Получаем текст из полей ввода, видимых в этом режиме.
    // Видимость не гарантируется и обеспечивается инициализацией
    // списа edit_ptrs
    InputData line_edit_input;
    for (auto uiptr : edit_ptrs){
        line_edit_input[uiptr] = uiptr->text();
    }
    return line_edit_input;
}

void FillMode::fillInDefaultValue(QLineEdit *uiptr, QString defval)
{
    // Заполняем поле ввода значением по умолчанию:
    default_values[uiptr] = defval;
}

void FillMode::clearDefaultValues()
{
    // Очищаем словарь пользовательских дефолтных значений:
    default_values.clear();
}

void FillMode::fillInDefaultValues()
{
    // Заполняем поля ввода пользовательскими значениями по умолчанию:
    for (auto uiptr : edit_ptrs){
        if (default_values.count(uiptr)){
            uiptr->setText(default_values[uiptr]);
        }
        else{
            uiptr->setText(default_value);
        }
    }
}

void FillMode::activateDefaultFocus()
{
    // Ставим курсор в поле по умолчанию:
    if (default_focus_ptr){
        default_focus_ptr->selectAll();
        default_focus_ptr->setFocus();
    }
}

void FillMode::setHide(QList<QWidget *> hide_ptrs_)
{
    hide_ptrs = hide_ptrs_;
}

void FillMode::setShow(QList<QWidget *> show_ptrs_)
{
    show_ptrs = show_ptrs_;
}

void FillMode::setEnable(QList<QWidget *> enable_ptrs_)
{
    enable_ptrs = enable_ptrs_;
}

void FillMode::setDisable(QList<QWidget *> disable_ptrs_)
{
    disable_ptrs = disable_ptrs_;
}

void FillMode::setEdit(QList<QLineEdit *> edit_ptrs_)
{
    edit_ptrs = edit_ptrs_;
}

void FillMode::setDefaultFocusPtr(QLineEdit *default_focus_ptr_)
{
    default_focus_ptr = default_focus_ptr_;
}

void FillMode::fillInDefaultValue(QString default_value_)
{
    default_value = default_value_;
}

void FillMode::setDefaultValues(InputData default_values_)
{
    default_values = default_values_;
}

void FillMode::setEventFilterPtr(QObject *event_filter_)
{
    event_filter = event_filter_;
}
