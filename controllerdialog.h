#pragma once
#include <QDialog>
#include <QList>
#include <cstdint>

namespace Ui { class ParamDialog; }
class QStandardItem;
class QRegularExpressionValidator;
class ControllerDialog : public QDialog
{
    enum statenum : uint32_t {  // is it Ok to place it here? where else?
        massLabel    = 1 << 0,
        massEdit     = 1 << 1,
        densityLabel = 1 << 2,
        densityEdit  = 1 << 3,
        checkBox     = 1 << 4,
        xLabel       = 1 << 5,
        xEdit        = 1 << 6,
        yLabel       = 1 << 7,
        yEdit        = 1 << 8,
        zLabel       = 1 << 9,
        zEdit        = 1 << 10,
        styleBox     = 1 << 11,
        angleEdit    = 1 << 12
    };

    Q_OBJECT
    Ui::ParamDialog *ui;
    QList<QStandardItem*> insertedLine;
    QRegularExpressionValidator* validator;
    QList<QWidget*> uipointers;
    uint32_t all;  // should I place it in a structure? would it be Ok to define the structure inside this Dialog class declaration?
    uint32_t coord;
    uint32_t center;
    uint32_t massShow;
    uint32_t massEnable;
    uint32_t densityShow;
    uint32_t densityEnable;
    uint32_t copyShow;
    uint32_t copyEnable;
    uint32_t currentShow;
    uint32_t currentEnable;
    void changeRegime(uint32_t showFlags, uint32_t enableFlags);    // is this style of .h file Ok?

public:
    explicit ControllerDialog(QWidget *parent = nullptr);
    ~ControllerDialog();
    QList<QStandardItem*> getInsertedLine();

private slots:
    void on_cancelButton_clicked();
    void on_checkBox_stateChanged(int state);
    void on_methodBox_currentIndexChanged(int index);
    void on_applyButton_clicked();
};
