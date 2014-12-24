#include "catconstants.h"
#include "ui_catconstants.h"

CatConstants::CatConstants(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CatConstants)
{
    ui->setupUi(this);
    initModel();
}

CatConstants::~CatConstants()
{
    delete ui;
}

void CatConstants::initModel()
{
    model = new QSqlTableModel(ui->tview);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("constants");
    ui->tview->setModel(model);

    ui->tview->hideColumn(model->fieldIndex("id"));
    ui->tview->setColumnWidth(model->fieldIndex("name"), 200);
    ui->tview->setColumnWidth(model->fieldIndex("value"), 300);
    model->setHeaderData(model->fieldIndex("name"), Qt::Horizontal, tr("Константа"));
    model->setHeaderData(model->fieldIndex("value"), Qt::Horizontal, tr("Значение"));
    ui->tview->verticalHeader()->setDefaultSectionSize(24);
    ui->tview->verticalHeader()->hide();
    ui->tview->horizontalHeader()->show();
    model->select();

}

void CatConstants::on_bSave_clicked()
{
    model->submitAll();
    close();
}

void CatConstants::on_bClose_clicked()
{
    close();
}
