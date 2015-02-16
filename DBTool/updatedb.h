#ifndef UPDATEDB_H
#define UPDATEDB_H

#include <QtSql>

QSqlError updateTo2() /*repaircenter greater than v0.3*/
{
    QSqlQuery q;
    q.exec("CREATE TABLE system (name VARCHAR(32) PRIMARY KEY, value_n INTEGER, value_c VARCHAR(255))");
    q.exec("INSERT INTO system VALUES('dbversion', 2, NULL)");
    q.exec("ALTER TABLE employees DROP hired, DROP dismissed");
    q.exec("ALTER TABLE employees ADD COLUMN isactive BOOLEAN NOT NULL DEFAULT 1");
    q.exec("ALTER TABLE orders ADD COLUMN called BOOLEAN NOT NULL DEFAULT 0");
    q.exec(QString("INSERT INTO states VALUES(20,'waitspares','") + QT_TR_NOOP("На руках-Запчасти получены") + "')");
    return q.lastError();
}

#endif // UPDATEDB_H
