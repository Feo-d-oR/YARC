#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "createdb.h"
#include "updatedb.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::dbCheckConnect()
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

bool MainWindow::connectDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(ui->eserver->text());
    db.setPort(ui->eport->text().toInt());
    db.setUserName(ui->eusername->text());
    db.setPassword(ui->epassword->text());
    db.setDatabaseName(ui->edbname->text());
    if(db.open())
        return true;
    else
        return false;
}

void MainWindow::readSettings()
{
    QSettings * settings = new QSettings(QCoreApplication::applicationDirPath()+"/settings.conf",QSettings::IniFormat);
    settings->setIniCodec("UTF-8");
    ui->eserver->setText(settings->value("mysql/hostname").toString());
    ui->eport->setText(settings->value("mysql/port").toString());
    ui->edbname->setText(settings->value("mysql/database").toString());
    ui->eusername->setText(settings->value("mysql/user").toString());
    ui->epassword->setText(settings->value("mysql/password").toString());
}

void MainWindow::saveSettings()
{
    QSettings * settings = new QSettings(QCoreApplication::applicationDirPath()+"/settings.conf",QSettings::IniFormat);
    settings->setIniCodec("UTF-8");
    settings->setValue("mysql/hostname", ui->server->text());
    settings->setValue("mysql/port", ui->port->text());
    settings->setValue("mysql/database", ui->dbname->text());
    settings->setValue("mysql/user", ui->username2->text());
    settings->setValue("mysql/password", ui->password2->text());
    settings->sync();
}

void MainWindow::on_create_clicked()
{
    if (dbCheckConnect()){
        QMessageBox mb;
        mb.setWindowTitle(tr("Error!"));
        mb.setText(tr("Database with that name already exist!"));
        QPushButton *bOk = mb.addButton(QMessageBox::Ok);
        mb.setDefaultButton(bOk);
        mb.exec();
    }
    else {
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName(ui->server->text());
        db.setPort(ui->port->text().toInt());
        db.setUserName(ui->username->text());
        db.setPassword(ui->password->text());
        db.open();

        QSqlQuery q;
        q.exec("CREATE DATABASE "+ui->dbname->text()+" DEFAULT CHARACTER SET utf8 COLLATE utf8_unicode_ci");
        q.exec("GRANT ALL PRIVILEGES ON "+ui->dbname->text()+".* TO '"+ui->username2->text()+"'@'%' IDENTIFIED BY '"+ui->password2->text()+"' WITH GRANT OPTION");
        db.close();
        db.setHostName(ui->server->text());
        db.setPort(ui->port->text().toInt());
        db.setUserName(ui->username->text());
        db.setPassword(ui->password->text());
        db.setDatabaseName(ui->dbname->text());
        db.open();

        createTables();

        if (ui->cbSave->isChecked())
            saveSettings();
        close();
    }
}

void MainWindow::on_bUpdate_clicked()
{
    connectDB();
    QSqlQuery q;
    QSqlRecord rec;

    qDebug() << "check:" << q.exec("SHOW TABLES LIKE 'system'");

    if (!q.exec("SELECT * FROM system WHERE name = 'dbversion'"))
        updateTo2();

//    q.exec("SELECT * FROM system WHERE name = 'dbversion'");
//    rec = q.record();
//    q.first();
//    dbversion = q.value(rec.indexOf("value_n")).toInt();

//    if(dbversion == 2)
//        updateTo3();

}

void MainWindow::on_mExit_triggered()
{
    close();
}
