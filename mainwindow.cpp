#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "partmodel.h"
#include "controllerdialog.h"
#include <QList>
#include <QSettings>
#include <QItemSelection>
#include <QTimer>
#include <QString>
#include <QSortFilterProxyModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    model(new PartModel(0, this)),
    proxy(new QSortFilterProxyModel(this))
{
    ui->setupUi(this);

    // Восстанавливаем геометрию окна:
    readSettings();

    // Устанавливаем прокси модель для сортировки.
    // Заголовки таблицы оставляем по умолчанию.
    proxy->setSourceModel(model);
    ui->tableView->setModel(proxy);

    // Подгоняем таблицу под виджет
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Подключаем пользовательский слот:
    connect(ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &MainWindow::onSelectionChanged);
}

MainWindow::~MainWindow()
{
    // Освобождаем память:
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // Сохраняем геометрию окна:
    QSettings settings("MMD18soft", "ControllerDialog");
    settings.setValue("geometry", saveGeometry());
    QWidget::closeEvent(event);
}

void MainWindow::readSettings()
{
    // Восстанавливаем геометрию окна:
    QSettings settings("MMD18soft", "ControllerDialog");
    restoreGeometry(settings.value("geometry").toByteArray());
}

void MainWindow::on_addLineButton_clicked()
{
    // Запускаем диалоговое окно контроллера:
    ControllerDialog controller(this);
    if(controller.exec()){
        // Сохраняем данные из контроллера в виде PartItem:
        PartItem* new_row = controller.getInsertedLine(this);

        // Вставляем строку-деталь и передам владение модели
        model->appendRow(new_row);

        // Чтобы проверить работу с PartItem по указателю добавьте
        // следующие строки после добавления детали в модель:
//        new_row->setMaterialName("Changed Excluded part Bla Bla Bla");
//        new_row->setCenter({99999, 126789, 21234});
    }
}

void MainWindow::on_deleteLineButton_clicked()
{
    // Удаляем строку:
    int index = ui->tableView->currentIndex().row();
    if (index >= 0 && index < model->rowCount()){
        model->removeRow(index);
    }
}

void MainWindow::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    // Включаем/отключаем кнопку Удалить строку:
    QModelIndexList indexes = ui->tableView->selectionModel()->selectedIndexes();
    ui->deleteLineButton->setEnabled(!indexes.isEmpty());
}
