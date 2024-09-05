#include "mode.h"
#include "ui_mainwindow.h"
#include <QLineEdit>
#include <QWidget>

Mode::Mode(const std::list<QWidget *> &hideptrs_,
           const std::list<QWidget *> &showptrs_,
           const std::list<QWidget *> &enableptrs_,
           const std::list<QWidget *> &disableptrs_,
           const std::list<QLineEdit *> &editptrs_,
           QString default_value_) :
    hideptrs(hideptrs_),
    showptrs(showptrs_),
    enableptrs(enableptrs_),
    disableptrs(disableptrs_),
    editptrs(editptrs_),
    default_value(default_value_)
{}

//void Mode::changeMode(const Mode& current_mode, const Mode& new_mode)
//{

//}

void Mode::turnOn()
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
}

void Mode::turnOff()
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
}

void Mode::getText(QMap<QString, QString>& inserted_lines)
{
    for (auto uiptr : editptrs){
        inserted_lines[uiptr->objectName()] = uiptr->text();
    }
}

void Mode::setDefVal(QLineEdit *uiptr, QString defval)
{
    defvals[uiptr] = defval;
}

void Mode::clearDefVals()
{
    defvals.clear();
}

void Mode::fillInDefVals()
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
