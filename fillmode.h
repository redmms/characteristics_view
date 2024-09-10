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
    // Приватные поля:
    // Описывают, какие элементы UI изменить в данном режиме относительно
    // обычного состояния виджета.
    const std::list<QWidget*> hideptrs;  // Описывает, что скрывать
    const std::list<QWidget*> showptrs;  // Что показать
    const std::list<QWidget*> enableptrs;  // Что разгреить
    const std::list<QWidget*> disableptrs;  // Что загреить
    const std::list<QLineEdit*> editptrs;  // Где читать и заполнять
    QLineEdit* const auto_focus_ptr; // Что выделять в первую очередь
    QString default_value;  // Чем заполнять
    std::map<QLineEdit*, QString> defvals;  // Гибкая настройка чем заполнять
    QObject* event_filter;  // Как и когда выделять


public:
   // Конструктор:
   FillMode(const std::list<QWidget*>& hideptrs_,
         const std::list<QWidget*>& showptrs_,
         const std::list<QWidget*>& enableptrs_,
         const std::list<QWidget*>& disableptrs_,
         const std::list<QLineEdit*>& editptrs_,
         QLineEdit* const focus_on_ptr_,
         QString default_value_ = "0",
         QObject* event_filter_ = nullptr,
         QObject* parent_ = nullptr);

    // Публичные методы:
    void turnOn();
    void turnOff();
    QMap<QLineEdit*, QString> getText();
    void setDefVal(QLineEdit* uiptr, QString defval);
    void clearDefVals();
    void fillInDefVals();
    void setDefFocus();
};
