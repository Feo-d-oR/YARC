#ifndef GIVEORDER_H
#define GIVEORDER_H

#include <QDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QtSql>
#include "qtrpt.h"
#include "CommonClasses.h"

namespace Ui {
class GiveOrder;
}

class GiveOrder : public QDialog
{
    Q_OBJECT

public:
    explicit GiveOrder(QWidget *parent = 0);
    ~GiveOrder();

signals:
    void orderSubmited();

private:
    Ui::GiveOrder *ui;
    QString orderID;
    bool saved;
    QSqlQueryModel * model_e;

    QSqlQuery qw;
    QSqlQuery qgn;
    QSqlRecord recgn;
    QSqlQuery qs;
    QSqlRecord recw;
    QSqlRecord recfs;
    QSqlQuery q;
    QSqlQuery qc;
    QSqlQuery qt;
    QSqlRecord rec;
    QSqlRecord recc;
    QSqlRecord rect;
    QStringList lsp;
    QStringList lqt;
    QString summstr;
    int roww;
    int rows;
    int rcw;
    int rcs;
    int summ;

    void submitOrder();
    void fillFields();
    void setModels();
    void calculateSumm();
    QtRPT * report1;
    QtRPT * report2;

protected:
    void closeEvent(QCloseEvent *event);
    void reject();

public slots:
   void getMode(QString mode, QString num);

private slots:
   void on_bSumm_clicked();
   void on_bSave_clicked();
   void on_eOrderID_textChanged(const QString &arg1);
   void setRptValue(int &recNo, QString &paramName, QVariant &paramValue, int reportPage);
   void print();

   void on_bCancel_clicked();
   void on_bPrint_clicked();
   void on_eWarranty_textChanged(const QString &arg1);
};
#endif // GIVEORDER_H
