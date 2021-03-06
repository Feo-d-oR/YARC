#ifndef CATCUSTOMERS_H
#define CATCUSTOMERS_H

#include <QDialog>
#include <QtSql>
#include <QDataWidgetMapper>

namespace Ui {
class CatCustomers;
}

class CatCustomers : public QDialog
{
    Q_OBJECT

public:
    explicit CatCustomers(QWidget *parent = 0);
    ~CatCustomers();

private slots:
    void on_bAdd_clicked();
    void on_bSave_clicked();
    void on_bClose_clicked();
    void on_bDelete_clicked();
    void on_bClear_clicked();
    void on_eSearchName_returnPressed();

private:
    Ui::CatCustomers *ui;
    QSqlRelationalTableModel *model;
    QDataWidgetMapper *mapper;
    void initModel();
};

#endif // CATCUSTOMERS_H
