#ifndef DBWORK_H
#define DBWORK_H

#include <QObject>
#include <QtSql>
#include <QSettings>
#include "createdbdialog.h"
#include "dbsettingsdialog.h"

static bool dbConnect()
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        QSettings *settings = new QSettings("db.conf",QSettings::IniFormat);
        db.setHostName(settings->value("mysql/hostname").toString());
        db.setPort(settings->value("mysql/port").toInt());
        db.setDatabaseName(settings->value("mysql/database").toString());
        db.setUserName(settings->value("mysql/user").toString());
        db.setPassword(settings->value("mysql/password").toString());
        if (db.open())
            return true;
        else
            return false;
    }

#endif // DBWORK_H
