#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "controllerdialog.h"
#include <QStandardItemModel>
#include <QStandardItem> //? Are this Items defined in QStandardItemModel for sure, or it is better to insure Items are included?
#include <QList>  // same question: QList SHOULD be defined in QStringList or not?

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    model(new QStandardItemModel(0, 7, this))
{
    ui->setupUi(this);
    QList<QString> headers{  // instead of QStringList to avoid extra include
        "способ рассчета",
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
    ui->tableView->resizeColumnsToContents();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addLineButton_clicked()
{
    ControllerDialog controller(this);
    if(controller.exec()){
        QList<QStandardItem*> new_row = controller.getInsertedLine(); // should the dialog be made modal in qt designer (property "windowModality")?
        int insert_idx = ui->tableView->currentIndex().row() + 1;
        if (!insert_idx){
            insert_idx = model->rowCount();
            // this is only for adding order if no row is selected by user
            // this way we always add it to the end of the table instead of
            // beggining
        }
        model->insertRow(insert_idx, new_row);
        ui->tableView->resizeColumnsToContents();
    }
}

void MainWindow::on_deleteLineButton_clicked()
{
    int index = ui->tableView->currentIndex().row();
    model->removeRow(index); // Do we need to check if the element exists?
}
