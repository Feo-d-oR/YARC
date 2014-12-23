#include "editdiagreport.h"
#include "ui_editdiagreport.h"

EditDiagReport::EditDiagReport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDiagReport)
{
    ui->setupUi(this);
}

EditDiagReport::~EditDiagReport()
{
    delete ui;
}
