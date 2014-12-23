#include "createdbdialog.h"
#include "ui_createdbdialog.h"

CreateDBDialog::CreateDBDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateDBDialog)
{
    ui->setupUi(this);
    CreateDBDialog::activateWindow();
}

CreateDBDialog::~CreateDBDialog()
{
    delete ui;
}

void CreateDBDialog::on_close_clicked()
{
    close();
}

void CreateDBDialog::on_create_clicked()
{
    if (dbCheckConnect()){
        QMessageBox mb;
        mb.setWindowTitle("Ошибка!");
        mb.setText("База данных с таким именем уже существует!");
        QPushButton *bOk = mb.addButton(QMessageBox::Ok);
        mb.setDefaultButton(bOk);
        mb.exec();
    }
    else {
        createDatabase();
        if (ui->cbSave->isChecked())
            saveSettings();
        close();
    }
}

bool CreateDBDialog::dbCheckConnect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(ui->server->text());
    db.setPort(ui->port->text().toInt());
    db.setUserName(ui->username->text());
    db.setPassword(ui->password->text());
    db.setDatabaseName(ui->dbname->text());
    if(db.open())
        return true;
    else
        return false;
}

void CreateDBDialog::createDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(ui->server->text());
    db.setPort(ui->port->text().toInt());
    db.setUserName(ui->username->text());
    db.setPassword(ui->password->text());
    db.open();

    QSqlQuery q;
    q.exec("CREATE DATABASE "+ui->dbname->text()+" DEFAULT CHARACTER SET utf8 COLLATE utf8_unicode_ci");
    db.close();
    db.setHostName(ui->server->text());
    db.setPort(ui->port->text().toInt());
    db.setUserName(ui->username->text());
    db.setPassword(ui->password->text());
    db.setDatabaseName(ui->dbname->text());
    db.open();
    q.exec("create table orders (number INTEGER AUTO_INCREMENT PRIMARY KEY, date_in TIMESTAMP, state VARCHAR(16), date_out TIMESTAMP, customer INTEGER, phone INTEGER, product_type INTEGER, product VARCHAR(32), serial VARCHAR(16), disease VARCHAR(255), cond VARCHAR(255), complect VARCHAR(255), cost DECIMAL(10, 2), acceptor INTEGER, master INTEGER, giver INTEGER, warranty VARCHAR(16), comment VARCHAR(255))");
    q.exec("create table product_types (id INTEGER AUTO_INCREMENT PRIMARY KEY, name VARCHAR(32))");
    q.exec("CREATE TABLE employees (id INTEGER AUTO_INCREMENT PRIMARY KEY, name VARCHAR(64), fullname VARCHAR(255), phone VARCHAR(64), address VARCHAR(255), position_type INTEGER, position VARCHAR(128), hired TIMESTAMP, dismissed TIMESTAMP)");
    q.exec("CREATE TABLE customers (id INTEGER AUTO_INCREMENT PRIMARY KEY, name VARCHAR(64), phone VARCHAR(64), address VARCHAR(128))");
    q.exec("CREATE TABLE work_reports (id INTEGER AUTO_INCREMENT PRIMARY KEY, date TIMESTAMP, orderid INTEGER, master INTEGER, work INTEGER, quant INTEGER, spares VARCHAR(64), quants VARCHAR(64))");
    q.exec("CREATE TABLE diag_reports (id INTEGER AUTO_INCREMENT PRIMARY KEY, date TIMESTAMP, orderid INTEGER, master INTEGER, inspect VARCHAR(1024), defects VARCHAR(1024), recomm VARCHAR(1024))");
    q.exec("CREATE TABLE works (id INTEGER AUTO_INCREMENT PRIMARY KEY, name VARCHAR(255), price DECIMAL(10, 2), comment VARCHAR(128))");
    q.exec("CREATE TABLE spares (id INTEGER AUTO_INCREMENT PRIMARY KEY, type INTEGER, name VARCHAR(255), price DECIMAL(10, 2))");
    q.exec("CREATE TABLE spare_types (id INTEGER AUTO_INCREMENT PRIMARY KEY, name VARCHAR(64))");

    q.exec("CREATE TABLE states (id INTEGER PRIMARY KEY, type VARCHAR(16), name VARCHAR(32))");
    q.exec("INSERT INTO states VALUES(1,'accepted','Принято в ремонт')");
    q.exec("INSERT INTO states VALUES(2,'accepted','Принято на диагностику')");
    q.exec("INSERT INTO states VALUES(3,'complete','Отказ клиента от ремонта')");
    q.exec("INSERT INTO states VALUES(4,'complete','Отказ в ремонте')");
    q.exec("INSERT INTO states VALUES(5,'complete','Диагностика выполнена')");
    q.exec("INSERT INTO states VALUES(6,'complete','Ремонт выполнен')");
    q.exec("INSERT INTO states VALUES(7,'consent','Ожидает согласования')");
    q.exec("INSERT INTO states VALUES(8,'consent','Согласовано')");
    q.exec("INSERT INTO states VALUES(9,'given','Выдано с актом диагностики')");
    q.exec("INSERT INTO states VALUES(10,'given','Выдано с ремонтом')");
    q.exec("INSERT INTO states VALUES(11,'given','Выдано без ремонта')");
    q.exec("INSERT INTO states VALUES(12,'processing','На диагностике')");
    q.exec("INSERT INTO states VALUES(13,'processing','В работе')");
    q.exec("INSERT INTO states VALUES(14,'waitspares','Ожидает запчастей')");
    q.exec("INSERT INTO states VALUES(15,'waitspares','Запчасти заказаны')");
    q.exec("INSERT INTO states VALUES(16,'waitspares','На руках-Ожидает запчастей')");
    q.exec("INSERT INTO states VALUES(17,'waitspares','На руках-Запчасти заказаны')");
    q.exec("INSERT INTO states VALUES(18,'complete','Ожидает выдачи')");
    q.exec("INSERT INTO states VALUES(19,'accepted','Принято в ремонт (гарантия)')");

    q.exec("CREATE TABLE constants (id INTEGER PRIMARY KEY, name VARCHAR(32), value VARCHAR(128))");
    q.exec("INSERT INTO constants VALUES(1,'Название организации', NULL)");
    q.exec("INSERT INTO constants VALUES(2,'ИНН',NULL)");
    q.exec("INSERT INTO constants VALUES(3,'Адрес',NULL)");
    q.exec("INSERT INTO constants VALUES(4,'Телефон',NULL)");
    q.exec("INSERT INTO constants VALUES(5,'Время работы',NULL)");
    q.exec("INSERT INTO constants VALUES(6,'Выходные',NULL)");

    q.exec("CREATE TABLE position_types (id INTEGER PRIMARY KEY, name VARCHAR(64))");
    q.exec("INSERT INTO position_types VALUES(1,'Мастер')");
    q.exec("INSERT INTO position_types VALUES(2,'Приёмщик')");
    q.exec("INSERT INTO position_types VALUES(3,'Продавец')");
    q.exec("INSERT INTO position_types VALUES(4,'Кладовщик')");
    q.exec("INSERT INTO position_types VALUES(5,'Закупщик')");
    q.exec("INSERT INTO position_types VALUES(6,'Бухгалтер')");
    q.exec("INSERT INTO position_types VALUES(7,'Директор')");
}

void CreateDBDialog::saveSettings()
{
    QSettings *settings = new QSettings("db.conf",QSettings::IniFormat);
    settings->setValue("mysql/hostname", ui->server->text());
    settings->setValue("mysql/port", ui->port->text());
    settings->setValue("mysql/database", ui->dbname->text());
    settings->setValue("mysql/user", ui->username->text());
    settings->setValue("mysql/password", ui->password->text());
    settings->sync();
}
