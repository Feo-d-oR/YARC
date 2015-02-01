#include "printhwdocuments.h"
#include "ui_printhwdocuments.h"

PrintHWDocuments::PrintHWDocuments(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrintHWDocuments)
{
    ui->setupUi(this);
}

PrintHWDocuments::~PrintHWDocuments()
{
    delete ui;
}

void PrintHWDocuments::allocateNumbers()
{
    lo.clear();

    for (int i=0; i<ui->eNumOrders->text().toInt(); i++)
    {
        q.exec("INSERT INTO orders (number, product) VALUES (null, 'reserved')");
        lo.append(q.lastInsertId().toString());
    }
}

void PrintHWDocuments::setRptValue(int &recNo, QString &paramName, QVariant &paramValue, int reportPage)
{
    Q_UNUSED(reportPage);
    Q_UNUSED(recNo);

    if (paramName == "number")
        paramValue = orderID;
}

void PrintHWDocuments::printOrders()
{
    QString fileName = "./print_forms/order_hw.xml";
    report = new QtRPT(this);
    if (report->loadReport(fileName) == false) {
        qDebug()<<"Report file not found: " << fileName;
    }
    connect(report,SIGNAL(setValue(int&,QString&,QVariant&,int)), this, SLOT(setRptValue(int&,QString&,QVariant&,int)));
    report->printExec(true, true);
}

void PrintHWDocuments::printWorks()
{
    QString fileName = "./print_forms/act_works_hw.xml";
    report = new QtRPT(this);
    if (report->loadReport(fileName) == false) {
        qDebug()<<"Report file not found: " << fileName;
    }
    for (int i=0; i<ui->eNumGives->text().toInt(); i++)
    {
         report->printExec(true, true);
    }
}

void PrintHWDocuments::printWarranty()
{
    QString fileName = "./print_forms/warranty_works_hw.xml";
    report = new QtRPT(this);
    if (report->loadReport(fileName) == false) {
        qDebug()<<"Report file not found: " << fileName;
    }
    for (int i=0; i<ui->eNumGives->text().toInt(); i++)
    {
         report->printExec(true, true);
    }
}

void PrintHWDocuments::printDiag()
{
    QString fileName = "./print_forms/act_diag_hw.xml";
    report = new QtRPT(this);
    if (report->loadReport(fileName) == false) {
        qDebug()<<"Report file not found: " << fileName;
    }
    for (int i=0; i<ui->eNumDiags->text().toInt(); i++)
    {
         report->printExec(true, true);
    }}

void PrintHWDocuments::on_bPrintOrders_clicked()
{
    allocateNumbers();
    for (int i=0; i<lo.size(); i++)
    {
        orderID = lo.at(i);
        printOrders();
    }
}

void PrintHWDocuments::on_bPrintGives_clicked(){
    printWorks();
    printWarranty();}

void PrintHWDocuments::on_bPrintDiags_clicked(){
    printDiag();}
