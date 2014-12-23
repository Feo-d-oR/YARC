#include "jrndiagreports.h"
#include "ui_jrndiagreports.h"

JrnDiagReports::JrnDiagReports(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JrnDiagReports)
{
    ui->setupUi(this);
}

JrnDiagReports::~JrnDiagReports()
{
    delete ui;
}
