// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "app_environment.h"
#include "import_qml_components_plugins.h"
#include "import_qml_plugins.h"

#include <iostream>
#include "DBManager.h"
#include "customer.h"
#include "account.h"
#include "transaction.h"
#include "card.h"
#include "atm.h"


int main(int argc, char *argv[])
{
    set_qt_environment();

    /* ///////////////////////// dbManager Test /////////////////////////////////////

    // Initialize the database manager
    DBManager& dbManager = DBManager::getInstance("database.db");

    // Create tables if they don't exist
    if (dbManager.isOpen()) {
        if (!dbManager.createTable()) {
            std::cerr << "Failed to create tables" << std::endl;
        }
    } else {
        std::cerr << "Failed to open database" << std::endl;
    }


    // Insert a customer record
    if (!dbManager.insertRecord("Customer", "NULL, 'John Doe', '1234'")) {
        std::cerr << "Failed to insert customer record" << std::endl;
    }

    // Insert an account record
    if (!dbManager.insertRecord("Account", "NULL, 1, 1000.0")) {
        std::cerr << "Failed to insert account record" << std::endl;
    }

    // Insert a transaction record
    if (!dbManager.insertRecord("`Transaction`", "NULL, 1, 100.0, 'deposit', CURRENT_TIMESTAMP")) {
        std::cerr << "Failed to insert transaction record" << std::endl;
    }

    // Insert a card record
    if (!dbManager.insertRecord("Card", "'1234577890123456', '12/25', '123', 1")) {
        std::cerr << "Failed to insert card record" << std::endl;
    }


    // Select records
    auto records = dbManager.selectRecords("Card", "*", "1=1");
    for (const auto& row : records) {
        for (const auto& col : row) {
            std::cout << col.toStdString() << " ";
        }
        std::cout << std::endl;
    }

    dbManager.deleteRecord("Customer", "pin=4888");

    */ //////////////////////////////////////////////////////////////////////////////////////////

    /////////////////////////// Customer Test /////////////////////////////////////
    /*Customer newCustomer("Ali ch", "0000");
    qDebug() << "New customer created with ID:" << newCustomer.getId();*/

    /*Customer retrievedCustomer = Customer::getCustomerById(3);
    qDebug() << "Retrieved customer ID:" << retrievedCustomer.getId();
    qDebug() << "Name:" << retrievedCustomer.getName();
    qDebug() << "PIN:" << retrievedCustomer.verifyPin("1234");*/

    /*if (Customer::removeCustomerById(7))
        qDebug() << "Customer removed successfully";
    else
        qDebug() << "Failed to remove customer";*/

    /*Customer customer = Customer::getCustomerById(3);

    auto account = customer.getCustomerAccount();

    qDebug() << "Account ID:" << account.getId()
             << "Customer ID:" << account.getCustomerId()
             << "Balance:" << account.getBalance();*/

    //////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////// Account Test /////////////////////////////////////
    //Account account1(2);
    /*Account account2(3);
    if (account2.deposit(100.0))
        qDebug() << "Balance after deposit:" << account2.getBalance();
    else
        qDebug() << "Deposit failed.";

    if (account2.withdraw(50.0))
        qDebug() << "Balance after withdrawal:" << account2.getBalance();
    else
        qDebug() << "Withdrawal failed.";*/
    //Account::removeAccountById(4);
    //qDebug() << Account::accountExists(3);

    /*try {
        Account retrievedAccount = Account::getAccountById(1);
        qDebug() << "Retrieved Account ID:" << retrievedAccount.getId();
        qDebug() << "Retrieved Account Customer ID:" << retrievedAccount.getCustomerId();
        qDebug() << "Retrieved Account Balance:" << retrievedAccount.getBalance();
    } catch (const std::runtime_error& e) {
        qDebug() << e.what();
    }*/
    //////////////////////////////////////////////////////////////////////////////////////////

    /////////////////////////// Transaction Test /////////////////////////////////////
    /*QDateTime current = QDateTime::currentDateTime();
    Transaction depositTransaction(1, 100.0, TransactionType::WITHDRAWAL, current.toString(Qt::ISODate));*/

    /*if (depositTransaction.getId() != -1) {
        qDebug() << "Deposit Transaction created with ID:" << depositTransaction.getId();
    } else {
        qDebug() << "Failed to create deposit transaction.";
    }*/

    /*Transaction retrievedTransaction = Transaction::getTransactionById(2);
    qDebug() << "Retrieved Transaction ID:" << retrievedTransaction.getId()
             << " Account ID:" << retrievedTransaction.getAccountId()
             << " Amount:" << retrievedTransaction.getAmount()
             << " Type:" << Transaction::transactionTypeToString(retrievedTransaction.getType())
             << " Timestamp:" << retrievedTransaction.getTimestamp();*/

    /*bool exists = Transaction::transactionExists(3);
    qDebug() << "Transaction exists:" << exists;*/

    /*bool removed = Transaction::removeTransactionById(9);
    qDebug() << "Transaction removed:" << removed;*/

    /*auto transactions = Transaction::getTransactionHistory(1);
    for (const auto& transaction : transactions) {
        qDebug() << "Transaction:" << transaction.getId() << transaction.getAmount()
                 << Transaction::transactionTypeToString(transaction.getType()) << transaction.getTimestamp();
    }*/

    ///////////////////////////////////////////////////////////////////////////////


    ///////////////////////// Card Test ////////////////////////////////////////

    /*Card newCard("3534567890123456", "12/24", "123", 3);
    Card::removeCustomerByCardNumber("1234567890123456");
    qDebug() << Card::getCardByNumber("3534567890123456").getCustomerId();
    qDebug() << Card::getCardByNumber("3534567890123456").getExpirationDate();
    qDebug() << Card::getCardByNumber("3534567890123456").getCvv();*/

    /////////////////////////////////////////////////////////////////////////////

    ///////////////////////// ATM Test ////////////////////////////////////////

    /*ATM atm;

    QString cardNumber = "1234577890123456"; // Example card number
    QString pin = "1234"; // Example PIN

    // Authenticate the customer
    if (atm.authenticateCustomer(cardNumber, pin)) {
        qDebug() << "Customer authenticated successfully.";

        // Check balance
        double balance = atm.checkBalance();
        qDebug() << "Current balance:" << balance;

        // Withdraw money
        double amountToWithdraw = 50.0;
        if (atm.withdraw(amountToWithdraw)) {
            qDebug() << "Withdrawal successful. New balance:" << atm.checkBalance();
        } else {
            qDebug() << "Withdrawal failed.";
        }

        // Get transaction history
        std::vector<Transaction> transactions = atm.getTransactionHistory();
        for (const auto& transaction : transactions) {
            qDebug() << "Transaction ID:" << transaction.getId()
                     << ", Amount:" << transaction.getAmount()
                     << ", Type:" << transaction.transactionTypeToString(transaction.getType())
                     << ", Timestamp:" << transaction.getTimestamp();
        }

    } else {
        qDebug() << "Authentication failed.";
    }*/

    /////////////////////////////////////////////////////////////////////////////

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:Main/main.qml"_qs);
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
    engine.addImportPath(":/");

    /*engine.load(url);

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }*/

    std::cout<<"Hello" << std::endl;
    return app.exec();
}
