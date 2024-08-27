#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addLineButton_clicked()
{

}


void MainWindow::on_deleteLineButton_clicked()
{
    auto index = ui->tableView->currentIndex();
    ui->tableView->removeRow(index); // Do we need to check if the element exists?
}

