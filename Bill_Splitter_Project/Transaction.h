#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <vector>
#include <string>
using namespace std;

struct Transaction {
    string payer;
    string owed;
    double amount;

    Transaction(string& _payer, string& payee, double _amount){
        payer = _payer;
        owed = payee;
        amount = _amount;
    }
};

#endif // TRANSACTION_H
