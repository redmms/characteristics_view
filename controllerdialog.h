#pragma once
#include "detailmode.h"
#include <QDialog>
#include <QList>
#include "detailitem.h"
#include <QMap>
#include "enums.h"

namespace Ui { class ControllerDialog; }
class QStandardItem;
class QRegularExpressionValidator;
class Mode;
class ControllerDialog : public QDialog
{
    Q_OBJECT
private:
    Ui::ControllerDialog *ui;
    DetailItem* detail;
    QRegularExpressionValidator* validator;
    QMap<ModeNum, Mode*> modes;
    ModeNum current_mode;

public:
    explicit ControllerDialog(QWidget *parent = nullptr);
    ~ControllerDialog();
    DetailItem* getInsertedLine();

private slots:
    void on_cancelButton_clicked();
    void on_methodBox_currentIndexChanged(int index);
    void on_applyButton_clicked();
};
