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

//Change stack widget pages
void MainWindow::on_goSplitEvenlyPageButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_goSplitIndPageButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

//button functions for stacked widget page 2

