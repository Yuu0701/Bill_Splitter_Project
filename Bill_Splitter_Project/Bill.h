#ifndef BILL_H
#define BILL_H

#include <string>
#include <vector>
using namespace std;

struct Bill{
    string payer;
    double billss;
    double tax;
    double tip;
    double gratuity;
    vector<string> debtor;

    Bill(string& _payer, double _bill, double _tax, double _tip, double _gratuity, vector<string>& debtors){
        payer = _payer;
        billss = _bill;
        tax = _tax;
        tip = _tip;
        gratuity = _gratuity;
        debtor = debtors;
    }
};


#endif // BILL_H
