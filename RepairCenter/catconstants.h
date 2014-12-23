#ifndef CATCONSTANTS_H
#define CATCONSTANTS_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class CatConstants;
}

class CatConstants : public QDialog
{
    Q_OBJECT

public:
    explicit CatConstants(QWidget *parent = 0);
    ~CatConstants();

private slots:
    void on_bSave_clicked();
    void on_bClose_clicked();

private:
    Ui::CatConstants *ui;
    QSqlTableModel *model;
    void initModel();
};

#endif // CATCONSTANTS_H
