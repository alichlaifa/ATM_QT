#include "atm.h"

ATM::ATM()
{

}

bool ATM::authenticateCustomer(const QString &cardNumber, const QString &pin)
{
    if (Card::cardExists(cardNumber)) {
        currentCard = Card::getCardByNumber(cardNumber);
        currentCustomer = Customer::getCustomerById(currentCard.getCustomerId());

        if (currentCustomer.verifyPin(pin)) {
            try {
                currentAccount = Account::getAccountByCustomerId(currentCustomer.getId());
                qDebug() << "Authentication successful.";
                return true;
            } catch (const std::runtime_error &e) {
                qDebug() << "Authentication failed: " << e.what();
            }
        } else {
            qDebug() << "Authentication failed: Incorrect PIN.";
        }
    } else {
        qDebug() << "Authentication failed: Card does not exist.";
    }
    return false;
}

bool ATM::withdraw(double amount)
{
    DBManager& dbManager = DBManager::getInstance();
    // Check if the amount is positive
    if (amount <= 0) {
        qDebug() << "Invalid withdrawal amount.";
        return false;
    }

    // Fetch the current balance
    double currentBalance = checkBalance();
    if (currentBalance < amount) {
        qDebug() << "Insufficient funds.";
        return false;
    }

    // Update the balance in the Account table
    QString updates = QString("balance = balance - %1").arg(amount);
    QString condition = QString("id = %1").arg(currentAccount.getId());
    if (!dbManager.updateRecord("Account", updates, condition)) {
        qDebug() << "Failed to update account balance.";
        return false;
    }

    // Insert a transaction record
    QDateTime timestamp = QDateTime::currentDateTime();
    TransactionType type = TransactionType::WITHDRAWAL;
    QString typeString = Transaction::transactionTypeToString(type);
    QString transactionValues = QString("NULL, %1, %2, '%3', '%4'")
                                    .arg(currentAccount.getId())
                                    .arg(amount)
                                    .arg(typeString)
                                    .arg(timestamp.toString(Qt::ISODate));

    if (!dbManager.insertRecord("\"Transaction\"", transactionValues)) {
        qDebug() << "Failed to record transaction.";
        return false;
    }

    return true;
}

double ATM::checkBalance() const {
    if (currentAccount.getId() <= 0) {
        qDebug() << "No valid account is set.";
        return 0.0;
    }

    return currentAccount.getBalance();
}

std::vector<Transaction> ATM::getTransactionHistory() const
{
    if (currentAccount.getId() <= 0) {
        qDebug() << "No valid account is set.";
        return {};
    }

    return Transaction::getTransactionHistory(currentAccount.getId());
}

