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
    model(new QStandardItemModel(0, 7, this))
{
    ui->setupUi(this);
    readSettings();
    QList<QString> headers{  // instead of QStringList to avoid extra include
        "способ рассчета", // please, add translations for these phrazes
        "масса",
        "плотность",
        "центр масс",
        "материал",
        "стиль штриховки",
        "угол штриховки"
    };
    for (int i = 0; i < headers.size(); ++i) {
        model->setHeaderData(i, Qt::Horizontal, headers[i], Qt::DisplayRole);
    }
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Connect custom slots
    connect(ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &MainWindow::onSelectionChanged);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings("MMD18soft", "DetailParameteres");
    settings.setValue("geometry", saveGeometry());
    QWidget::closeEvent(event);
}

void MainWindow::readSettings()
{
    QSettings settings("MMD18soft", "DetailParameteres");
    restoreGeometry(settings.value("geometry").toByteArray());
}

void MainWindow::on_addLineButton_clicked()
{
    ControllerDialog controller(this);
    if(controller.exec()){
        QList<QStandardItem*> new_row = controller.getInsertedLine();
        int insert_idx = ui->tableView->currentIndex().row() + 1;
        if (!insert_idx){
            insert_idx = model->rowCount();
            // this is for adding order if no row is selected by user
            // this way we always add it to the end of the table instead of
            // beggining, it goes in pair with inserting
            // (appending wouldn't need it)
        }
        model->insertRow(insert_idx, new_row);
    }
}

void MainWindow::on_deleteLineButton_clicked()
{
    int index = ui->tableView->currentIndex().row();
    if (index >= 0 && index < model->rowCount()){
        model->removeRow(index);
    }
}

void MainWindow::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    QModelIndexList indexes = selected.indexes();
    ui->deleteLineButton->setEnabled(!indexes.isEmpty());
}
