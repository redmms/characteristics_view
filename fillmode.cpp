#include "fillmode.h"
#include "ui_mainwindow.h"
#include <QLineEdit>
#include <QWidget>

FillMode::FillMode( QList<QWidget*> hide_ptrs_,
                    QList<QWidget*> show_ptrs_,
                    QList<QWidget*> enable_ptrs_,
                    QList<QWidget*> disable_ptrs_,
                    QList<QLineEdit*> edit_ptrs_,
                    QLineEdit* default_focus_ptr_,
                    QString default_value_,
                    InputData custom_defaults_,
                    QObject* event_filter_) :
    hide_ptrs(hide_ptrs_),
    show_ptrs(show_ptrs_),
    enable_ptrs(enable_ptrs_),
    disable_ptrs(disable_ptrs_),
    edit_ptrs(edit_ptrs_),
    default_focus_ptr(default_focus_ptr_),
    default_value(default_value_),
    custom_defaults(custom_defaults_),
    event_filter(event_filter_)
{}

void FillMode::turnOn() const
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

void FillMode::turnOff() const
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

FillMode::InputData FillMode::getText() const
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

void FillMode::fillInDefaultValues() const
{
    // Заполняем поля ввода пользовательскими значениями по умолчанию:
    for (auto uiptr : edit_ptrs){
        if (custom_defaults.count(uiptr)){
            uiptr->setText(custom_defaults[uiptr]);
        }
        else{
            uiptr->setText(default_value);
        }
    }
}

void FillMode::activateDefaultFocus() const
{
    // Ставим курсор в поле по умолчанию:
    if (default_focus_ptr){
        default_focus_ptr->selectAll();
        default_focus_ptr->setFocus();
    }
}

