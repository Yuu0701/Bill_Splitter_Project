#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <debtGraph.h>
#include <DebtTree.h>
#include <Transaction.h>
#include <Bill.h>
#include <unordered_map>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_movePageTwoButton_clicked();

    void on_goPage1Button_clicked();

    void on_goBackPage2Button_clicked();

    void on_addNameButton_clicked();

    void on_newTransactionButton_clicked();

    void on_TransHistoryButton_clicked();

    void on_splitIndButton_clicked();

    void on_debtShareButton_clicked();

    void on_fifteenTipButton_clicked();

    void on_eighteenTipButton_clicked();

    void on_twentyTipButton_clicked();

    void on_twentyFiveTipButton_clicked();

    void on_calculateButton_clicked();

    void on_goBackPage3Button_clicked();

    void on_goMenuButton_clicked();

    void on_addFeeButton_clicked();

    void on_splitEvenlyButton_clicked();

    void on_backToMenuPageButton_clicked();

    void on_GoBackMenuButton_clicked();

    void on_makePaymentButton_clicked();

    void on_undoPaymentButton_clicked();

    void on_loadDebtGraphButton_clicked();

    void on_loadListButton_clicked();

    void on_checkDebtButton_clicked();

private:
    Ui::MainWindow *ui;
    vector<string> participants;
    unordered_map<string, double> debtBalance;
    Graph graph;
    TreeBST tree;
    stack<Bill> billHistory;
    stack<Transaction> transactionHistory;
    double totalHolder;

    double calculateBill();
    void newBalance();
    void addBillHistoryTabel(double total, string& payer, vector<string> debtors);
    double calculateTip(double tipPercent);
    double calculateShare();
    void displayGraphQt(Graph& g);
};
#endif // MAINWINDOW_H
