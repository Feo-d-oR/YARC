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
    model = new QSqlRelationalTableModel(ui->tview);
    model->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("suppliers");
    ui->tview->setModel(model);

    ui->tview->hideColumn(model->fieldIndex("id"));
    ui->tview->hideColumn(model->fieldIndex("phone"));
    ui->tview->hideColumn(model->fieldIndex("address"));
    ui->tview->hideColumn(model->fieldIndex("whours"));
    ui->tview->hideColumn(model->fieldIndex("email"));
    ui->tview->hideColumn(model->fieldIndex("website"));
    ui->tview->hideColumn(model->fieldIndex("org"));
    ui->tview->hideColumn(model->fieldIndex("bank"));
    ui->tview->hideColumn(model->fieldIndex("comment"));
    ui->tview->setColumnWidth(model->fieldIndex("name"), 150);
    ui->tview->setColumnWidth(model->fieldIndex("goods"), 300);

    model->setHeaderData(model->fieldIndex("name"), Qt::Horizontal, tr("Name"));
    model->setHeaderData(model->fieldIndex("goods"), Qt::Horizontal, tr("Goods"));

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
    mapper->addMapping(ui->eHours, model->fieldIndex("whours"));
    mapper->addMapping(ui->eEmail, model->fieldIndex("email"));
    mapper->addMapping(ui->eWebsite, model->fieldIndex("website"));
    mapper->addMapping(ui->eOrg, model->fieldIndex("org"));
    mapper->addMapping(ui->eBank, model->fieldIndex("bank"));
    mapper->addMapping(ui->eGoods, model->fieldIndex("goods"));
    mapper->addMapping(ui->eComment, model->fieldIndex("comment"));

    connect(ui->tview->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            mapper, SLOT(setCurrentModelIndex(QModelIndex)));

    model->select();
}

void CatSuppliers::on_bAdd_clicked()
{
    int rc;
    rc = model->rowCount();
    model->insertRows(rc, 1);
    ui->tview->selectRow(rc);
    ui->eName->clear();
    ui->ePhone->clear();
    ui->eHours->clear();
    ui->eEmail->clear();
    ui->eWebsite->clear();
    ui->eAddress->clear();
    ui->eOrg->clear();
    ui->eBank->clear();
    ui->eGoods->clear();
    ui->eComment->clear();
}

void CatSuppliers::on_bSave_clicked(){
    model->submitAll();
}

void CatSuppliers::on_bClose_clicked(){
    model->revertAll();
    close();
}

void CatSuppliers::on_bDelete_clicked(){
    QItemSelectionModel *sm = ui->tview->selectionModel();
    if (sm->hasSelection()){
        model->removeRow(sm->selectedRows().first().row());
        model->submitAll();
        model->select();
    }
}

void CatSuppliers::search()
{
    if (ui->cbSearchType->currentText() == tr("Name"))
            model->setFilter("suppliers.name LIKE '%" + ui->lSearch->text() + "%'");
    else if (ui->cbSearchType->currentText() == tr("Goods"))
            model->setFilter("suppliers.goods LIKE '%" + ui->lSearch->text() + "%'");
    else return;
}

void CatSuppliers::on_lSearch_returnPressed(){
    search();}

void CatSuppliers::on_bSearch_clicked(){
    search();}

void CatSuppliers::on_bClear_clicked()
{
    ui->lSearch->clear();
    model->setFilter(QString());
    model->select();
}
