#include <QtSql>

QSqlError createTables()
{
    QSqlQuery q;

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

    q.exec("CREATE TABLE states (id INTEGER PRIMARY KEY, type VARCHAR(16), name VARCHAR(32))");
    q.exec(QString("INSERT INTO states VALUES(1,'accepted','") + QT_TR_NOOP("Принято в ремонт") + "')");
    q.exec(QString("INSERT INTO states VALUES(2,'accepted','") + QT_TR_NOOP("Принято на диагностику") + "')");
    q.exec(QString("INSERT INTO states VALUES(3,'complete','") + QT_TR_NOOP("Отказ клиента от ремонта") + "')");
    q.exec(QString("INSERT INTO states VALUES(4,'complete','") + QT_TR_NOOP("Отказ в ремонте") + "')");
    q.exec(QString("INSERT INTO states VALUES(5,'complete','") + QT_TR_NOOP("Диагностика выполнена") + "')");
    q.exec(QString("INSERT INTO states VALUES(6,'complete','") + QT_TR_NOOP("Ремонт выполнен") + "')");
    q.exec(QString("INSERT INTO states VALUES(7,'consent','") + QT_TR_NOOP("Ожидает согласования") + "')");
    q.exec(QString("INSERT INTO states VALUES(8,'consent','") + QT_TR_NOOP("Согласовано") + "')");
    q.exec(QString("INSERT INTO states VALUES(9,'given','") + QT_TR_NOOP("Выдано с актом диагностики") + "')");
    q.exec(QString("INSERT INTO states VALUES(10,'given','") + QT_TR_NOOP("Выдано с ремонтом") + "')");
    q.exec(QString("INSERT INTO states VALUES(11,'given','") + QT_TR_NOOP("Выдано без ремонта") + "')");
    q.exec(QString("INSERT INTO states VALUES(12,'processing','") + QT_TR_NOOP("На диагностике") + "')");
    q.exec(QString("INSERT INTO states VALUES(13,'processing','") + QT_TR_NOOP("В работе") + "')");
    q.exec(QString("INSERT INTO states VALUES(14,'waitspares','") + QT_TR_NOOP("Ожидает запчастей") + "')");
    q.exec(QString("INSERT INTO states VALUES(15,'waitspares','") + QT_TR_NOOP("Запчасти заказаны") + "')");
    q.exec(QString("INSERT INTO states VALUES(16,'waitspares','") + QT_TR_NOOP("На руках-Ожидает запчастей") + "')");
    q.exec(QString("INSERT INTO states VALUES(17,'waitspares','") + QT_TR_NOOP("На руках-Запчасти заказаны") + "')");
    q.exec(QString("INSERT INTO states VALUES(18,'complete','") + QT_TR_NOOP("Ожидает выдачи") + "')");
    q.exec(QString("INSERT INTO states VALUES(19,'accepted','") + QT_TR_NOOP("Принято в ремонт (гарантия)") + "')");
    q.exec(QString("INSERT INTO states VALUES(20,'waitspares','") + QT_TR_NOOP("На руках-Запчасти получены") + "')");

    q.exec("CREATE TABLE position_types (id INTEGER PRIMARY KEY, name VARCHAR(64))");
    q.exec(QString("INSERT INTO position_types VALUES(1,'") + QT_TR_NOOP("Мастер") + "')");
    q.exec(QString("INSERT INTO position_types VALUES(2,'") + QT_TR_NOOP("Приёмщик") + "')");
    q.exec(QString("INSERT INTO position_types VALUES(3,'") + QT_TR_NOOP("Продавец") + "')");
    q.exec(QString("INSERT INTO position_types VALUES(4,'") + QT_TR_NOOP("Кладовщик") + "')");
    q.exec(QString("INSERT INTO position_types VALUES(5,'") + QT_TR_NOOP("Закупщик") + "')");
    q.exec(QString("INSERT INTO position_types VALUES(6,'") + QT_TR_NOOP("Бухгалтер") + "')");
    q.exec(QString("INSERT INTO position_types VALUES(7,'") + QT_TR_NOOP("Директор") + "')");
    return q.lastError();
}
