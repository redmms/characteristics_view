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
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    model(new PartModel(0, boost::pfr::tuple_size_v<Part>, this)),
    proxy(new QSortFilterProxyModel(this))
{
    ui->setupUi(this);

    // Восстанавливаем геометрию окна:
    readSettings();

    // Задаем заголовки таблице:
    model->setHeaderData(0, "способ расчёта");
    model->setHeaderData(1, "масса");
    model->setHeaderData(2, "плотность");
    model->setHeaderData(3, "центр масс");
    model->setHeaderData(4, "материал");
    model->setHeaderData(5, "стиль штриховки");
    model->setHeaderData(6, "угол штриховки");

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
    bool success = restoreGeometry(settings.value("geometry").toByteArray());
    if (!success){
        qDebug() << "Couldn't restore geometry";
    }
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

//        PartItem* item = model->getPart(0);
//        delete item;
    }
}

void MainWindow::on_deleteLineButton_clicked()
{
    // Удаляем строку:
    int index = ui->tableView->currentIndex().row();
    if (index >= 0 && index < model->rowCount()){
        bool success = model->removeRow(index);
        if (!success){
            qDebug() << "Couldn't remove a row";
        }
    }
}

void MainWindow::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    // Включаем/отключаем кнопку Удалить строку:
    Q_UNUSED(selected)
    Q_UNUSED(deselected)
    QModelIndexList indexes = ui->tableView->selectionModel()->selectedIndexes();
    ui->deleteLineButton->setEnabled(!indexes.isEmpty());
}
