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
    using InputData = QMap<QObject*, QString>;
    friend class FillModeBuilder;
private:
    // Приватные поля:
    // Описывают, какие элементы UI изменить в данном режиме относительно
    // обычного состояния виджета. Никем не владеем, кроме контейнеров.
    QList<QWidget*> hide_ptrs = {};  // Описывает, что скрывать
    QList<QWidget*> show_ptrs = {};  // Что показать
    QList<QWidget*> enable_ptrs = {};  // Что разгреить
    QList<QWidget*> disable_ptrs = {};  // Что загреить
    QList<QLineEdit*> edit_ptrs = {};  // Где читать и заполнять
    QLineEdit* default_focus_ptr = nullptr; // Что выделять в первую очередь
    QString default_value = "0";  // Чем заполнять
    InputData custom_defaults = {};  // Гибкая настройка чем заполнять
    QObject* event_filter = nullptr;  // Как и когда выделять

    // Конструктор, должен вызываться только через FillModeBuilder
    FillMode(QList<QWidget*> hide_ptrs_,
             QList<QWidget*> show_ptrs_,
             QList<QWidget*> enable_ptrs_,
             QList<QWidget*> disable_ptrs_,
             QList<QLineEdit*> edit_ptrs_,
             QLineEdit* default_focus_ptr_,
             QString default_value_,
             InputData custom_defaults_,
             QObject* event_filter_);

public:
    // Дефолтные конструкторы и операторы
    FillMode() = default;
    FillMode(const FillMode& other) = default;
    FillMode& operator=(const FillMode& other) = default;
    FillMode(FillMode&& other) = default;
    FillMode& operator=(FillMode&& other) = default;

    // Публичные методы:
    void turnOn() const;
    void turnOff() const;
    InputData getText() const;
    void fillInDefaultValues() const;
    void activateDefaultFocus() const;
};
