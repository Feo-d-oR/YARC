#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbwork.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    readSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::dbCheckConnect()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(ui->server->text());
    db.setPort(ui->port->text().toInt());
    db.setUserName(ui->username->text());
    db.setPassword(ui->password->text());
    db.setDatabaseName(ui->dbname->text());
    if(db.open())
        return true;
    else
        return false;
    return false;
}

bool MainWindow::connectDB()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(ui->eserver->text());
    db.setPort(ui->eport->text().toInt());
    db.setUserName(ui->eusername->text());
    db.setPassword(ui->epassword->text());
    db.setDatabaseName(ui->edbname->text());

    if(db.open())
    {
        q = QSqlQuery(db);
        return true;
    }
    else
    {
        QMessageBox mb;
        mb.setWindowTitle(tr("Error!"));
        mb.setText(tr("Unable to connect to the database!"));
        mb.setInformativeText(db.lastError().text());
        QPushButton *bOk = mb.addButton(QMessageBox::Ok);
        mb.setDefaultButton(bOk);
        mb.exec();
        return false;
    }
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

    QString lang = settings->value("locale/language").toString();
    if (lang == "") //default system language
        ui->language->setCurrentIndex(0);

    else if (lang == "ru_RU")//russian
        ui->language->setCurrentIndex(1);

    else if (lang == "en_US")//english
        ui->language->setCurrentIndex(2);
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

    switch(ui->language->currentIndex())  {
    case 0://system default
        settings->setValue("locale/language", "");
        break;
    case 1://russian
        settings->setValue("locale/language", "ru_RU");
        break;
    case 2://american english
        settings->setValue("locale/language", "en_US");
        break;
    }
    settings->sync();

}

void MainWindow::on_create_clicked()
{
    if (dbCheckConnect())
    {
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
        if (db.open())
        {
            q = QSqlQuery(db);
            q.exec("CREATE DATABASE "+ui->dbname->text()+" DEFAULT CHARACTER SET utf8 COLLATE utf8_unicode_ci");
            q.exec("GRANT ALL PRIVILEGES ON "+ui->dbname->text()+".* TO '"+ui->username2->text()+"'@'%' IDENTIFIED BY '"+ui->password2->text()+"' WITH GRANT OPTION");
            db.close();
            db.setHostName(ui->server->text());
            db.setPort(ui->port->text().toInt());
            db.setUserName(ui->username->text());
            db.setPassword(ui->password->text());
            db.setDatabaseName(ui->dbname->text());
            db.open();

            DBWork dbw;
            dbw.createTables();


            if (ui->cbSave->isChecked())
                saveSettings();

            QMessageBox mb;
            mb.setWindowTitle(tr("Done!"));
            mb.setText(tr("Database succesfully created!"));
            QPushButton *bOk = mb.addButton(QMessageBox::Ok);
            mb.setDefaultButton(bOk);
            mb.exec();
        }
        else
        {
            QMessageBox mb;
            mb.setWindowTitle(tr("Error!"));
            mb.setText(tr("Unable to create database!"));
            mb.setInformativeText(db.lastError().text());
            QPushButton *bOk = mb.addButton(QMessageBox::Ok);
            mb.setDefaultButton(bOk);
            mb.exec();
        }
    }
}

void MainWindow::on_bUpdate_clicked()
{
    if (connectDB())
    {
    q.exec("SELECT value_n FROM system WHERE name = 'dbversion'");
    q.first();

    if(q.value(0).toFloat() == 2)
        allLatest();

    if(q.value(0).toFloat() == 0)
    {
        DBWork upd;
        QSqlError err = upd.updateTo2();
        qDebug() << err.text();
        if (err.type() == QSqlError::NoError)
            allUpdated();
        else
            updateError(err);
    }


//    q.exec("SELECT * FROM system WHERE name = 'dbversion'");
//    rec = q.record();
//    q.first();
//    dbversion = q.value(rec.indexOf("value_n"));

//    if(dbversion == 2)
//        updateTo3();
    }
}

void MainWindow::allUpdated()
{
    QMessageBox mb;
    mb.setWindowTitle(tr("Done!"));
    mb.setText(tr("Database succesfully updated!"));
    QPushButton *bOk = mb.addButton(QMessageBox::Ok);
    mb.setDefaultButton(bOk);
    mb.exec();
}

void MainWindow::allLatest()
{
    QMessageBox mb;
    mb.setWindowTitle(tr("Done!"));
    mb.setText(tr("Database doesn't need to be updated"));
    QPushButton *bOk = mb.addButton(QMessageBox::Ok);
    mb.setDefaultButton(bOk);
    mb.exec();
}

void MainWindow::allCleared()
{
    QMessageBox mb;
    mb.setWindowTitle(tr("Done!"));
    mb.setText(tr("Database succecfully cleared!"));
    QPushButton *bOk = mb.addButton(QMessageBox::Ok);
    mb.setDefaultButton(bOk);
    mb.exec();
}

void MainWindow::updateError(QSqlError error)
{
    QMessageBox mb;
    mb.setWindowTitle(tr("Error!"));
    mb.setText(tr("Something went wrong during update"));
    mb.setInformativeText(error.text());
    QPushButton *bOk = mb.addButton(QMessageBox::Ok);
    mb.setDefaultButton(bOk);
    mb.exec();
}

void MainWindow::on_bClearSalary_clicked()
{
    if(connectDB())
    {
        q.exec("TRUNCATE TABLE salaries");

        if(q.lastError().type() == QSqlError::NoError)
            allCleared();
        else
        {
            QMessageBox mb;
            mb.setWindowTitle(tr("Error!"));
            mb.setText(tr("Something went wrong during clearing"));
            mb.setInformativeText(q.lastError().text());
            QPushButton *bOk = mb.addButton(QMessageBox::Ok);
            mb.setDefaultButton(bOk);
            mb.exec();
        }
    }
}

void MainWindow::on_bClearOrders_clicked()
{
    connectDB();
    q.exec("DELETE FROM orders WHERE state IN (9,10,11)");

    if(q.lastError().type() == QSqlError::NoError)
        allCleared();
    else
    {
        QMessageBox mb;
        mb.setWindowTitle(tr("Error!"));
        mb.setText(tr("Something went wrong during clearing"));
        mb.setInformativeText(q.lastError().text());
        QPushButton *bOk = mb.addButton(QMessageBox::Ok);
        mb.setDefaultButton(bOk);
        mb.exec();
    }
}

void MainWindow::on_language_activated(int index)
{
    qDebug()<< "index: "<<index;
    QApplication::instance()->removeTranslator(&qTranslator);
    switch(index){
    case 0://system default
        locale = QLocale::system().name(); //reading system locale
        if (qTranslator.load(":/langs/i18n/dbtool_"+locale+".qm"))
            break;
        else
        {   qTranslator.load(":/langs/i18n/repaircenter_en_US.qm");\
            langIdx = 0;
            break;
        }
        break;
    case 1://russian
        locale = "ru_RU";
        qTranslator.load(":/langs/i18n/dbtool_"+locale+".qm");
        langIdx = 1;
        break;
    case 2://american english
        locale = "en_US";
        qTranslator.load(":/langs/i18n/dbtool_"+locale+".qm");
        langIdx = 2;
        break;
    }
    QApplication::installTranslator(&qTranslator);
}

void MainWindow::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        // retranslate designer form (single inheritance approach)
        ui->retranslateUi(this);
        ui->language->setCurrentIndex(langIdx);
    }

    // remember to call base class implementation
    QMainWindow::changeEvent(event);
}

