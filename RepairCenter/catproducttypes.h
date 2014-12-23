#ifndef CATPRODUCTTYPES_H
#define CATPRODUCTTYPES_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class CatProductTypes;
}

class CatProductTypes : public QDialog
{
    Q_OBJECT

public:
    explicit CatProductTypes(QWidget *parent = 0);
    ~CatProductTypes();

private slots:
    void on_bAdd_clicked();
    void on_bSave_clicked();
    void on_bClose_clicked();
    void on_bDelete_clicked();

private:
    Ui::CatProductTypes *ui;
    QSqlTableModel *model;
    void initModel();
};

#endif // CATPRODUCTTYPES_H
