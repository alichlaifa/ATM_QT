#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "DBManager.h"
#include "customer.h"

class Account
{
private:
    int id;
    int customerId;
    double balance = 0.0;
    Account(int id, int customerId, double balance);

public:
    Account();
    Account(int customerId);
    int getId() const;
    int getCustomerId() const;
    double getBalance() const;
    bool deposit(double amount);
    bool withdraw(double amount);

    static bool accountExists(int id);
    static Account getAccountById(int id);
    static bool removeAccountById(int id);
    static Account getAccountByCustomerId(int customerId);
};

#endif // ACCOUNT_H
