#include "fillmodebuilder.h"

FillModeBuilder& FillModeBuilder::setHide(QList<QWidget*> hide_ptrs_)
{
    hide_ptrs = hide_ptrs_;
    return *this;
}

FillModeBuilder& FillModeBuilder::setShow(QList<QWidget*> show_ptrs_)
{
    show_ptrs = show_ptrs_;
    return *this;
}

FillModeBuilder& FillModeBuilder::setEnable(QList<QWidget*> enable_ptrs_)
{
    enable_ptrs = enable_ptrs_;
    return *this;
}

FillModeBuilder& FillModeBuilder::setDisable(QList<QWidget*> disable_ptrs_)
{
    disable_ptrs = disable_ptrs_;
    return *this;
}

FillModeBuilder& FillModeBuilder::setEdit(QList<QLineEdit*> edit_ptrs_)
{
    edit_ptrs = edit_ptrs_;
    return *this;
}

FillModeBuilder& FillModeBuilder::setDefaultFocusPtr(QLineEdit* default_focus_ptr_)
{
    default_focus_ptr = default_focus_ptr_;
    return *this;
}

FillModeBuilder& FillModeBuilder::setDefaultValue(QString default_value_)
{
    default_value = default_value_;
    return *this;
}

FillModeBuilder& FillModeBuilder::setCustomDefaults(InputData custom_defaults_)
{
    custom_defaults = custom_defaults_;
    return *this;
}

FillModeBuilder& FillModeBuilder::setEventFilterPtr(QObject *event_filter_)
{
    event_filter = event_filter_;
    return *this;
}

FillMode FillModeBuilder::build() const
{
    return FillMode(hide_ptrs,
                    show_ptrs,
                    enable_ptrs,
                    disable_ptrs,
                    edit_ptrs,
                    default_focus_ptr,
                    default_value,
                    custom_defaults,
                    event_filter);
}

QScopedPointer<FillMode> FillModeBuilder::buildScoped() const
{
    return QScopedPointer<FillMode>(new FillMode(hide_ptrs,
                                                 show_ptrs,
                                                 enable_ptrs,
                                                 disable_ptrs,
                                                 edit_ptrs,
                                                 default_focus_ptr,
                                                 default_value,
                                                 custom_defaults,
                                                 event_filter));
}
