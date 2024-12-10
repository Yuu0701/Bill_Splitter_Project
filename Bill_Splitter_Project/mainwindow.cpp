#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <stack>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //table setup for transaction history
    ui->tableWidget_payment->setColumnCount(3);
    ui->tableWidget_payment->setHorizontalHeaderLabels({"Payer", "Payee", "Amount"});
    ui->tableWidget_payment->setSelectionBehavior(QTableView::SelectRows);

    //table setup for bill history
    ui->tableWidget_bill->setColumnCount(3);
    ui->tableWidget_bill->setHorizontalHeaderLabels({"Who Paid", "How Much", "Who Owes"});
    ui->tableWidget_bill->setSelectionBehavior(QTableView::SelectRows);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//calculation functions
double MainWindow::calculateBill(){
    double subtotal = ui->subtotalLineEdit->text().toDouble();
    double tax = ui->taxLineEdit->text().toDouble();
    double gratuity = ui->gratuityLineEdit->text().toDouble();
    double tip = ui->tipLineEdit->text().toDouble();

    double total = subtotal + tax + gratuity + tip;
    return total;
}

double MainWindow::calculateShare(){
    double total = ui->billTotalLineEdit->text().toDouble();
    double num = ui->NumPeopleLineEdit->text().toDouble();

    double share = total / num;
    return share;
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
    totalHolder = temp;
    QString QTemp = QString::number(temp, 'f', 2);

    //display on screen
    ui->billTotalLineEdit->setText(QTemp);
    ui->totalLineEdit->setText(ui->billTotalLineEdit->text());
}

void MainWindow::on_splitEvenlyButton_clicked()
{
    double subtotal = ui->subtotalLineEdit->text().toDouble();
    double tax = ui->taxLineEdit->text().toDouble();
    double tip = ui->tipLineEdit->text().toDouble();
    double gratuity = ui->gratuityLineEdit->text().toDouble();

    double share = calculateShare();

    //format double into QString with maximum 2 decimals
    QString qTemp = QString::number(share, 'f', 2);

    string payer = ui->payerLineEdit->text().toStdString();

    //update graph, tree, transaction history
    for (auto& person : participants){
        if (person != payer){
            debtBalance[person] = share;
            graph.addDebtEdge(person, payer, share);
            tree.insert(person, share);
        }
    }
    Bill newBill(payer, subtotal, tax, tip, gratuity, participants);
    billHistory.push(newBill);

    double total = subtotal + tax + tip + gratuity;
    addBillHistoryTabel(total, payer, participants);

    ui->stackedWidget->setCurrentIndex(1);
}


//STACK WIDGET PAGE 4
void MainWindow::on_addFeeButton_clicked()
{
    string payer = ui->payerLineEdit->text().toStdString();
    string debtor = ui->nameDebtorLineEdit->text().toStdString();
    double share = ui->shareAmountLineEdit->text().toDouble();
    double total = ui->totalLineEdit->text().toDouble();

    QString value = QString::number((total - share), 'f', 2);
    ui->totalLineEdit->setText(value);

    //update graph, tree, and transaction history
    graph.addDebtEdge(debtor, payer, share);
    tree.insert(debtor, share);
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
    ui->payerLineEdit->clear();
    ui->subtotalLineEdit->clear();
    ui->taxLineEdit->clear();
    ui->tipLineEdit->clear();
    ui->gratuityLineEdit->clear();
    ui->billTotalLineEdit->clear();
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_TransHistoryButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_splitIndButton_clicked()
{
    double total = ui->billTotalLineEdit->text().toDouble();
    string payer = ui->payerLineEdit->text().toStdString();

    addBillHistoryTabel(total, payer, participants);
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_debtShareButton_clicked()
{
    ui->debtGraphTextEdit->clear();
    ui->listWidgetTree->clear();
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

//payment widget screen
void MainWindow::on_makePaymentButton_clicked()
{
    string payers = ui->payingLineEdit->text().toStdString();
    string payees = ui->payeeLineEdit->text().toStdString();
    double amounts = ui->payAmountLineEdit->text().toDouble();

    //update graph and tree
    graph.reduceDebt(payers, payees, amounts);
    double oldDebt = tree.getDebt(payers);
    tree.remove(payers, amounts);
    tree.insert(payers, amounts - oldDebt);

    ui->tableWidget_payment->setRowCount(0);

    Transaction newTransHistory(payers, payees, amounts);
    transactionHistory.push(newTransHistory);
    stack<Transaction> copiedStack(transactionHistory);

    while(!copiedStack.empty()){
        Transaction temp = copiedStack.top();
        QString payer = QString::fromStdString(temp.payer);
        QString payee = QString::fromStdString(temp.owed);
        QString amount = QString::number(temp.amount, 'f', 2);

        if (payer.isEmpty()){
            return;
        }
        if (payee.isEmpty()){
            return;
        }
        if (amount.isEmpty()){
            return;
        }
        const int row = ui->tableWidget_payment->rowCount();
        ui->tableWidget_payment->insertRow(row);
        ui->tableWidget_payment->setItem(row, 0, new QTableWidgetItem(payer));
        ui->tableWidget_payment->setItem(row, 1, new QTableWidgetItem(payee));
        ui->tableWidget_payment->setItem(row, 2, new QTableWidgetItem(amount));

        copiedStack.pop();
    }
}

void MainWindow::addBillHistoryTabel(double total, string& payer, vector<string> debtors){
    QString totalBill = QString::number(total, 'f', 2);
    QString personPaid = QString::fromStdString(payer);
    QString people;
    for (auto& debtor : debtors){
        if (debtor != payer){
            people += QString::fromStdString(debtor) + " ";
        }
    }

    const int row = ui->tableWidget_bill->rowCount();
    ui->tableWidget_bill->insertRow(row);
    ui->tableWidget_bill->setItem(row, 0, new QTableWidgetItem(personPaid));
    ui->tableWidget_bill->setItem(row, 1, new QTableWidgetItem(totalBill));
    ui->tableWidget_bill->setItem(row, 2, new QTableWidgetItem(people));
}


void MainWindow::on_undoPaymentButton_clicked()
{
    string payers = ui->payingLineEdit->text().toStdString();
    string payees = ui->payeeLineEdit->text().toStdString();
    double amounts = ui->payAmountLineEdit->text().toDouble();

    ui->tableWidget_payment->removeRow(0);

    transactionHistory.pop();

    //update graph and tree
    graph.increaseDebt(payers, payees, amounts);
    double oldDebt = tree.getDebt(payers);
    tree.remove(payers, amounts);
    tree.insert(payers, amounts + oldDebt);

}


void MainWindow::on_loadDebtGraphButton_clicked()
{
    displayGraphQt(graph);
}

void MainWindow::displayGraphQt(Graph& g){
    QString x = "Member Graph Relationship: \n";
    x += "(ex: (person) -> ((owes this person), (by this much debt))) \n";
    x += "\n";

    auto& debtG = g.getGraph();

    for (auto& [from, pair] : debtG){
        x += QString::fromStdString(from);
        for (auto& [to, amount] : pair){
            x += " -> (" + QString::fromStdString(to) + ", $" + QString::number(amount, 'f', 2) + ")";
        }
        x += "\n";
    }

    ui->debtGraphTextEdit->setPlainText(x);
}


void MainWindow::on_loadListButton_clicked()
{
    ui->listWidgetTree->clear();

    for (auto& i : participants){
        QString name = QString::fromStdString(i);
        ui->listWidgetTree->addItem(name);
    }
}


void MainWindow::on_checkDebtButton_clicked()
{
    for (auto& i : participants){
        double debt = tree.getDebt(i);

        if (ui->listWidgetTree->currentItem()->text() == i){
            QString output;
            output += "Total Debt for " + QString::fromStdString(i) + ": $" + QString::number(debt, 'f', 2);

            QMessageBox::information(this, "Debt Info", output);
        }
    }
}

















