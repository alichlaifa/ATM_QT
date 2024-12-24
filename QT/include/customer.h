#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QString>
#include "DBManager.h"
#include "account.h"

class Account;

class Customer
{
private:
    int id;
    QString name;
    QString pin;
    Customer(int id, const QString &name, const QString &pin);

public:
    Customer();
    Customer(const QString &name, const QString &pin);

    int getId() const;
    QString getName() const;
    void setName(const QString &name);
    QString getPin() const;
    void setPin(const QString &pin);

    bool verifyPin(const QString& pin) const;
    static bool customerExists(int id);
    static Customer getCustomerById(int id);
    static bool removeCustomerById(int id);
};

#endif // CUSTOMER_H
