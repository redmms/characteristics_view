#pragma once
#include <QList>
#include <QString>
#include <QMap>

class QObject;
class QWidget;
class QLineEdit;
class FillMode
{
    using InsertData = QMap<QLineEdit*, QString>;
private:
    // Приватные поля:
    // Описывают, какие элементы UI изменить в данном режиме относительно
    // обычного состояния виджета. Никем не владеем, кроме контейнеров.
    QList<QWidget*> hide_ptrs;  // Описывает, что скрывать
    QList<QWidget*> show_ptrs;  // Что показать
    QList<QWidget*> enable_ptrs;  // Что разгреить
    QList<QWidget*> disable_ptrs;  // Что загреить
    QList<QLineEdit*> edit_ptrs;  // Где читать и заполнять
    QLineEdit* default_focus_ptr; // Что выделять в первую очередь
    QString default_value;  // Чем заполнять
    InsertData default_values;  // Гибкая настройка чем заполнять
    QObject* event_filter;  // Как и когда выделять

public:
    // Конструкторы:
    FillMode(const QList<QWidget*>& hide_ptrs_,
         const QList<QWidget*>& show_ptrs_,
         const QList<QWidget*>& enable_ptrs_,
         const QList<QWidget*>& disable_ptrs_,
         const QList<QLineEdit*>& edit_ptrs_,
         QLineEdit* const default_focus_ptr_,
         QString default_value_ = "0",
         QObject* event_filter_ = nullptr);
    FillMode();

    // Публичные методы:
    void turnOn();
    void turnOff();
    QMap<QLineEdit*, QString> getText();
    void setDefaultValue(QLineEdit* uiptr, QString defval);
    void clearDefaultValues();
    void fillInDefaultValues();
    void activateDefaultFocus();

    // Сэттеры:
    void setHide(QList<QWidget*> hide_ptrs_);
    void setShow(QList<QWidget*> show_ptrs_);
    void setEnable(QList<QWidget*> enable_ptrs_);
    void setDisable(QList<QWidget*> disable_ptrs_);
    void setEdit(QList<QLineEdit*> edit_ptrs_);
    void setDefaultFocusPtr(QLineEdit* default_focus_ptr_);
    void setDefaultValue(QString default_value_);
    void setDefaultValues(InsertData default_values_);
    void setEventFilterPtr(QObject* event_filter_);
};
