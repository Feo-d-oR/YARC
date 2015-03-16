#include "dbwork.h"

DBWork::DBWork(QObject *parent) :
    QObject(parent)
{
}

QSqlError DBWork::createTables()
{
    q.exec("CREATE TABLE orders (number INTEGER AUTO_INCREMENT PRIMARY KEY, date_in TIMESTAMP, state VARCHAR(16), date_out TIMESTAMP, customer INTEGER, phone INTEGER, product_type INTEGER, product VARCHAR(32), serial VARCHAR(16), disease VARCHAR(255), cond VARCHAR(255), complect VARCHAR(255), cost DECIMAL(10, 2), acceptor INTEGER, master INTEGER, giver INTEGER, warranty VARCHAR(16), comment VARCHAR(255), called BOOLEAN NOT NULL DEFAULT 0)");
    q.exec("CREATE TABLE product_types (id INTEGER AUTO_INCREMENT PRIMARY KEY, name VARCHAR(32))");
    q.exec("CREATE TABLE employees (id INTEGER AUTO_INCREMENT PRIMARY KEY, name VARCHAR(64), fullname VARCHAR(255), phone VARCHAR(64), address VARCHAR(255), position_type INTEGER, position VARCHAR(128), isactive BOOLEAN NOT NULL DEFAULT 1)");
    q.exec("CREATE TABLE customers (id INTEGER AUTO_INCREMENT PRIMARY KEY, name VARCHAR(64), phone VARCHAR(64), address VARCHAR(128))");
    q.exec("CREATE TABLE work_reports (id INTEGER AUTO_INCREMENT PRIMARY KEY, date TIMESTAMP, orderid INTEGER, master INTEGER, work INTEGER, quant INTEGER, spares VARCHAR(64), quants VARCHAR(64))");
    q.exec("CREATE TABLE diag_reports (id INTEGER AUTO_INCREMENT PRIMARY KEY, date TIMESTAMP, orderid INTEGER, master INTEGER, inspect VARCHAR(1024), defects VARCHAR(1024), recomm VARCHAR(1024))");
    q.exec("CREATE TABLE works (id INTEGER AUTO_INCREMENT PRIMARY KEY, name VARCHAR(255), price DECIMAL(10, 2), comment VARCHAR(128))");
    q.exec("CREATE TABLE spares (id INTEGER AUTO_INCREMENT PRIMARY KEY, type INTEGER, name VARCHAR(255), price DECIMAL(10, 2))");
    q.exec("CREATE TABLE spare_types (id INTEGER AUTO_INCREMENT PRIMARY KEY, name VARCHAR(64))");
    q.exec("CREATE TABLE salaries (id INTEGER AUTO_INCREMENT PRIMARY KEY, employee INTEGER, summ FLOAT)");

    q.exec("CREATE TABLE system (name VARCHAR(32) PRIMARY KEY, value_n INTEGER, value_c VARCHAR(255))");
    q.exec("INSERT INTO system VALUES('dbversion', 2, NULL)");
    q.exec("INSERT INTO system VALUES('percMaster', 0.5, NULL)");
    q.exec("INSERT INTO system VALUES('percAcceptor', 0.1, NULL)");
    q.exec("INSERT INTO system VALUES('percFirm', 0.4, NULL)");

    q.exec("CREATE TABLE states (id INTEGER PRIMARY KEY, name VARCHAR(32))");
    q.exec(QString("INSERT INTO states VALUES(1,'") + tr("Taken for repair") + "')");
    q.exec(QString("INSERT INTO states VALUES(2,'") + tr("Taken for diagnosis") + "')");
    q.exec(QString("INSERT INTO states VALUES(3,'") + tr("Customer refused to repair") + "')");
    q.exec(QString("INSERT INTO states VALUES(4,'") + tr("Refused to repair") + "')");
    q.exec(QString("INSERT INTO states VALUES(5,'") + tr("Diagnosis completed") + "')");
    q.exec(QString("INSERT INTO states VALUES(6,'") + tr("Repair completed") + "')");
    q.exec(QString("INSERT INTO states VALUES(7,'") + tr("Waits for agreement") + "')");
    q.exec(QString("INSERT INTO states VALUES(8,'") + tr("Agreed") + "')");
    q.exec(QString("INSERT INTO states VALUES(9,'") + tr("Given with diagnosis") + "')");
    q.exec(QString("INSERT INTO states VALUES(10,'") + tr("Given with repair") + "')");
    q.exec(QString("INSERT INTO states VALUES(11,'") + tr("Given without repair") + "')");
    q.exec(QString("INSERT INTO states VALUES(12,'") + tr("In diagnosing") + "')");
    q.exec(QString("INSERT INTO states VALUES(13,'") + tr("In the work") + "')");
    q.exec(QString("INSERT INTO states VALUES(14,'") + tr("Waits for spares") + "')");
    q.exec(QString("INSERT INTO states VALUES(15,'") + tr("Spares ordered") + "')");
    q.exec(QString("INSERT INTO states VALUES(16,'") + tr("Customer-Waits for spares") + "')");
    q.exec(QString("INSERT INTO states VALUES(17,'") + tr("Customer-Spares ordered") + "')");
    q.exec(QString("INSERT INTO states VALUES(18,'") + tr("Waits for giving out") + "')");
    q.exec(QString("INSERT INTO states VALUES(19,'") + tr("Taken for repair (warranty)") + "')");
    q.exec(QString("INSERT INTO states VALUES(20,'") + tr("Customer-Spares recieved") + "')");
    q.exec(QString("INSERT INTO states VALUES(21,'") + tr("Spares recieved") + "')");

    q.exec("CREATE TABLE position_types (id INTEGER PRIMARY KEY, name VARCHAR(64))");
    q.exec(QString("INSERT INTO position_types VALUES(1,'") + tr("Master") + "')");
    q.exec(QString("INSERT INTO position_types VALUES(2,'") + tr("Acceptor") + "')");
//    q.exec(QString("INSERT INTO position_types VALUES(3,'") + tr("Seller") + "')");
//    q.exec(QString("INSERT INTO position_types VALUES(4,'") + tr("Storekeeper") + "')");
//    q.exec(QString("INSERT INTO position_types VALUES(5,'") + tr("Notice Buyer") + "')");
//    q.exec(QString("INSERT INTO position_types VALUES(6,'") + tr("Bookkeeper") + "')");
//    q.exec(QString("INSERT INTO position_types VALUES(7,'") + tr("Boss") + "')");
    return q.lastError();
}

QSqlError DBWork::updateTo2() /*repaircenter greater than v0.3*/
{
    q.exec("CREATE TABLE system (name VARCHAR(32) PRIMARY KEY, value_n FLOAT, value_c VARCHAR(255))");
    q.exec("INSERT INTO system VALUES('dbversion', 2, NULL)");
    q.exec("INSERT INTO system VALUES('percMaster', 0.5, NULL)");
    q.exec("INSERT INTO system VALUES('percAcceptor', 0.1, NULL)");
    q.exec("INSERT INTO system VALUES('percFirm', 0.4, NULL)");
    q.exec("ALTER TABLE employees DROP hired, DROP dismissed");
    q.exec("ALTER TABLE employees ADD COLUMN isactive BOOLEAN NOT NULL DEFAULT 1");
    q.exec("ALTER TABLE orders ADD COLUMN called BOOLEAN NOT NULL DEFAULT 0");
    q.exec(QString("INSERT INTO states VALUES(20,'") + tr("Customer-Spares recieved") + "')");
    q.exec(QString("INSERT INTO states VALUES(21,'") + tr("Spares recieved") + "')");
    q.exec("CREATE TABLE salaries (id INTEGER AUTO_INCREMENT PRIMARY KEY, employee INTEGER, summ FLOAT)");
    return q.lastError();
}
