#ifndef EditOrder_H
#define EditOrder_H

#include <QDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QtSql>
#include "qtrpt.h"
#include "CommonClasses.h"

namespace Ui {
class EditOrder;
}

class EditOrder : public QDialog
{
    Q_OBJECT

public:
    explicit EditOrder(QWidget *parent = 0);
    ~EditOrder();

signals:
    void orderSubmited();

private:
    Ui::EditOrder *ui;
    void allocateNumber();
    void submitOrder();
    void printOrder();
    void removeAllocated();
    void fillFields();
    void setModels();
    QSqlQuery q;
    QSqlRecord rec;
    QSqlQuery qc;
    QSqlRecord recc;
    QSqlQuery qpt;
    QString orderID;
    QString customerID;
    bool isnew;
    bool saved;
    QSqlQueryModel *model_s;
    QSqlQueryModel *model_e;
//    QSqlQueryModel *model_t;
    QSqlTableModel *model_t;
    QtRPT *report;

protected:
    void closeEvent(QCloseEvent *event);

public slots:
   void getMode(QString mode, QString num);

private slots:
   void print();
   void setRptValue(int &recNo, QString &paramName, QVariant &paramValue, int reportPage);
   void on_bCancel_clicked();
   void on_bPrint_clicked();
   void on_bSave_clicked();
   void on_bAddType_clicked();
};

#endif // EditOrder_H
