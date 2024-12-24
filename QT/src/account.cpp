#include "account.h"

Account::Account()
{

}

Account::Account(int customerId) : customerId(customerId), balance(0.0), id(-1)
{
    if (!Customer::customerExists(customerId)) {
        qDebug() << "Customer with ID" << customerId << "does not exist. Account not created.";
        return; // Do not create the account if the customer does not exist
    }

    DBManager& dbManager = DBManager::getInstance();
    auto existingAccounts = dbManager.selectRecords("Account", "id", "customerID = " + QString::number(customerId));
    if (!existingAccounts.empty()) {
        qDebug() << "Customer already has an account. Cannot create another one.";
        return; // Do not create the account if one already exists for this customer
    }

    QString values = QString("NULL, %1, %2").arg(customerId).arg(balance);
    if (dbManager.insertRecord("Account", values)) {
        // Retrieve the last inserted ID
        QSqlQuery query("SELECT last_insert_rowid()");
        if (query.next())
            id = query.value(0).toInt();
        else
            qDebug() << "Failed to insert account record: ";
    }
}

Account::Account(int id, int customerId, double balance)
    : id(id), customerId(customerId), balance(balance) {}

int Account::getId() const
{
    return id;
}

int Account::getCustomerId() const
{
    return customerId;
}

double Account::getBalance() const
{
    return balance;
}

bool Account::deposit(double amount)
{
    if (amount <= 0) {
        qDebug() << "Deposit amount must be positive.";
        return false;
    }

    DBManager& dbManager = DBManager::getInstance();
    balance += amount;
    QString updates = QString("balance = %1").arg(balance);
    QString condition = QString("id = %1").arg(id);

    return dbManager.updateRecord("Account", updates, condition);
}

bool Account::withdraw(double amount)
{
    if (amount <= 0) {
        qDebug() << "Withdrawal amount must be positive.";
        return false;
    }
    if (amount > balance) {
        qDebug() << "Insufficient balance.";
        return false;
    }

    DBManager& dbManager = DBManager::getInstance();
    balance -= amount;
    QString updates = QString("balance = %1").arg(balance);
    QString condition = QString("id = %1").arg(id);

    return dbManager.updateRecord("Account", updates, condition);
}

bool Account::accountExists(int id)
{
    DBManager& dbManager = DBManager::getInstance();
    auto records = dbManager.selectRecords("Account", "id", QString("id = %1").arg(id));
    return !records.empty();
}

Account Account::getAccountById(int id)
{
    DBManager& dbManager = DBManager::getInstance();
    auto records = dbManager.selectRecords("Account", "*", "id = " + QString::number(id));
    if (!records.empty()) {
        auto row = records[0];
        return Account(row[0].toInt(), row[1].toInt(), row[2].toDouble());
    }
    throw std::runtime_error("Account not found");
}

bool Account::removeAccountById(int id)
{
    DBManager& dbManager = DBManager::getInstance();
    QString condition = QString("id = %1").arg(id);
    return dbManager.deleteRecord("Account", condition);
}

Account Account::getAccountByCustomerId(int customerId)
{
    DBManager& dbManager = DBManager::getInstance();
    auto records = dbManager.selectRecords("Account", "*", "customerID = " + QString::number(customerId));

    if (!records.empty()) {
        int accountId = records[0][0].toInt();
        return Account::getAccountById(accountId);
    } else {
        throw std::runtime_error("No account found for this customer");
    }
}
