#ifndef DBWORK_H
#define DBWORK_H

#include <QObject>
#include <QtSql>

class DBWork : public QObject
{
    Q_OBJECT
public:
    explicit DBWork(QObject *parent = 0);
    QSqlError createTables();
    QSqlError updateTo2();
    QSqlError updateTo3();
    QSqlError updateTo4();
    QSqlError updateTo5();
    QSqlError updateTo6();
    QSqlError retranslate();

signals:

public slots:

private:
    QSqlQuery q;
};

#endif // DBWORK_H
