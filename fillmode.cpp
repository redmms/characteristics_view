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

//void Mode::changeMode(const Mode& current_mode, const Mode& new_mode)
//{

//}

void FillMode::turnOn()
{
    // Use it only after turnOff() of previously used mode was called
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
    if (event_filter){
        for (auto uiptr : editptrs){
            uiptr->removeEventFilter(event_filter);
        }
    }
}

QMap<QLineEdit*, QString> FillMode::getText()
{
    QMap<QLineEdit*, QString> line_edit_input;
    for (auto uiptr : editptrs){
        line_edit_input[uiptr] = uiptr->text();
    }
    return line_edit_input;
}

void FillMode::setDefVal(QLineEdit *uiptr, QString defval)
{
    defvals[uiptr] = defval;
}

void FillMode::clearDefVals()
{
    defvals.clear();
}

void FillMode::fillInDefVals()
{
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
    auto_focus_ptr->selectAll();
    auto_focus_ptr->setFocus();
}
