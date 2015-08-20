#include "dbwork.h"
#include "mainwindow.h"

DBWork::DBWork(QObject *parent) :
    QObject(parent)
{
}

QSqlError DBWork::createTables()
{
    q.exec("CREATE TABLE orders (number INTEGER AUTO_INCREMENT PRIMARY KEY, date_in TIMESTAMP, state VARCHAR(16), date_out TIMESTAMP, customer INTEGER, phone INTEGER, product_type INTEGER, product VARCHAR(32), serial VARCHAR(16), disease VARCHAR(255), cond VARCHAR(255), complect VARCHAR(255), cost DOUBLE, acceptor INTEGER, master INTEGER, giver INTEGER, warranty VARCHAR(16), comment VARCHAR(255), called BOOLEAN NOT NULL DEFAULT 0)");
    q.exec("CREATE TABLE product_types (id INTEGER AUTO_INCREMENT PRIMARY KEY, name VARCHAR(32))");
    q.exec("CREATE TABLE employees (id INTEGER AUTO_INCREMENT PRIMARY KEY, name VARCHAR(64), fullname VARCHAR(255), phone VARCHAR(64), address VARCHAR(255), position_type INTEGER, position VARCHAR(128), isactive BOOLEAN NOT NULL DEFAULT 1)");
    q.exec("CREATE TABLE customers (id INTEGER AUTO_INCREMENT PRIMARY KEY, name VARCHAR(64), phone VARCHAR(64), address VARCHAR(128))");
    q.exec("CREATE TABLE work_reports (id INTEGER AUTO_INCREMENT PRIMARY KEY, date TIMESTAMP, orderid INTEGER, master INTEGER, work INTEGER, quant INTEGER, spares VARCHAR(64), quants VARCHAR(64))");
    q.exec("CREATE TABLE diag_reports (id INTEGER AUTO_INCREMENT PRIMARY KEY, date TIMESTAMP, orderid INTEGER, master INTEGER, inspect VARCHAR(1024), defects VARCHAR(1024), recomm VARCHAR(1024))");
    q.exec("CREATE TABLE works (id INTEGER AUTO_INCREMENT PRIMARY KEY, name VARCHAR(255), price DOUBLE, comment VARCHAR(128))");
    q.exec("CREATE TABLE spares (id INTEGER AUTO_INCREMENT PRIMARY KEY, type INTEGER, name VARCHAR(255), price DOUBLE)");
    q.exec("CREATE TABLE spare_types (id INTEGER AUTO_INCREMENT PRIMARY KEY, name VARCHAR(64))");
    q.exec("CREATE TABLE salaries (id INTEGER AUTO_INCREMENT PRIMARY KEY, employee INTEGER, summ DOUBLE)");

    q.exec("CREATE TABLE system (name VARCHAR(32) PRIMARY KEY, value_n DOUBLE, value_c VARCHAR(255))");
    q.exec("INSERT INTO system VALUES('dbversion', 2, NULL)");
    q.exec("INSERT INTO system VALUES('percMaster', 0.6, NULL)");
    q.exec("INSERT INTO system VALUES('percAcceptor', 0.1, NULL)");
    q.exec("INSERT INTO system VALUES('percFirm', 0.3, NULL)");
    q.exec("INSERT INTO system VALUES('dblocale', NULL, '" + MainWindow::lang +"')");

    q.exec("CREATE TABLE states (id INTEGER PRIMARY KEY, name VARCHAR(32))");
    q.exec(QString("INSERT INTO states VALUES(1,'") + tr("Accepted for repair") + "')");
    q.exec(QString("INSERT INTO states VALUES(2,'") + tr("Accepted for diagnostics") + "')");
    q.exec(QString("INSERT INTO states VALUES(3,'") + tr("Customer refused to repair") + "')");
    q.exec(QString("INSERT INTO states VALUES(4,'") + tr("Refused to repair") + "')");
    q.exec(QString("INSERT INTO states VALUES(5,'") + tr("Diagnostics completed") + "')");
    q.exec(QString("INSERT INTO states VALUES(6,'") + tr("Repair completed") + "')");
    q.exec(QString("INSERT INTO states VALUES(7,'") + tr("Awaits coordination") + "')");
    q.exec(QString("INSERT INTO states VALUES(8,'") + tr("Customer agreed") + "')");
    q.exec(QString("INSERT INTO states VALUES(9,'") + tr("Issued with diagnostics") + "')");
    q.exec(QString("INSERT INTO states VALUES(10,'") + tr("Issued with repair") + "')");
    q.exec(QString("INSERT INTO states VALUES(11,'") + tr("Isuued without repair") + "')");
    q.exec(QString("INSERT INTO states VALUES(12,'") + tr("In diagnostics") + "')");
    q.exec(QString("INSERT INTO states VALUES(13,'") + tr("In work") + "')");
    q.exec(QString("INSERT INTO states VALUES(14,'") + tr("Awaits spares") + "')");
    q.exec(QString("INSERT INTO states VALUES(15,'") + tr("Spares ordered") + "')");
    q.exec(QString("INSERT INTO states VALUES(16,'") + tr("Customer-Awaits spares") + "')");
    q.exec(QString("INSERT INTO states VALUES(17,'") + tr("Customer-Spares ordered") + "')");
    q.exec(QString("INSERT INTO states VALUES(18,'") + tr("Awaits issuing") + "')");
    q.exec(QString("INSERT INTO states VALUES(19,'") + tr("Accepted for repair (warranty)") + "')");
    q.exec(QString("INSERT INTO states VALUES(20,'") + tr("Customer-Spares recieved") + "')");
    q.exec(QString("INSERT INTO states VALUES(21,'") + tr("Spares recieved") + "')");

    q.exec("CREATE TABLE position_types (id INTEGER PRIMARY KEY, name VARCHAR(64))");
    q.exec(QString("INSERT INTO position_types VALUES(1,'") + tr("Master") + "')");
    q.exec(QString("INSERT INTO position_types VALUES(2,'") + tr("Acceptor") + "')");
    q.exec(QString("INSERT INTO position_types VALUES(3,'") + tr("Storekeeper") + "')");
    return q.lastError();
}

QSqlError DBWork::retranslate() //requires latest dbversion
{
    q.exec("DROP TABLE states");
    q.exec("CREATE TABLE states (id INTEGER PRIMARY KEY, name VARCHAR(32))");
    q.exec(QString("INSERT INTO states VALUES(1,'") + tr("Accepted for repair") + "')");
    q.exec(QString("INSERT INTO states VALUES(2,'") + tr("Accepted for diagnostics") + "')");
    q.exec(QString("INSERT INTO states VALUES(3,'") + tr("Customer refused to repair") + "')");
    q.exec(QString("INSERT INTO states VALUES(4,'") + tr("Refused to repair") + "')");
    q.exec(QString("INSERT INTO states VALUES(5,'") + tr("Diagnostics completed") + "')");
    q.exec(QString("INSERT INTO states VALUES(6,'") + tr("Repair completed") + "')");
    q.exec(QString("INSERT INTO states VALUES(7,'") + tr("Awaits coordination") + "')");
    q.exec(QString("INSERT INTO states VALUES(8,'") + tr("Customer agreed") + "')");
    q.exec(QString("INSERT INTO states VALUES(9,'") + tr("Issued with diagnostics") + "')");
    q.exec(QString("INSERT INTO states VALUES(10,'") + tr("Issued with repair") + "')");
    q.exec(QString("INSERT INTO states VALUES(11,'") + tr("Isuued without repair") + "')");
    q.exec(QString("INSERT INTO states VALUES(12,'") + tr("In diagnostics") + "')");
    q.exec(QString("INSERT INTO states VALUES(13,'") + tr("In work") + "')");
    q.exec(QString("INSERT INTO states VALUES(14,'") + tr("Awaits spares") + "')");
    q.exec(QString("INSERT INTO states VALUES(15,'") + tr("Spares ordered") + "')");
    q.exec(QString("INSERT INTO states VALUES(16,'") + tr("Customer-Awaits spares") + "')");
    q.exec(QString("INSERT INTO states VALUES(17,'") + tr("Customer-Spares ordered") + "')");
    q.exec(QString("INSERT INTO states VALUES(18,'") + tr("Awaits issuing") + "')");
    q.exec(QString("INSERT INTO states VALUES(19,'") + tr("Accepted for repair (warranty)") + "')");
    q.exec(QString("INSERT INTO states VALUES(20,'") + tr("Customer-Spares recieved") + "')");
    q.exec(QString("INSERT INTO states VALUES(21,'") + tr("Spares recieved") + "')");

    q.exec("DROP TABLE position_types");
    q.exec("CREATE TABLE position_types (id INTEGER PRIMARY KEY, name VARCHAR(64))");
    q.exec(QString("INSERT INTO position_types VALUES(1,'") + tr("Master") + "')");
    q.exec(QString("INSERT INTO position_types VALUES(2,'") + tr("Acceptor") + "')");
    q.exec(QString("INSERT INTO position_types VALUES(3,'") + tr("Storekeeper") + "')");

    q.exec(QString("UPDATE system SET value_c = '")+ MainWindow::lang +("' WHERE name = 'dblocale'"));

    return q.lastError();
}

QSqlError DBWork::updateTo2() /*from repaircenter v0.3*/
{
    q.exec("CREATE TABLE system (name VARCHAR(32) PRIMARY KEY, value_n DOUBLE, value_c VARCHAR(255))");
    q.exec("INSERT INTO system VALUES('dbversion', 2, NULL)");
    q.exec("INSERT INTO system VALUES('percMaster', 0.5, NULL)");
    q.exec("INSERT INTO system VALUES('percAcceptor', 0.1, NULL)");
    q.exec("INSERT INTO system VALUES('percFirm', 0.4, NULL)");
    q.exec("ALTER TABLE employees DROP hired, DROP dismissed");
    q.exec("ALTER TABLE employees ADD COLUMN isactive BOOLEAN NOT NULL DEFAULT 1");
    q.exec("ALTER TABLE orders ADD COLUMN called BOOLEAN NOT NULL DEFAULT 0");
    q.exec(QString("INSERT INTO states VALUES(20,'") + tr("Customer-Spares recieved") + "')");
    q.exec(QString("INSERT INTO states VALUES(21,'") + tr("Spares recieved") + "')");
    q.exec("CREATE TABLE salaries (id INTEGER AUTO_INCREMENT PRIMARY KEY, employee INTEGER, summ DOUBLE)");
    return q.lastError();
}

QSqlError DBWork::updateTo3() /*from repaircenter v0.3.1b*/
{
    q.exec(QString("INSERT INTO position_types VALUES(3,'") + tr("Storekeeper") + "')");

    q.exec(QString("INSERT INTO system VALUES('dblocale', NULL, '") + MainWindow::lang +"')");
    q.exec(QString("UPDATE system SET value_n = 3 WHERE name = 'dbversion'"));
    q.exec(QString("ALTER TABLE `system` CHANGE `value_n` `value_n` DOUBLE NULL DEFAULT NULL ;"));

    return q.lastError();
}

QSqlError DBWork::updateTo4() /*from repaircenter v0.3.2b*/
{
    q.exec(QString("ALTER TABLE system CHANGE value_n value_n DOUBLE NULL DEFAULT NULL"));
    q.exec(QString("ALTER TABLE orders CHANGE cost cost DOUBLE NULL DEFAULT NULL"));
    q.exec(QString("ALTER TABLE spares CHANGE price price DOUBLE NULL DEFAULT NULL"));
    q.exec(QString("ALTER TABLE works CHANGE price price DOUBLE NULL DEFAULT NULL"));
    q.exec(QString(""));
    q.exec(QString("UPDATE system SET value_n = 4 WHERE name = 'dbversion'"));
    return q.lastError();
}
