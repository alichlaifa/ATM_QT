#include "customer.h"

Customer::Customer()
{

}

Customer::Customer(const QString &name, const QString &pin) : name(name),pin(pin)
{
    DBManager& dbManager = DBManager::getInstance();
    QString values = "NULL, '" + name + "', '" + pin + "'";
    if (dbManager.insertRecord("Customer", values)) {
        // Retrieve the last inserted ID
        QSqlQuery query("SELECT last_insert_rowid()");
        if (query.next())
            id = query.value(0).toInt();
    }
}

Customer::Customer(int id, const QString &name, const QString &pin)
    : id(id), name(name), pin(pin) {}

int Customer::getId() const
{
    return id;
}

QString Customer::getName() const
{
    return name;
}

void Customer::setName(const QString &name)
{
    this->name = name;
}

QString Customer::getPin() const
{
    return pin;
}

void Customer::setPin(const QString &pin)
{
    this->pin = pin;
}

bool Customer::verifyPin(const QString &pin) const
{
    return this->pin == pin;
}

bool Customer::customerExists(int id)
{
    DBManager& dbManager = DBManager::getInstance();
    auto records = dbManager.selectRecords("Customer", "*", "id = " + QString::number(id));

    return !records.empty();
}

Customer Customer::getCustomerById(int id) {
    DBManager& dbManager = DBManager::getInstance();
    auto records = dbManager.selectRecords("Customer", "*", "id = " + QString::number(id));
    if (!records.empty()) {
        auto row = records[0];
        return Customer(row[0].toInt(), row[1], row[2]);
    }
    throw std::runtime_error("Customer not found");
}

bool Customer::removeCustomerById(int id)
{
    DBManager& dbManager = DBManager::getInstance();
    QString condition = QString("id = %1").arg(id);
    if (dbManager.deleteRecord("Customer", condition))
        return true;

    return false;
}

