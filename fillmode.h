#pragma once
#include <QList>
#include <QString>
#include <QMap>
#include <QScopedPointer>

class QObject;
class QWidget;
class QLineEdit;
class FillMode
{
private:
    // Приватные поля:
    // Описывают, какие элементы UI изменить в данном режиме относительно
    // обычного состояния виджета. Никем не владеем, кроме контейнеров.
    const QList<QWidget*> hide_ptrs;  // Описывает, что скрывать
    const QList<QWidget*> show_ptrs;  // Что показать
    const QList<QWidget*> enable_ptrs;  // Что разгреить
    const QList<QWidget*> disable_ptrs;  // Что загреить
    const QList<QLineEdit*> edit_ptrs;  // Где читать и заполнять
    QLineEdit* const auto_focus_ptr; // Что выделять в первую очередь
    QString default_value;  // Чем заполнять
    QMap<QLineEdit*, QString> default_values;  // Гибкая настройка чем заполнять
    QObject* event_filter;  // Как и когда выделять


public:
   // Конструктор:
   FillMode(const QList<QWidget*>& hide_ptrs_,
         const QList<QWidget*>& show_ptrs_,
         const QList<QWidget*>& enable_ptrs_,
         const QList<QWidget*>& disable_ptrs_,
         const QList<QLineEdit*>& edit_ptrs_,
         QLineEdit* const focus_on_ptr_,
         QString default_value_ = "0",
         QObject* event_filter_ = nullptr,
         QObject* parent_ = nullptr);

    // Публичные методы:
    void turnOn();
    void turnOff();
    QMap<QLineEdit*, QString> getText();
    void setDefaultValue(QLineEdit* uiptr, QString defval);
    void clearDefaultValues();
    void fillInDefaultValues();
    void setDefaultFocus();
};
