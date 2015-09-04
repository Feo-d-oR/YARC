#ifndef USERS_H
#define USERS_H

#include <QDialog>
#include <QtSql>
#include <QDataWidgetMapper>
#include <QCryptographicHash>

namespace Ui {
class Users;
}

class Users : public QDialog
{
    Q_OBJECT

private slots:
    void on_bDelete_clicked();
    void on_bAdd_clicked();

public:
    explicit Users(QWidget *parent = 0);
    ~Users();

private:
    void initModelUsers();
    Ui::Users *ui;
    int tidx;
    QSqlQuery q;
    QSqlQueryModel *model_t;
    QSqlRelationalTableModel * model;

};

#endif // USERS_H
