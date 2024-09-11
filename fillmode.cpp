#include "fillmode.h"
#include "ui_mainwindow.h"
#include <QLineEdit>
#include <QWidget>

FillMode::FillMode(const QList<QWidget *> &hide_ptrs_,
           const QList<QWidget *> &show_ptrs_,
           const QList<QWidget *> &enable_ptrs_,
           const QList<QWidget *> &disable_ptrs_,
           const QList<QLineEdit *> &edit_ptrs_,
           QLineEdit* const focus_on_ptr_,
           QString default_value_,
                   QObject* event_filter_,
                   QObject* parent_) :
    hide_ptrs(hide_ptrs_),
    show_ptrs(show_ptrs_),
    enable_ptrs(enable_ptrs_),
    disable_ptrs(disable_ptrs_),
    edit_ptrs(edit_ptrs_),
    auto_focus_ptr(focus_on_ptr_),
    default_value(default_value_),
    event_filter(event_filter_)
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

QMap<QLineEdit*, QString> FillMode::getText()
{
    // Получаем текст из полей ввода, видимых в этом режиме.
    // Видимость не гарантируется и обеспечивается инициализацией
    // списа edit_ptrs
    QMap<QLineEdit*, QString> line_edit_input;
    for (auto uiptr : edit_ptrs){
        line_edit_input[uiptr] = uiptr->text();
    }
    return line_edit_input;
}

void FillMode::setDefaultValue(QLineEdit *uiptr, QString defval)
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

void FillMode::setDefaultFocus()
{
    // Ставим курсор в поле по умолчанию:
    if (auto_focus_ptr){
        auto_focus_ptr->selectAll();
        auto_focus_ptr->setFocus();
    }
}
