#ifndef ATM_H
#define ATM_H

#include "DBManager.h"
#include "card.h"
#include "transaction.h"
#include <QDateTime>

class ATM
{
private:
    Customer currentCustomer;
    Card currentCard;
    Account currentAccount;
public:
    ATM();

    bool authenticateCustomer(const QString &cardNumber, const QString &pin);
    double checkBalance() const;
    bool withdraw(double amount);
    std::vector<Transaction> getTransactionHistory() const;
};

#endif // ATM_H
