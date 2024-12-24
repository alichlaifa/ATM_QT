#include "transaction.h"

Transaction::Transaction(int accountId, double amount, TransactionType type, const QString &timestamp)
    : id(-1), accountId(accountId), amount(amount), type(type), timestamp(timestamp)
{
    if (!Account::accountExists(accountId)) {
        qDebug() << "Account with ID" << accountId << "does not exist. Account not created.";
        return; // Do not create the transaction if the account does not exist
    }

    DBManager& dbManager = DBManager::getInstance();
    QString values = QString("NULL, %1, %2, '%3', '%4'")
                         .arg(accountId)
                         .arg(amount)
                         .arg(transactionTypeToString(type))
                         .arg(timestamp);

    if (dbManager.insertRecord("\"Transaction\"", values)) {
        // Retrieve the last inserted ID
        QSqlQuery query("SELECT last_insert_rowid()");
        if (query.next()) {
            id = query.value(0).toInt();

            // Update account balance based on transaction type
            if (type == TransactionType::DEPOSIT)
                Account::getAccountById(accountId).deposit(amount);
            else if (type == TransactionType::WITHDRAWAL)
                Account::getAccountById(accountId).withdraw(amount);

        } else {
            qDebug() << "Failed to retrieve last inserted row ID.";
        }
    } else {
        qDebug() << "Failed to insert transaction record.";
    }
}

Transaction::Transaction(int id, int accountId, double amount, TransactionType type, const QString &timestamp)
    : id(id), accountId(accountId), amount(amount), type(type), timestamp(timestamp) {}

QString Transaction::transactionTypeToString(TransactionType type)
{
    switch (type) {
    case TransactionType::DEPOSIT:
        return "DEPOSIT";
    case TransactionType::WITHDRAWAL:
        return "WITHDRAWAL";
    default:
        return "UNKNOWN";
    }
}

TransactionType Transaction::stringToTransactionType(const QString &typeStr)
{
    if (typeStr == "DEPOSIT")
        return TransactionType::DEPOSIT;
    else if (typeStr == "WITHDRAWAL")
        return TransactionType::WITHDRAWAL;
    else
        throw std::runtime_error("Unknown transaction type");
}

int Transaction::getId() const
{
    return id;
}

int Transaction::getAccountId() const
{
    return accountId;
}

double Transaction::getAmount() const
{
    return amount;
}

TransactionType Transaction::getType() const
{
    return type;
}

QString Transaction::getTimestamp() const
{
    return timestamp;
}

bool Transaction::transactionExists(int id)
{
    DBManager& dbManager = DBManager::getInstance();
    auto records = dbManager.selectRecords("\"Transaction\"", "*", "id = " + QString::number(id));

    return !records.empty();
}

Transaction Transaction::getTransactionById(int id)
{
    DBManager& dbManager = DBManager::getInstance();
    auto records = dbManager.selectRecords("\"Transaction\"", "*", "id = " + QString::number(id));
    if (!records.empty()) {
        auto row = records[0];
        TransactionType type = stringToTransactionType(row[3]);
        return Transaction(row[0].toInt(), row[1].toInt(), row[2].toDouble(), type, row[4]);
    }
    throw std::runtime_error("Transaction not found");
}

std::vector<Transaction> Transaction::getTransactionHistory(int accountId)
{
    std::vector<Transaction> transactions;

    DBManager& dbManager = DBManager::getInstance();
    auto records = dbManager.selectRecords("\"Transaction\"", "*", "accountID = " + QString::number(accountId));

    for (const auto& row : records) {
        /*int id = row[0].toInt();
        double amount = row[2].toDouble();
        QString type = row[3];
        QString timestamp = row[4];*/
        int transactionId = row[0].toInt();
        transactions.push_back(Transaction::getTransactionById(transactionId));
    }

    return transactions;
}
