#include "card.h"

Card::Card(const QString &cardNumber, const QString &expirationDate, const QString &cvv, int customerId)
    : cardNumber(cardNumber), expirationDate(expirationDate), cvv(cvv), customerId(customerId)
{
    if (!Customer::customerExists(customerId)) {
        qDebug() << "Customer with ID" << customerId << "does not exist. Customer not created.";
        return; // Do not create the card if the account does not exist
    }

    DBManager& dbManager = DBManager::getInstance();
    QString values = QString("'%1', '%2', '%3', %4")
                         .arg(cardNumber)
                         .arg(expirationDate)
                         .arg(cvv)
                         .arg(customerId);
    if (!dbManager.insertRecord("Card", values)) {
        qDebug() << "Failed to insert card record.";
    }
}
void Card::setCardNumber(const QString &CardNumber)
{
    cardNumber = CardNumber;
}

void Card::setExpirationDate(const QString &ExpirationDate)
{
    expirationDate = ExpirationDate;
}

void Card::setCvv(const QString &Cvv)
{
    cvv = Cvv;
}

void Card::setCustomerId(int CustomerId)
{
    customerId = CustomerId;
}

QString Card::getCardNumber() const
{
    return cardNumber;
}

QString Card::getExpirationDate() const
{
    return expirationDate;
}

QString Card::getCvv() const
{
    return cvv;
}

int Card::getCustomerId() const
{
    return customerId;
}

Card Card::getCardByNumber(const QString &cardNumber)
{
    DBManager& dbManager = DBManager::getInstance();
    auto records = dbManager.selectRecords("Card", "*", "cardNumber = '" + cardNumber + "'");
    if (!records.empty()) {
        auto row = records[0];
        Card card;
        card.setCardNumber(row[0]);
        card.setExpirationDate(row[1]);
        card.setCvv(row[2]);
        card.setCustomerId(row[3].toInt());
        return card;
    }
    throw std::runtime_error("Card not found");
}

bool Card::cardExists(const QString &cardNumber)
{
    DBManager& dbManager = DBManager::getInstance();
    auto records = dbManager.selectRecords("Card", "cardNumber", QString("cardNumber = %1").arg(cardNumber));
    return !records.empty();
}

bool Card::removeCustomerByCardNumber(const QString &cardNumber)
{
    DBManager& dbManager = DBManager::getInstance();
    QString condition = QString("cardNumber = %1").arg(cardNumber);
    if (dbManager.deleteRecord("Card", condition))
        return true;

    return false;
}

