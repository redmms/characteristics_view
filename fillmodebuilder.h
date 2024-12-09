#pragma once
#include "fillmode.h"

class FillModeBuilder
{
    using InputData = QMap<QObject*, QString>;
private:
    // Приватные поля:
    QList<QWidget*> hide_ptrs = {};  // Описывает, что скрывать
    QList<QWidget*> show_ptrs = {};  // Что показать
    QList<QWidget*> enable_ptrs = {};  // Что разгреить
    QList<QWidget*> disable_ptrs = {};  // Что загреить
    QList<QLineEdit*> edit_ptrs = {};  // Где читать и заполнять
    QLineEdit* default_focus_ptr = nullptr; // Что выделять в первую очередь
    QString default_value = "0";  // Чем заполнять
    InputData custom_defaults = {};  // Гибкая настройка чем заполнять
    QObject* event_filter = nullptr;  // Как и когда выделять

public:
    // Сэттеры:
    FillModeBuilder& setHide(QList<QWidget*> hide_ptrs_);
    FillModeBuilder& setShow(QList<QWidget*> show_ptrs_);
    FillModeBuilder& setEnable(QList<QWidget*> enable_ptrs_);
    FillModeBuilder& setDisable(QList<QWidget*> disable_ptrs_);
    FillModeBuilder& setEdit(QList<QLineEdit*> edit_ptrs_);
    FillModeBuilder& setDefaultFocusPtr(QLineEdit* default_focus_ptr_);
    FillModeBuilder& setDefaultValue(QString default_value_);
    FillModeBuilder& setCustomDefaults(InputData custom_defaults_);
    FillModeBuilder& setEventFilterPtr(QObject* event_filter_);

    // Основной метод:
    FillMode build() const;
    QScopedPointer<FillMode> buildScoped() const;
};
