#pragma once
#include <list>
#include <QString>
#include <QMap>

class QWidget;
class QLineEdit;
class Mode
{
private:
   const std::list<QWidget*> hideptrs;
   const std::list<QWidget*> showptrs;
   const std::list<QWidget*> enableptrs;
   const std::list<QWidget*> disableptrs;
   const std::list<QLineEdit*> editptrs;
   QString default_value;
   std::map<QLineEdit*, QString> defvals;

public:
    Mode(const std::list<QWidget*>& hideptrs_,
         const std::list<QWidget*>& showptrs_,
         const std::list<QWidget*>& enableptrs_,
         const std::list<QWidget*>& disableptrs_,
         const std::list<QLineEdit*>& editptrs_,
         QString default_value_ = "0");
//    static void changeMode(const Mode& current_mode, const Mode& new_mode);
    void turnOn();
    void turnOff();
    void getText(QMap<QString, QString>& inserted_lines);
    void setDefVal(QLineEdit* uiptr, QString defval);
    void clearDefVals();
    void fillInDefVals();
};