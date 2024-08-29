#pragma once // is it Ok in Qt programming to replace those defines by #pragma once?
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QStandardItemModel;
class MainWindow : public QMainWindow
{
    Q_OBJECT
    Ui::MainWindow* ui;
    QStandardItemModel* model; // is this style Ok?

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addLineButton_clicked();
    void on_deleteLineButton_clicked();
};
