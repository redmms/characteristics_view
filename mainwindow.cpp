#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "controllerdialog.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QList>
#include <QSettings>
#include <QItemSelection>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    model(new DetailModel(0, this)),
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
    QSettings settings("MMD18soft", "DetailParameteres");
    settings.setValue("geometry", saveGeometry());
    QWidget::closeEvent(event);
}

void MainWindow::readSettings()
{
    // Восстанавливаем геометрию окна:
    QSettings settings("MMD18soft", "DetailParameteres");
    restoreGeometry(settings.value("geometry").toByteArray());
}

void MainWindow::on_addLineButton_clicked()
{
    // Запускаем диалоговое окно контроллера:
    ControllerDialog controller(this);
    if(controller.exec()){
        // Сохраняем данные из контроллера в виде DetailItem:
        DetailItem* new_row = controller.getInsertedLine();

        // Проверяем индекс строки:
        int insert_idx = ui->tableView->currentIndex().row() + 1;
        if (!insert_idx){
            insert_idx = model->rowCount();
            // this is for adding order if no row is selected by user
            // this way we always add it to the end of the table instead of
            // beggining, it goes in pair with inserting
            // (appending wouldn't need it)
        }

        // Вставляем строку-деталь
        model->insertRow(insert_idx, new_row);

        // Чтобы проверить работу с DetailItem по указателю добавьте
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
    QModelIndexList indexes = selected.indexes();
    ui->deleteLineButton->setEnabled(!indexes.isEmpty());
}
