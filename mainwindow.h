#pragma once
#include <QMainWindow>
#include <QString>
#include <unordered_map> // is it ok, or map is better?

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QStandardItemModel;
class QCloseEvent;
class QItemSelection;
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow* ui;
    QStandardItemModel* model;
    void closeEvent(QCloseEvent* event);
    void readSettings();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addLineButton_clicked();
    void on_deleteLineButton_clicked();
    void onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
};
