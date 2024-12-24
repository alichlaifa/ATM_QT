#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <vector>
#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

class DBManager
{
private:
    QSqlDatabase m_db;

    DBManager(const QString& path);
    ~DBManager();

    DBManager(const DBManager&) = delete;
    DBManager& operator=(const DBManager&) = delete;

public:
    static DBManager& getInstance(const QString& path = "database.db");

    bool isOpen() const;

    bool createTable();

    bool insertRecord(const QString &table, const QString &values);
    bool deleteRecord(const QString &table, const QString &condition);
    std::vector<std::vector<QString>> selectRecords(const QString &table,
                                                    const QString& columns,
                                                    const QString& condition);
    bool updateRecord(const QString &table, const QString &updates, const QString &condition);
};

#endif // DBMANAGER_H
