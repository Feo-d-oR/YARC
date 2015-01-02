#ifndef GIVEORDERDIAG_H
#define GIVEORDERDIAG_H

#include <QDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QtSql>
#include "qtrpt.h"
#include "CommonClasses.h"

namespace Ui {
class GiveOrderDiag;
}

class GiveOrderDiag : public QDialog
{
    Q_OBJECT

public:
    explicit GiveOrderDiag(QWidget *parent = 0);
    ~GiveOrderDiag();

signals:
    void orderSubmited();

private:
    Ui::GiveOrderDiag *ui;
    QString orderID;
    bool saved;
    QSqlQueryModel * model_e;
    QSqlQuery qf;
    QSqlQuery q;
    QSqlQuery qc;
    QSqlQuery qt;
    QSqlRecord recf;
    QSqlRecord rec;
    QSqlRecord recc;
    QSqlRecord rect;
    void submitOrder();
    void fillFields();
    void setModels();
    QtRPT * report1;

protected:
    void closeEvent(QCloseEvent *event);
    void reject();

public slots:
   void getMode(QString mode, QString num);

private slots:
   void on_bSave_clicked();
   void on_eOrderID_textChanged(const QString &arg1);
   void setRptValue(int &recNo, QString &paramName, QVariant &paramValue, int reportPage);
   void print();
   void on_bCancel_clicked();
   void on_bPrint_clicked();
};

#endif // GIVEORDERDIAG_H
