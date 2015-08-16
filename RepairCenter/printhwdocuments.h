#ifndef PRINTHWDOCUMENTS_H
#define PRINTHWDOCUMENTS_H

#include <QDialog>
#include <QtSql>
#include "qtrpt.h"
#include "CommonClasses.h"

namespace Ui {
class PrintHWDocuments;
}

class PrintHWDocuments : public QDialog
{
    Q_OBJECT

public:
    explicit PrintHWDocuments(QWidget *parent = 0);
    ~PrintHWDocuments();

private:
    Ui::PrintHWDocuments *ui;
    QSqlQuery q;
    void allocateNumbers();
    QStringList lo;
    QString orderID;
    QtRPT *report;

private slots:
   void printOrders();
   void printWorks();
   void printWarranty();
   void printDiag();
   void setRptValue(const int recNo, const QString paramName, QVariant &paramValue, const int reportPage);

   void on_bPrintOrders_clicked();
   void on_bPrintGives_clicked();
   void on_bPrintDiags_clicked();
};

#endif // PRINTHWDOCUMENTS_H
