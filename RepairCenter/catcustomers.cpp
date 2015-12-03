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
    model = new QSqlRelationalTableModel(ui->tview);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    model->setTable("customers");
    ui->tview->setModel(model);

    ui->tview->hideColumn(model->fieldIndex("id"));
    ui->tview->setColumnWidth(model->fieldIndex("name"), 250);
    ui->tview->setColumnWidth(model->fieldIndex("regular"), 50);

    model->setHeaderData(model->fieldIndex("name"), Qt::Horizontal, tr("Name"));
    model->setHeaderData(model->fieldIndex("regular"), Qt::Horizontal, tr("Regular?"));

    ui->tview->hideColumn(model->fieldIndex("phone"));
    ui->tview->hideColumn(model->fieldIndex("address"));
    ui->tview->hideColumn(model->fieldIndex("email"));
    ui->tview->hideColumn(model->fieldIndex("bankdata"));

    ui->tview->verticalHeader()->setDefaultSectionSize(24);
    ui->tview->verticalHeader()->hide();
    ui->tview->horizontalHeader()->show();
    ui->tview->setEditTriggers(QAbstractItemView::NoEditTriggers);

    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->setItemDelegate(new QSqlRelationalDelegate(this));
    mapper->addMapping(ui->eName, model->fieldIndex("name"));
    mapper->addMapping(ui->ePhone, model->fieldIndex("phone"));
    mapper->addMapping(ui->eAddress, model->fieldIndex("address"));
    mapper->addMapping(ui->eEmail, model->fieldIndex("email"));
    mapper->addMapping(ui->eBankData, model->fieldIndex("bankdata"));
    mapper->addMapping(ui->eRegular, model->fieldIndex("regular"));

    connect(ui->tview->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            mapper, SLOT(setCurrentModelIndex(QModelIndex)));

    model->select();
}

void CatCustomers::on_bAdd_clicked()
{
//    int rc;
//    rc = model->rowCount();
//    model->insertRows(rc, 1);
//    ui->tview->selectRow(rc);

    int rc;
    rc = model->rowCount();
    model->insertRows(rc, 1);
    ui->tview->selectRow(rc);
    ui->eName->clear();
    ui->ePhone->clear();
    ui->eEmail->clear();
    ui->eAddress->clear();
    ui->eBankData->clear();
    ui->eRegular->setChecked(false);
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

void CatCustomers::on_bClear_clicked()
{
    ui->eSearchName->clear();
    model->setFilter(QString());
    model->select();
}

void CatCustomers::on_eSearchName_returnPressed()
{
    if(ui->eSearchName->text() != "")
    {
        model->setFilter("customers.name LIKE '%" + ui->eSearchName->text() + "%'");
        qDebug() << "filter:" << model->filter();
    }
    else model->setFilter(QString());
}
