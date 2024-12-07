#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <vector>
#include <string>
#include <stack>
using namespace std;

struct Transaction {
    string payer;
    double billss;
    double tax;
    double tip;
    double gratuity;
    vector<string> debtor;

    Transaction(const string& _payer, double _bill, double _tax, double _tip, double _gratuity, vector<string>& debtors){
        payer = _payer;
        billss = _bill;
        tax = _tax;
        tip = _tip;
        gratuity = _gratuity;
        debtor = debtors;
    }
};

class TransactionHistory {
private:
    stack<Transaction> transactions;
public:

    void addTransaction(Transaction& transaction) {
        transactions.push(transaction);
    }
};

#endif // TRANSACTION_H
