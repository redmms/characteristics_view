#pragma once
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class PartModel;
class QCloseEvent;
class QItemSelection;
class QSortFilterProxyModel;
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    // Приватные поля:
    Ui::MainWindow* ui;  // Указатель на UI
    PartModel* model;  // Табличная модель с деталями, в иерархии
    QSortFilterProxyModel* proxy;  // Прокси модель сортировки, в иерархии

    // Приватные методы:
    void closeEvent(QCloseEvent* event);  // Для сохранения геометрии
    void readSettings();  // Для восстановления геометрии

public:
    // Конструктор:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Автоген слоты для UI:
    void on_addLineButton_clicked();
    void on_deleteLineButton_clicked();

    // Пользовательский слот UI:
    void onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
};
