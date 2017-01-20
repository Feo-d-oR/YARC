#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbwork.h"

QString MainWindow::lang = "";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    newdbversion = 8;
    readTranslation();
}

void MainWindow::on_bUpdate_clicked()
{
    if (connectDB())
    {
        for (int i=0 ; i<newdbversion; i++)
        {
            q.exec("SELECT value_n FROM system WHERE name = 'dbversion'");
            q.first();
            dbversion = q.value(0).toInt();
            q.clear();
            qDebug()<<"dbversion: "<< dbversion;

            if(dbversion == newdbversion)
            {
                allLatest();
                break;
            }

            if(dbversion == 0)
            {
                DBWork upd;
                QSqlError err = upd.updateTo2();
                qDebug() << err.text();
                if (err.type() != QSqlError::NoError)
                    updateError(err);
            }

            if(dbversion == 2)
            {
                DBWork upd;
                QSqlError err = upd.updateTo3();
                qDebug() << err.text();
                if (err.type() != QSqlError::NoError)
                    updateError(err);
            }

            if(dbversion == 3)
            {
                DBWork upd;
                QSqlError err = upd.updateTo4();
                qDebug() << err.text();
                if (err.type() != QSqlError::NoError)
                    updateError(err);
            }

            if(dbversion == 4)
            {
                DBWork upd;
                QSqlError err = upd.updateTo5();
                qDebug() << err.text();
                if (err.type() != QSqlError::NoError)
                    updateError(err);
            }
            if(dbversion == 5)
            {
                DBWork upd;
                QSqlError err = upd.updateTo6();
                qDebug() << err.text();
                if (err.type() != QSqlError::NoError)
                    updateError(err);
            }
            if(dbversion == 6)
            {
                DBWork upd;
                QSqlError err = upd.updateTo7();
                qDebug() << err.text();
                if (err.type() != QSqlError::NoError)
                    updateError(err);
            }
            if(dbversion == 7)
            {
                DBWork upd;
                QSqlError err = upd.updateTo8();
                qDebug() << err.text();
                if (err.type() != QSqlError::NoError)
                    updateError(err);
                else
                {
                    allUpdated();
                    break;
                }
            }
        }
    }
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
        q.exec("SET SESSION sql_mode = ''");    //disabling strict mode for easier life ;)
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

void MainWindow::readTranslation()
{
    QSettings *settings = new QSettings(QCoreApplication::applicationDirPath()+"/repaircenter.conf",QSettings::IniFormat);
    settings->setIniCodec("UTF-8");
    lang = settings->value("locale/language").toString();

    QApplication::instance()->removeTranslator(&qTranslator);
    if (lang == "") //default system language
    {
        locale = QLocale::system().name(); //reading system locale
        if (qTranslator.load("./i18n/dbtool_"+locale+".qm"))
//            if (qTranslator.load(":/langs/i18n/dbtool_"+locale+".qm"))
            langIdx = 0;
        else
        {   qTranslator.load("./i18n/dbtool_en_US.qm");\
            langIdx = 1;
            MainWindow::lang = "en_US";
        }
    }
    else if (lang == "ru_RU")//russian
    {
        locale = "ru_RU";
        qTranslator.load("./i18n/dbtool_"+locale+".qm");
        langIdx = 2;
        MainWindow::lang = "ru_RU";
    }
    else if (lang == "en_US")//english
    {
        locale = "en_US";
        qTranslator.load("./i18n/dbtool_"+locale+".qm");
        langIdx = 1;
        MainWindow::lang = "en_US";
    }
    else if (lang == "it_IT")//italian
    {
        locale = "it_IT";
        qTranslator.load("./i18n/dbtool_"+locale+".qm");
        langIdx = 1;
        MainWindow::lang = "it_IT";
    }

//    else if (lang == "nl_NL")//dutch
//    {
//        locale = "nl_NL";
//        qTranslator.load("./i18n/dbtool_"+locale+".qm");
//        langIdx = 3;
//        MainWindow::lang = "nl_NL";
//    }
    QApplication::installTranslator(&qTranslator);
}

void MainWindow::readSettings()
{
    QSettings *settings = new QSettings(QCoreApplication::applicationDirPath()+"/repaircenter.conf",QSettings::IniFormat);
    settings->setIniCodec("UTF-8");
    ui->eserver->setText(settings->value("mysql/hostname").toString());
    ui->eport->setText(settings->value("mysql/port").toString());
    ui->edbname->setText(settings->value("mysql/database").toString());
    ui->eusername->setText(settings->value("mysql/user").toString());
//    ui->epassword->setText("********");
}

void MainWindow::saveSettings()
{
    QSettings *settings = new QSettings(QCoreApplication::applicationDirPath()+"/repaircenter.conf",QSettings::IniFormat);
    settings->setIniCodec("UTF-8");
    settings->setValue("mysql/hostname", ui->server->text());
    settings->setValue("mysql/port", ui->port->text());
    settings->setValue("mysql/database", ui->dbname->text());
    settings->setValue("mysql/user", ui->username2->text());
    crypto = SimpleCrypt(Q_UINT64_C(0xd3752f1e9b140689));
    settings->setValue("mysql/password", crypto.encryptToString(ui->password2->text()));

    switch(ui->language->currentIndex())  {
    case 0://system default
        settings->setValue("locale/language", "");
        break;
    case 1://english
        settings->setValue("locale/language", "en_US");
        break;
    case 2://russian
        settings->setValue("locale/language", "ru_RU");
        break;
    case 3://italian
        settings->setValue("locale/language", "it_IT");
        break;
//    case 3://dutch
//        settings->setValue("locale/language", "nl_NL");
//        break;

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
            q.exec("SET SESSION sql_mode = ''");    //disabling strict mode for easier life ;)

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
    QApplication::instance()->removeTranslator(&qTranslator);
    switch(index){
    case 0://system default
        locale = QLocale::system().name(); //reading system locale
        if (qTranslator.load("./i18n/dbtool_"+locale+".qm"))
        {langIdx = 0;
         break;}
        else
        {   qTranslator.load("./i18n/dbtool_en_US.qm");\
            langIdx = 1;
            MainWindow::lang = "en_US";
            break;
        }
        break;
    case 1://english
        locale = "en_US";
        qTranslator.load("./i18n/dbtool_"+locale+".qm");
        langIdx = 1;
        MainWindow::lang = "en_US";
        break;
    case 2://russian
        locale = "ru_RU";
        qTranslator.load("./i18n/dbtool_"+locale+".qm");
        langIdx = 2;
        MainWindow::lang = "ru_RU";
        break;
    case 3://italian
        locale = "it_IT";
        qTranslator.load("./i18n/dbtool_"+locale+".qm");
        langIdx = 3;
        MainWindow::lang = "it_IT";
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
    readSettings();
}

void MainWindow::on_bRetranslate_clicked()
{
    if (connectDB())
    {
        DBWork upd;
        QSqlError err = upd.retranslate();
        qDebug() << err.text();
        if (err.type() != QSqlError::NoError)
            updateError(err);
        else
            allUpdated();
    }
}
