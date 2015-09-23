#ifndef CATSUPPLIERS_H
#define CATSUPPLIERS_H

#include <QDialog>
#include <QtSql>
#include <QDataWidgetMapper>

namespace Ui {
class CatSuppliers;
}

class CatSuppliers : public QDialog
{
    Q_OBJECT

public:
    explicit CatSuppliers(QWidget *parent = 0);
    ~CatSuppliers();

private slots:
    void on_bAdd_clicked();
    void on_bSave_clicked();
    void on_bClose_clicked();
    void on_bDelete_clicked();
    void on_bClear_clicked();
    void on_lSearch_returnPressed();
    void on_bSearch_clicked();

private:
    Ui::CatSuppliers *ui;
    QSqlRelationalTableModel *model;
    QDataWidgetMapper *mapper;
    void initModel();
    void search();
};

#endif // CATSUPPLIERS_H
