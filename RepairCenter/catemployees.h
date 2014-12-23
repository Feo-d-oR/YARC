#ifndef CATEMPLOYEES_H
#define CATEMPLOYEES_H

#include <QDialog>
#include <QtSql>
#include <QDataWidgetMapper>

namespace Ui {
class CatEmployees;
}

class CatEmployees : public QDialog
{
    Q_OBJECT

public:
    explicit CatEmployees(QWidget *parent = 0);
    ~CatEmployees();

private slots:
    void on_bAdd_clicked();
    void on_bSave_clicked();
    void on_bClose_clicked();
    void on_bDelete_clicked();

private:
    Ui::CatEmployees *ui;
    QSqlRelationalTableModel *model;
    QDataWidgetMapper *mapper;
    void initModel();
    int pt_idx;
};

#endif // CATEMPLOYEES_H
