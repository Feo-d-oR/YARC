#ifndef EditOrder_H
#define EditOrder_H

#include <QDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QtSql>
#include "qtrpt.h"
#include "CommonClasses.h"
#include "qdynamiccheckbox.h"

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
    void getCustomer();
    void setDefaults();
    void mandatoryAlert();
    bool mandatoryCheck();
    void setCheckboxTemplates();
    QString composeString(QLayout *layout, QString str);
    QSqlQuery q;
    QSqlRecord rec;
    QSqlQuery qc;
    QSqlRecord recc;
    QString orderID;
    QString customerID;
    QString newCustomerID;
    bool block;
    bool isnew;
    bool saved;
    QSqlQueryModel *model_s;
    QSqlQueryModel *model_a;
    QSqlQueryModel *model_m;
    QSettings * settings;
    QSqlTableModel *model_t;
    QSqlQueryModel *model_c;
    QtRPT *report;
    QModelIndexList idx_t, idx_a, idx_m, idx_s;

protected:
    void closeEvent(QCloseEvent *event);
    void reject();

public slots:
   void getMode(QString mode, QString num);

private slots:
   void print();
   void setRptValue(const int recNo, const QString paramName, QVariant &paramValue, const int reportPage);
   void on_bCancel_clicked();
   void on_bPrint_clicked();
   void on_bSave_clicked();
   void on_bAddType_clicked();
   void on_rbNew_clicked(bool checked);
   void on_rbPrev_clicked(bool checked);
   void on_rbOld_clicked(bool checked);
   void on_cbOldCustomer_currentIndexChanged(int index);
};

#endif // EditOrder_H
