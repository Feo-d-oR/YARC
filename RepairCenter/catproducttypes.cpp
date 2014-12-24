#include "catproducttypes.h"
#include "ui_catproducttypes.h"

CatProductTypes::CatProductTypes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CatProductTypes)
{
    ui->setupUi(this);
    initModel();
}

CatProductTypes::~CatProductTypes()
{
    delete ui;
}

void CatProductTypes::initModel()
{
    model = new QSqlTableModel(ui->tview);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("product_types");
    ui->tview->setModel(model);


    ui->tview->hideColumn(model->fieldIndex("id"));
    ui->tview->setColumnWidth(model->fieldIndex("name"), 250);
    model->setHeaderData(model->fieldIndex("name"), Qt::Horizontal, tr("Наименование"));
    ui->tview->verticalHeader()->setDefaultSectionSize(24);
    ui->tview->verticalHeader()->hide();
    ui->tview->horizontalHeader()->show();

    model->select();
}

void CatProductTypes::on_bAdd_clicked()
{
    model->insertRows(model->rowCount(), 1);
    ui->tview->setCurrentIndex(model->index(model->rowCount()-1, 1));
}

void CatProductTypes::on_bSave_clicked()
{
    model->submitAll();
}

void CatProductTypes::on_bClose_clicked()
{
    model->revertAll();
    close();
}

void CatProductTypes::on_bDelete_clicked()
{
    QItemSelectionModel *sm = ui->tview->selectionModel();
    if (sm->hasSelection()){
        model->removeRow(sm->selectedRows().first().row());
        model->submitAll();
        model->select();
    }
}
