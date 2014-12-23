/*
Name: QtRpt
Version: 1.4.5
Programmer: Aleksey Osipov
e-mail: aliks-os@ukr.net
2012-2014
*/

#include "RptSql.h"
#include <QTextCodec>

RptSql::RptSql(QString dbType, QString dbName, QString dbHost, QString dbUser, QString dbPassword, int dbPort, QString dbConnectionName, QObject *parent) : QObject(parent) {
    /*#ifdef QT_DEBUG
      qDebug() << "Running a debug build";
    #else
      qDebug() << "Running a release build";
    #endif*/

    db = QSqlDatabase::addDatabase(dbType, dbConnectionName.isEmpty() ? QLatin1String(QSqlDatabase::defaultConnection) : dbConnectionName);
    db.setDatabaseName(dbName);
    db.setHostName(dbHost);
    db.setUserName(dbUser);
    db.setPassword(dbPassword);
    if(dbPort)
        db.setPort(dbPort);
}

bool RptSql::openQuery(QString sql, QString dbCoding, QString charsetCoding) {
    db.open();
    if (!db.isOpen()) {
        qDebug() << "Failed open DB";
        qDebug()<<db.lastError().text();
    } else {
        qDebug() << "open DB";
    }

    query = new QSqlQuery(db);
    if (!dbCoding.isEmpty()) {
        if (db.driverName().contains("MYSQL"))
            query->exec("set names '"+dbCoding+"'");
    }
    if (!charsetCoding.isEmpty()) {
        QTextCodec *codec;
        qDebug()<<dbCoding;
        codec = QTextCodec::codecForName( QString(charsetCoding).toLocal8Bit().constData() );
        QTextCodec::setCodecForLocale(codec);
        qDebug()<<QTextCodec::codecForLocale()->name();
    }

    if (!query->exec(sql)) {
        qDebug()<<query->lastError().text();
        return false;
    }

    return true;
}

QString RptSql::getFieldValue(QString fieldName, int recNo) {
    if (query->isActive()){
        if (recNo >= getRecordCount()) {
            qDebug() << "recNo more than recordCount";
            return "";
        } else {
            query->seek(recNo);
            int fieldNo = query->record().indexOf(fieldName);
            return query->value(fieldNo).toString();
        }
    } else {
        qDebug() << "Query is not active";
        return "";
    }
}

int RptSql::getRecordCount() {
    if (query->isActive()){
        query->last();
        return query->at()+1;
    } else return 0;
}
