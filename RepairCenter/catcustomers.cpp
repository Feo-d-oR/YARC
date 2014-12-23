#include "catcustomers.h"
#include "ui_catcustomers.h"

CatCustomers::CatCustomers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CatCustomers)
{
    ui->setupUi(this);
    initModel();
}

CatCustomers::~CatCustomers()
{
    delete ui;
}

void CatCustomers::initModel()
{
    model = new QSqlTableModel(ui->tview);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("customers");
    ui->tview->setModel(model);

    ui->tview->hideColumn(model->fieldIndex("id"));
    ui->tview->setColumnWidth(model->fieldIndex("name"), 200);
    ui->tview->setColumnWidth(model->fieldIndex("phone"), 150);
    ui->tview->setColumnWidth(model->fieldIndex("address"), 300);
    model->setHeaderData(model->fieldIndex("name"), Qt::Horizontal, "Имя");
    model->setHeaderData(model->fieldIndex("phone"), Qt::Horizontal, "Телефон");
    model->setHeaderData(model->fieldIndex("address"), Qt::Horizontal, "Адрес");
    ui->tview->verticalHeader()->setDefaultSectionSize(24);
    ui->tview->verticalHeader()->hide();
    ui->tview->horizontalHeader()->show();

    model->select();
}

void CatCustomers::on_bAdd_clicked()
{
    model->insertRows(model->rowCount(), 1);
}

void CatCustomers::on_bSave_clicked()
{
    model->submitAll();
}

void CatCustomers::on_bClose_clicked()
{
    model->revertAll();
    close();
}

void CatCustomers::on_bDelete_clicked()
{
    QItemSelectionModel *sm = ui->tview->selectionModel();
    if (sm->hasSelection()){
        model->removeRow(sm->selectedRows().first().row());
        model->submitAll();
        model->select();
    }
}
