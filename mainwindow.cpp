#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QList>
#include <QStandardItem> //?
#include "paramdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(new QStandardItemModel(this))
{
    ui->setupUi(this);
    model->setHeaderData(0, Qt::Horizontal, "способ рассчета", Qt::DisplayRole);
    model->setHeaderData(1, Qt::Horizontal, "масса", Qt::DisplayRole);
    model->setHeaderData(2, Qt::Horizontal, "плотность", Qt::DisplayRole);
    model->setHeaderData(3, Qt::Horizontal, "центр масс", Qt::DisplayRole);
    model->setHeaderData(4, Qt::Horizontal, "материал", Qt::DisplayRole);
    model->setHeaderData(5, Qt::Horizontal, "стиль штриховки", Qt::DisplayRole);
    model->setHeaderData(6, Qt::Horizontal, "угол штриховки", Qt::DisplayRole);


    ui->tableView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addLineButton_clicked()
{
    ParamDialog dialog(this);
    if(dialog.exec()){
        QList<QStandardItem*> new_row = dialog.getInsertedLine(); // should the dialog be made modal in qt designer?
        model->insertRow(model->rowCount(), new_row);
    }
}


void MainWindow::on_deleteLineButton_clicked()
{
    int index = ui->tableView->currentIndex().row();
    int debug_count = model->rowCount(); // don't forget
    model->removeRow(index); // Do we need to check if the element exists?
}

