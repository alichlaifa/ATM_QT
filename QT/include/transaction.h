#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "DBManager.h"
#include "account.h"

enum class TransactionType {
    DEPOSIT,
    WITHDRAWAL
};

class Transaction
{
private:
    Transaction(int id, int accountId, double amount, TransactionType type, const QString &timestamp);
    int id;
    int accountId;
    double amount;
    TransactionType type;
    QString timestamp;

public:
    Transaction(int accountId, double amount, TransactionType type, const QString &timestamp);
    static QString transactionTypeToString(TransactionType type);
    static TransactionType stringToTransactionType(const QString& typeStr);

    int getId() const;
    int getAccountId() const;
    double getAmount() const;
    TransactionType getType() const;
    QString getTimestamp() const;

    static Transaction getTransactionById(int id);
    static bool transactionExists(int id);
    static std::vector<Transaction> getTransactionHistory(int accountId);
};

#endif // TRANSACTION_H
