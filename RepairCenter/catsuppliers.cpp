#include "catsuppliers.h"
#include "ui_catsuppliers.h"

CatSuppliers::CatSuppliers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CatSuppliers)
{
    ui->setupUi(this);
    initModel();
}

CatSuppliers::~CatSuppliers()
{
    delete ui;
}

void CatSuppliers::initModel()
{
    model = new QSqlTableModel(ui->tview);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("suppliers");
    ui->tview->setModel(model);

    ui->tview->hideColumn(model->fieldIndex("id"));
    ui->tview->setColumnWidth(model->fieldIndex("name"), 200);
    ui->tview->setColumnWidth(model->fieldIndex("phone"), 150);
    ui->tview->setColumnWidth(model->fieldIndex("address"), 300);
    ui->tview->setColumnWidth(model->fieldIndex("comment"), 500);
    model->setHeaderData(model->fieldIndex("name"), Qt::Horizontal, tr("Name"));
    model->setHeaderData(model->fieldIndex("phone"), Qt::Horizontal, tr("Phone"));
    model->setHeaderData(model->fieldIndex("address"), Qt::Horizontal, tr("Address"));
    model->setHeaderData(model->fieldIndex("comment"), Qt::Horizontal, tr("Comment"));
    ui->tview->verticalHeader()->setDefaultSectionSize(24);
    ui->tview->verticalHeader()->hide();
    ui->tview->horizontalHeader()->show();

    model->select();
}

void CatSuppliers::on_bAdd_clicked()
{
    int rc;
    rc = model->rowCount();
    model->insertRows(rc, 1);
    ui->tview->selectRow(rc);
}

void CatSuppliers::on_bSave_clicked()
{
    model->submitAll();
}

void CatSuppliers::on_bClose_clicked()
{
    model->revertAll();
    close();
}

void CatSuppliers::on_bDelete_clicked()
{
    QItemSelectionModel *sm = ui->tview->selectionModel();
    if (sm->hasSelection()){
        model->removeRow(sm->selectedRows().first().row());
        model->submitAll();
        model->select();
    }
}
