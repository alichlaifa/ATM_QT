#ifndef CARD_H
#define CARD_H

#include "DBManager.h"
#include "customer.h"

class Card
{
private:
    QString cardNumber;
    QString expirationDate;
    QString cvv;
    int customerId;
public:
    Card() = default;
    Card(const QString &cardNumber, const QString &expirationDate, const QString &cvv, int customerId);

    QString getCardNumber() const;
    QString getExpirationDate() const;
    QString getCvv() const;
    int getCustomerId() const;

    static Card getCardByNumber(const QString &cardNumber);
    static bool cardExists(const QString &cardNumber);
    static bool removeCustomerByCardNumber(const QString &cardNumber);
    void setCardNumber(const QString &CardNumber);
    void setExpirationDate(const QString &ExpirationDate);
    void setCvv(const QString &Cvv);
    void setCustomerId(int CustomerId);
};

#endif // CARD_H
