#include "DBManager.h"

DBManager::DBManager(const QString &path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open()) {
        qDebug() << "Error: connection with database failed";
    } else {
        qDebug() << "Database: connection ok";
    }
}

DBManager &DBManager::getInstance(const QString &path)
{
    static DBManager instance(path);
    return instance;
}

DBManager::~DBManager()
{
    if (m_db.isOpen()) {
        m_db.close();
    }
}

bool DBManager::isOpen() const
{
    return m_db.isOpen();
}

bool DBManager::createTable()
{
    bool success = false;

    QSqlQuery query;
    //query.prepare("CREATE TABLE IF NOT EXISTS ATM (id INTEGER PRIMARY KEY AUTOINCREMENT, customer TEXT, age INTEGER);");

    QString createCustomerTable = "CREATE TABLE IF NOT EXISTS Customer ("
                                  "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                  "name TEXT NOT NULL, "
                                  "pin TEXT NOT NULL);";

    QString createAccountTable = "CREATE TABLE IF NOT EXISTS Account ("
                                 "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                 "customerID INTEGER NOT NULL, "
                                 "balance REAL NOT NULL, "
                                 "FOREIGN KEY (customerID) REFERENCES Customer(id));";

    QString createTransactionTable = "CREATE TABLE IF NOT EXISTS `Transaction` ("
                                     "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                     "accountID INTEGER NOT NULL, "
                                     "amount REAL NOT NULL, "
                                     "type TEXT NOT NULL, "
                                     "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP, "
                                     "FOREIGN KEY (accountID) REFERENCES Account(id));";

    QString createCardTable = "CREATE TABLE IF NOT EXISTS Card ("
                              "cardNumber TEXT PRIMARY KEY, "
                              "expirationDate TEXT NOT NULL, "
                              "cvv TEXT NOT NULL, "
                              "customerID INTEGER NOT NULL, "
                              "FOREIGN KEY (customerID) REFERENCES Customer(id));";

    if (!query.exec(createCustomerTable) ||
        !query.exec(createAccountTable) ||
        !query.exec(createTransactionTable) ||
        !query.exec(createCardTable))
    {
        qDebug() << "Error creating tables: " << query.lastError();
        success = false;
    } else
        success = true;

    return success;
}

bool DBManager::insertRecord(const QString &table, const QString &values)
{
    bool success = false;

    QSqlQuery queryAdd;
    QString queryStr = "INSERT INTO " + table + " VALUES (" + values + ")";
    queryAdd.prepare(queryStr);

    if(queryAdd.exec())
        success = true;
    else
        qDebug() << "add record failed: " << queryAdd.lastError();

    return success;
}

bool DBManager::deleteRecord(const QString &table, const QString &condition)
{
    bool success = false;


    QSqlQuery queryDelete;
    queryDelete.prepare("DELETE FROM " + table + " WHERE " + condition);
    success = queryDelete.exec();

    if(!success)
    {
        qDebug() << "remove failed: " << queryDelete.lastError();
    }

    return success;
}

std::vector<std::vector<QString> > DBManager::selectRecords(const QString &table,
                                                           const QString &columns,
                                                           const QString &condition)
{
    std::vector<std::vector<QString>> results;
    QSqlQuery query;
    QString queryString = QString("SELECT " + columns + " FROM " + table + " WHERE " + condition);
    query.prepare(queryString);

    if (query.exec()) {
        int columnsCount = query.record().count();
        while (query.next()) {
            std::vector<QString> row;
            for (int i = 0; i < columnsCount; ++i) {
                row.push_back(query.value(i).toString());
            }
            results.push_back(row);
        }
    } else {
        qDebug() << "Select records error: " << query.lastError();
    }

    return results;
}

bool DBManager::updateRecord(const QString &table, const QString &updates, const QString &condition)
{
    QSqlQuery query;
    query.prepare(QString("UPDATE %1 SET %2 WHERE %3").arg(table).arg(updates).arg(condition));
    if (!query.exec()) {
        qDebug() << "Failed to execute query: " << query.lastError();
        return false;
    }
    return true;
}
