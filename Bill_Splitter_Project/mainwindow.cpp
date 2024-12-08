#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
using namespace std;

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

//calculation functions
double MainWindow::calculateBill(){
    subtotal = ui->subtotalLineEdit->text().toDouble();
    tax = ui->taxLineEdit->text().toDouble();
    gratuity = ui->gratuityLineEdit->text().toDouble();
    tip = ui->tipLineEdit->text().toDouble();

    double total = subtotal + tax + gratuity + tip;
    return total;
}

double MainWindow::calculateShare(){
    double total = ui->billTotalLineEdit->text().toDouble();
    double num = ui->NumPeopleLineEdit->text().toDouble();

    double share = total / num;
    return share;
}

void MainWindow::newBalance(){

}

double MainWindow::calculateTip(double tipPercent){
    double temp = ui->subtotalLineEdit->text().toDouble();
    if (temp <= 0){
        QMessageBox::information(this, "Info", "Please enter subtotal before choosing tip options");
        return 0.0;
    }
    else{
        temp *= tipPercent;
        return temp;
    }
}
/*
    vector<string> participants;
    map<string, double> debtBalance;
    string payer;
    double subtotal;
    double tax;
    double tip;
    double gratuity;
*/

//STACK WIDGET PAGE 1
//button functions
void MainWindow::on_addNameButton_clicked()
{
    string personName = ui->nameLineEdit->text().toStdString();
    if (!personName.empty()){
        participants.push_back(personName);
        ui->nameLineEdit->clear();
    }
}

//STACK WIDGET PAGE 3
//tip button functions
void MainWindow::on_fifteenTipButton_clicked()
{
    int tip = 15;
    double percent = tip / 100.0;

    double total = calculateTip(percent);
    QString QTemp = QString::number(total, 'f', 2);

    ui->tipLineEdit->setText(QTemp);
}

void MainWindow::on_eighteenTipButton_clicked()
{
    int tip = 18;
    double percent = tip / 100.0;

    double total = calculateTip(percent);
    QString QTemp = QString::number(total, 'f', 2);

    ui->tipLineEdit->setText(QTemp);
}

void MainWindow::on_twentyTipButton_clicked()
{
    int tip = 20;
    double percent = tip / 100.0;

    double total = calculateTip(percent);
    QString QTemp = QString::number(total, 'f', 2);

    ui->tipLineEdit->setText(QTemp);
}

void MainWindow::on_twentyFiveTipButton_clicked()
{
    int tip = 25;
    double percent = tip / 100.0;

    double total = calculateTip(percent);
    QString QTemp = QString::number(total, 'f', 2);

    ui->tipLineEdit->setText(QTemp);
}

//transaction calculation and split button functions
void MainWindow::on_calculateButton_clicked()
{
    double temp = calculateBill();
    QString QTemp = QString::number(temp, 'f', 2);

    //display on screen
    ui->billTotalLineEdit->setText(QTemp);
    ui->totalLineEdit->setText(ui->billTotalLineEdit->text());
}

void MainWindow::on_splitEvenlyButton_clicked()
{
    double share = calculateShare();

    //format double into QString with maximum 2 decimals
    QString qTemp = QString::number(share, 'f', 2);

    //update graph, tree, transaction history
}


//STACK WIDGET PAGE 4
void MainWindow::on_addFeeButton_clicked()
{
    //update graph, tree, and transaction history
}

//button functions to move pages
void MainWindow::on_movePageTwoButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_goPage1Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_goBackPage2Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_newTransactionButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_TransHistoryButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_splitIndButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_debtShareButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_goBackPage3Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_goMenuButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_backToMenuPageButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_GoBackMenuButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

