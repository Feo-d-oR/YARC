#include "dbwork.h"
#include "mainwindow.h"

DBWork::DBWork(QObject *parent) :
    QObject(parent)
{
}

QSqlError DBWork::createTables()
{
    q.exec("CREATE TABLE orders (number INTEGER AUTO_INCREMENT PRIMARY KEY, \
           date_in TIMESTAMP, state VARCHAR(16), date_out TIMESTAMP, customer INTEGER, phone INTEGER, \
           product_type INTEGER, product VARCHAR(32), serial VARCHAR(16), disease VARCHAR(255), \
           cond VARCHAR(255), complect VARCHAR(255), cost DOUBLE, acceptor INTEGER, master INTEGER, giver INTEGER, \
           warranty VARCHAR(16), comment VARCHAR(255), called BOOLEAN NOT NULL DEFAULT FALSE, date_called TIMESTAMP)");
    q.exec("CREATE TABLE product_types (id INTEGER AUTO_INCREMENT PRIMARY KEY, name VARCHAR(32))");
    q.exec("CREATE TABLE employees (id INTEGER AUTO_INCREMENT PRIMARY KEY, \
           name VARCHAR(64)NULL, fullname VARCHAR(255), phone VARCHAR(64), address VARCHAR(255), \
           position_type INTEGER, position VARCHAR(128), isactive BOOLEAN NOT NULL DEFAULT FALSE, \
           username VARCHAR(64), password VARCHAR(64))");
    q.exec("CREATE TABLE customers (id INTEGER AUTO_INCREMENT PRIMARY KEY, \
           name VARCHAR(64), phone VARCHAR(64), address TEXT, regular BOOLEAN NOT NULL DEFAULT FALSE, \
           email VARCHAR(128) NULL DEFAULT NULL, bankdata TEXT NULL DEFAULT NULL)");
    q.exec("CREATE TABLE work_reports (id INTEGER AUTO_INCREMENT PRIMARY KEY, \
           date TIMESTAMP, orderid INTEGER, master INTEGER, work INTEGER, quant INTEGER, spares VARCHAR(64), quants VARCHAR(64))");
    q.exec("CREATE TABLE diag_reports (id INTEGER AUTO_INCREMENT PRIMARY KEY, \
           date TIMESTAMP, orderid INTEGER, master INTEGER, inspect VARCHAR(1024), defects VARCHAR(1024), recomm VARCHAR(1024))");
    q.exec("CREATE TABLE works (id INTEGER AUTO_INCREMENT PRIMARY KEY, name VARCHAR(255), price DOUBLE, comment VARCHAR(128))");
    q.exec("CREATE TABLE spares (id INTEGER AUTO_INCREMENT PRIMARY KEY, \
           type INTEGER, name VARCHAR(255), price DOUBLE, buyingprice DOUBLE, supplier INTEGER, quantity INTEGER, partnum VARCHAR(64))");
    q.exec("CREATE TABLE spare_types (id INTEGER AUTO_INCREMENT PRIMARY KEY, name VARCHAR(64))");
    q.exec("CREATE TABLE salaries (id INTEGER AUTO_INCREMENT PRIMARY KEY, employee INTEGER, summ DOUBLE)");
    q.exec("CREATE TABLE suppliers (id INTEGER AUTO_INCREMENT PRIMARY KEY, \
           name VARCHAR(255),phone VARCHAR(255), address VARCHAR(255), comment VARCHAR(1024), whours VARCHAR(255), \
           email VARCHAR(255), website VARCHAR(255), org VARCHAR(255), bankdata TEXT, goods VARCHAR(1024))");

    q.exec("CREATE TABLE system (name VARCHAR(32) PRIMARY KEY, value_n DOUBLE, value_c VARCHAR(255))");
    q.exec("INSERT INTO system VALUES('dbversion', 8, NULL)");
    q.exec("INSERT INTO system VALUES('percMaster', 0.6, NULL)");
    q.exec("INSERT INTO system VALUES('percAcceptor', 0.1, NULL)");
    q.exec("INSERT INTO system VALUES('percFirm', 0.3, NULL)");
    q.exec("INSERT INTO system VALUES('dblocale', NULL, '" + MainWindow::lang +"')");
    q.exec("INSERT INTO system VALUES('masterCanEditWorks', 1, NULL)");
    q.exec("INSERT INTO system VALUES('masterCanEditSpares', 1, NULL)");
    q.exec("INSERT INTO system VALUES('acceptorCanEditWorks', 1, NULL)");
    q.exec("INSERT INTO system VALUES('acceptorCanEditSpares', 1, NULL)");
    q.exec("INSERT INTO system VALUES('acceptorCanEditDiag', 1, NULL)");
    q.exec("INSERT INTO system VALUES('productTypeM', 0, NULL)");
    q.exec("INSERT INTO system VALUES('productM', 0, NULL)");
    q.exec("INSERT INTO system VALUES('serialM', 0, NULL)");
    q.exec("INSERT INTO system VALUES('defectM', 0, NULL)");
    q.exec("INSERT INTO system VALUES('conditionM', 0, NULL)");
    q.exec("INSERT INTO system VALUES('completenessM', 0, NULL)");
    q.exec("INSERT INTO system VALUES('customerM', 0, NULL)");
    q.exec("INSERT INTO system VALUES('phoneM', 0, NULL)");

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
    q.exec(QString("INSERT INTO position_types VALUES(4,'") + tr("Manager") + "')");
    q.exec(QString("INSERT INTO position_types VALUES(5,'") + tr("Admin") + "')");

    q.exec("INSERT INTO employees VALUES(NULL,'Admin','Admin','Admin','Admin',5,'Admin',0,'admin','admin')");

    q.exec("CREATE TABLE part_requests (id INTEGER AUTO_INCREMENT PRIMARY KEY, \
           date TIMESTAMP, master INTEGER, orderid INTEGER, spares VARCHAR(64), quants VARCHAR(64), \
           sparesnew VARCHAR(1024), state INTEGER, comment VARCHAR(1024), summ DOUBLE)");
    q.exec("CREATE TABLE pr_states (id INTEGER PRIMARY KEY, name VARCHAR(32))");
    q.exec(QString("INSERT INTO pr_states VALUES(1,'") + tr("Placed") + "')");
    q.exec(QString("INSERT INTO pr_states VALUES(2,'") + tr("Confirmed") + "')");
    q.exec(QString("INSERT INTO pr_states VALUES(3,'") + tr("Rejected") + "')");
    q.exec(QString("INSERT INTO pr_states VALUES(4,'") + tr("Ordered") + "')");
    q.exec(QString("INSERT INTO pr_states VALUES(5,'") + tr("Awaits payment") + "')");
    q.exec(QString("INSERT INTO pr_states VALUES(6,'") + tr("Awaits receiving") + "')");
    q.exec(QString("INSERT INTO pr_states VALUES(7,'") + tr("Recieved") + "')");
    q.exec(QString("INSERT INTO pr_states VALUES(8,'") + tr("Completed") + "')");
    q.exec(QString("INSERT INTO pr_states VALUES(9,'") + tr("Info-Placed") + "')");
    q.exec(QString("INSERT INTO pr_states VALUES(10,'") + tr("Info-Confirmed") + "')");
    q.exec(QString("INSERT INTO pr_states VALUES(11,'") + tr("Info-Rejected") + "')");
    q.exec(QString("INSERT INTO pr_states VALUES(12,'") + tr("Info-Completed") + "')");

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
    q.exec(QString("INSERT INTO states VALUES(17,'") + tr("Customer-Spares ordered") + "')6");
    q.exec(QString("INSERT INTO states VALUES(18,'") + tr("Awaits issuing") + "')");
    q.exec(QString("INSERT INTO states VALUES(19,'") + tr("Accepted for repair (warranty)") + "')");
    q.exec(QString("INSERT INTO states VALUES(20,'") + tr("Customer-Spares recieved") + "')");
    q.exec(QString("INSERT INTO states VALUES(21,'") + tr("Spares recieved") + "')");

    q.exec("DROP TABLE position_types");
    q.exec("CREATE TABLE position_types (id INTEGER PRIMARY KEY, name VARCHAR(64))");
    q.exec(QString("INSERT INTO position_types VALUES(1,'") + tr("Master") + "')");
    q.exec(QString("INSERT INTO position_types VALUES(2,'") + tr("Acceptor") + "')");
    q.exec(QString("INSERT INTO position_types VALUES(3,'") + tr("Storekeeper") + "')");
    q.exec(QString("INSERT INTO position_types VALUES(4,'") + tr("Manager") + "')");
    q.exec(QString("INSERT INTO position_types VALUES(5,'") + tr("Admin") + "')");

    q.exec("UPDATE system SET value_c = '" + MainWindow::lang + "' WHERE name = 'dblocale'");

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
    q.exec("ALTER TABLE employees ADD COLUMN isactive BOOLEAN NOT NULL DEFAULT TRUE");
    q.exec("ALTER TABLE orders ADD COLUMN called BOOLEAN NOT NULL DEFAULT FALSE");
    q.exec(QString("INSERT INTO states VALUES(20,'") + tr("Customer-Spares recieved") + "')");
    q.exec(QString("INSERT INTO states VALUES(21,'") + tr("Spares recieved") + "')");
    q.exec("CREATE TABLE salaries (id INTEGER AUTO_INCREMENT PRIMARY KEY, employee INTEGER, summ DOUBLE)");
    return q.lastError();
}

QSqlError DBWork::updateTo3() /*since repaircenter v0.3.1b*/
{
    q.exec(QString("INSERT INTO position_types VALUES(3,'") + tr("Storekeeper") + "')");

    q.exec("INSERT INTO system VALUES('dblocale', NULL, '" + MainWindow::lang +"')");
    q.exec("UPDATE system SET value_n = 3 WHERE name = 'dbversion'");
    q.exec("ALTER TABLE `system` CHANGE `value_n` `value_n` DOUBLE NULL DEFAULT NULL ;");

    return q.lastError();
}

QSqlError DBWork::updateTo4() /*since repaircenter v0.3.2b*/
{
    q.exec("ALTER TABLE system CHANGE value_n value_n DOUBLE NULL DEFAULT NULL");
    q.exec("ALTER TABLE orders CHANGE cost cost DOUBLE NULL DEFAULT NULL");
    q.exec("ALTER TABLE spares CHANGE price price DOUBLE NULL DEFAULT NULL");
    q.exec("ALTER TABLE works CHANGE price price DOUBLE NULL DEFAULT NULL");
    q.exec("UPDATE system SET value_n = 4 WHERE name = 'dbversion'");
    return q.lastError();
}

QSqlError DBWork::updateTo5() /*since repaircenter v0.3.3b*/
{
    q.exec("ALTER TABLE customers ADD regular BOOLEAN NULL DEFAULT FALSE");
    q.exec("ALTER TABLE orders ADD date_called TIMESTAMP NULL default NULL");
    q.exec("UPDATE system SET value_n = 5 WHERE name = 'dbversion'");
    return q.lastError();
}

QSqlError DBWork::updateTo6() /*since repaircenter v0.3.4b*/
{
    q.exec("ALTER TABLE employees ADD username VARCHAR(64) NULL DEFAULT NULL , ADD password VARCHAR(64) NULL DEFAULT NULL");
    q.exec(QString("INSERT INTO position_types VALUES(4,'") + tr("Manager") + "')");
    q.exec(QString("INSERT INTO position_types VALUES(5,'") + tr("Admin") + "')");
    q.exec("INSERT INTO employees VALUES(NULL,'Admin','Admin','Admin','Admin',5,'Admin',0,'admin','admin')");

    q.exec("INSERT INTO system VALUES('masterCanEditWorks', 1, NULL)");
    q.exec("INSERT INTO system VALUES('masterCanEditSpares', 1, NULL)");
    q.exec(("INSERT INTO system VALUES('acceptorCanEditWorks', 1, NULL)"));
    q.exec(("INSERT INTO system VALUES('acceptorCanEditSpares', 1, NULL)"));
    q.exec("INSERT INTO system VALUES('acceptorCanEditDiag', 1, NULL)");
    q.exec("ALTER TABLE spares ADD buyingprice DOUBLE NULL DEFAULT NULL, \
           ADD supplier INT NULL DEFAULT NULL , ADD quantity INT NULL DEFAULT NULL");
    q.exec("CREATE TABLE suppliers (id INTEGER AUTO_INCREMENT PRIMARY KEY, name VARCHAR(255) NULL DEFAULT NULL, \
           phone VARCHAR(255) NULL DEFAULT NULL, address VARCHAR(255) NULL DEFAULT NULL, comment VARCHAR(1024) NULL DEFAULT NULL)");

    q.exec(QString("UPDATE system SET value_n = 6 WHERE name = 'dbversion'"));
    return q.lastError();
}

QSqlError DBWork::updateTo7() /*since repaircenter v0.3.5b*/
{
    q.exec("ALTER TABLE suppliers \
           ADD whours VARCHAR(255) NULL DEFAULT NULL, ADD email VARCHAR(255) NULL DEFAULT NULL, \
           ADD website VARCHAR(255) NULL DEFAULT NULL, ADD org VARCHAR(255) NULL DEFAULT NULL, \
           ADD bank VARCHAR(1024) NULL DEFAULT NULL, ADD goods VARCHAR(1024) NULL DEFAULT NULL");
    q.exec("ALTER TABLE customers CHANGE regular regular BOOLEAN NOT NULL DEFAULT FALSE");
    q.exec("ALTER TABLE spares ADD partnum VARCHAR(64) NULL DEFAULT NULL");

    q.exec("CREATE TABLE part_requests (id INTEGER AUTO_INCREMENT PRIMARY KEY, \
           date TIMESTAMP, master INTEGER, orderid INTEGER, spares VARCHAR(64), quants VARCHAR(64), \
           sparesnew VARCHAR(1024), state INTEGER, comment VARCHAR(1024))");
    q.exec("CREATE TABLE pr_states (id INTEGER PRIMARY KEY, name VARCHAR(32))");
    q.exec(QString("INSERT INTO pr_states VALUES(1,'") + tr("Placed") + "')");
    q.exec(QString("INSERT INTO pr_states VALUES(2,'") + tr("Confirmed") + "')");
    q.exec(QString("INSERT INTO pr_states VALUES(3,'") + tr("Rejected") + "')");
    q.exec(QString("INSERT INTO pr_states VALUES(4,'") + tr("Ordered") + "')");
    q.exec(QString("INSERT INTO pr_states VALUES(5,'") + tr("Awaits payment") + "')");
    q.exec(QString("INSERT INTO pr_states VALUES(6,'") + tr("Awaits receiving") + "')");
    q.exec(QString("INSERT INTO pr_states VALUES(7,'") + tr("Recieved") + "')");
    q.exec(QString("INSERT INTO pr_states VALUES(8,'") + tr("Completed") + "')");

    q.exec("UPDATE system SET value_n = 7 WHERE name = 'dbversion'");
    return q.lastError();
}

QSqlError DBWork::updateTo8() /*since repaircenter v0.4*/
{
    q.exec(QString("INSERT INTO pr_states VALUES(9,'") + tr("Info-Placed") + "')");
    q.exec(QString("INSERT INTO pr_states VALUES(10,'") + tr("Info-Confirmed") + "')");
    q.exec(QString("INSERT INTO pr_states VALUES(11,'") + tr("Info-Rejected") + "')");
    q.exec(QString("INSERT INTO pr_states VALUES(12,'") + tr("Info-Completed") + "')");
    q.exec("ALTER TABLE part_requests ADD summ DOUBLE NULL DEFAULT NULL");
    q.exec("ALTER TABLE customers ADD email VARCHAR(128) NULL DEFAULT NULL, ADD bankdata TEXT NULL DEFAULT NULL, \
           CHANGE address address TEXT NULL DEFAULT NULL");
    q.exec("ALTER TABLE suppliers CHANGE bank bankdata TEXT NULL DEFAULT NULL");

    q.exec("INSERT INTO system VALUES('productTypeM', 0, NULL)");
    q.exec("INSERT INTO system VALUES('productM', 0, NULL)");
    q.exec("INSERT INTO system VALUES('serialM', 0, NULL)");
    q.exec("INSERT INTO system VALUES('defectM', 0, NULL)");
    q.exec("INSERT INTO system VALUES('conditionM', 0, NULL)");
    q.exec("INSERT INTO system VALUES('completenessM', 0, NULL)");
    q.exec("INSERT INTO system VALUES('customerM', 0, NULL)");
    q.exec("INSERT INTO system VALUES('phoneM', 0, NULL)");


//    q.exec("");
//    q.exec(QString(""));
    q.exec("UPDATE system SET value_n = 8 WHERE name = 'dbversion'");
    return q.lastError();
}
