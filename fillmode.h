#pragma once
#include <list>
#include <QString>
#include <QMap>

class QObject;
class QWidget;
class QLineEdit;
class FillMode
{
private:
   const std::list<QWidget*> hideptrs;
   const std::list<QWidget*> showptrs;
   const std::list<QWidget*> enableptrs;
   const std::list<QWidget*> disableptrs;
   const std::list<QLineEdit*> editptrs;
   QLineEdit* const auto_focus_ptr;
   QString default_value;
   std::map<QLineEdit*, QString> defvals;
   QObject* event_filter;


public:
    FillMode(const std::list<QWidget*>& hideptrs_,
         const std::list<QWidget*>& showptrs_,
         const std::list<QWidget*>& enableptrs_,
         const std::list<QWidget*>& disableptrs_,
         const std::list<QLineEdit*>& editptrs_,
         QLineEdit* const focus_on_ptr_,
         QString default_value_ = "0",
         QObject* event_filter_ = nullptr,
         QObject* parent_ = nullptr);
//    static void changeMode(const Mode& current_mode, const Mode& new_mode);
    void turnOn();
    void turnOff();
    QMap<QLineEdit*, QString> getText();
    void setDefVal(QLineEdit* uiptr, QString defval);
    void clearDefVals();
    void fillInDefVals();
    void setDefFocus();
};
