#ifndef CATSUPPLIERS_H
#define CATSUPPLIERS_H

#include <QDialog>
#include <QtSql>

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

private:
    Ui::CatSuppliers *ui;
    QSqlTableModel *model;
    void initModel();
};

#endif // CATSUPPLIERS_H
