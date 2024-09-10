#include "fillmode.h"
#include "ui_mainwindow.h"
#include <QLineEdit>
#include <QWidget>

FillMode::FillMode(const std::list<QWidget *> &hideptrs_,
           const std::list<QWidget *> &showptrs_,
           const std::list<QWidget *> &enableptrs_,
           const std::list<QWidget *> &disableptrs_,
           const std::list<QLineEdit *> &editptrs_,
           QLineEdit* const focus_on_ptr_,
           QString default_value_,
                   QObject* event_filter_,
                   QObject* parent_) :
    hideptrs(hideptrs_),
    showptrs(showptrs_),
    enableptrs(enableptrs_),
    disableptrs(disableptrs_),
    editptrs(editptrs_),
    auto_focus_ptr(focus_on_ptr_),
    default_value(default_value_),
    event_filter(event_filter_)
{}

void FillMode::turnOn()
{
    // Включение режима:
    // Использовать только после turnOff() предыдущего режима
    for (auto uiptr : hideptrs){
        uiptr->hide();
    }
    for (auto uiptr : showptrs){
        uiptr->show();
    }
    for (auto uiptr : enableptrs){
        uiptr->setEnabled(true);
    }
    for (auto uiptr : disableptrs){
        uiptr->setEnabled(false);
    }

    // Установка фильтра событий для выделения ввода из полей UI, но можно
    // использовать и для другого:
    if (event_filter){
        for (auto uiptr : editptrs){
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
    for (auto uiptr : hideptrs){
        uiptr->show();
    }
    for (auto uiptr : showptrs){
        uiptr->hide();
    }
    for (auto uiptr : enableptrs){
        uiptr->setEnabled(false);
    }
    for (auto uiptr : disableptrs){
        uiptr->setEnabled(true);
    }

    // Отключения всех фильтров событий, что могли установить ранее:
    if (event_filter){
        for (auto uiptr : editptrs){
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
    for (auto uiptr : editptrs){
        line_edit_input[uiptr] = uiptr->text();
    }
    return line_edit_input;
}

void FillMode::setDefVal(QLineEdit *uiptr, QString defval)
{
    // Заполняем поле ввода значением по умолчанию:
    defvals[uiptr] = defval;
}

void FillMode::clearDefVals()
{
    // Очищаем словарь пользовательских дефолтных значений:
    defvals.clear();
}

void FillMode::fillInDefVals()
{
    // Заполняем поля ввода пользовательскими значениями по умолчанию:
    for (auto uiptr : editptrs){
        if (defvals.count(uiptr)){
            uiptr->setText(defvals[uiptr]);
        }
        else{
            uiptr->setText(default_value);
        }
    }
}

void FillMode::setDefFocus()
{
    // Ставим курсор в поле по умолчанию:
    if (auto_focus_ptr){
        auto_focus_ptr->selectAll();
        auto_focus_ptr->setFocus();
    }
}
