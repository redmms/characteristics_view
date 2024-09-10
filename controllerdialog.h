#pragma once
#include "fillmode.h"
#include <QDialog>
#include <QList>
#include "detailitem.h"
#include <QMap>
#include "enums.h"

namespace Ui { class ControllerDialog; }
class QStandardItem;
class QRegularExpressionValidator;
class FillMode;
class ControllerDialog : public QDialog
{
    Q_OBJECT
private:
    Ui::ControllerDialog *ui;
    DetailItem* detail;
    QRegularExpressionValidator* validator;
    QMap<ModeNum, FillMode*> modes;
    ModeNum current_mode;

public:
    explicit ControllerDialog(QWidget *parent = nullptr);
    ~ControllerDialog();
    DetailItem* getInsertedLine();
    bool eventFilter(QObject *object, QEvent *event);

private slots:
    void on_cancelButton_clicked();
    void on_methodBox_currentIndexChanged(int index);
    void on_applyButton_clicked();
};
