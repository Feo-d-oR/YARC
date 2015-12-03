#include "catspares.h"
#include "ui_catspares.h"

CatSpares::CatSpares(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CatSpares)
{
    ui->setupUi(this);
    initModels();
}

CatSpares::~CatSpares()
{
    delete ui;
}

void CatSpares::initModels()
{
    model = new QSqlRelationalTableModel(ui->tview);
    model->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("spares");

    type_idx = model->fieldIndex("type");
    model->setRelation(type_idx, QSqlRelation("spare_types", "id", "name"));
    supp_idx = model->fieldIndex("supplier");
    model->setRelation(supp_idx, QSqlRelation("suppliers", "id", "name"));

    ui->tview->setModel(model);

    ui->tview->hideColumn(model->fieldIndex("id"));
    ui->tview->hideColumn(model->fieldIndex("type"));
    ui->tview->hideColumn(model->fieldIndex("supplier"));
    ui->tview->hideColumn(model->fieldIndex("buyingprice"));
    ui->tview->hideColumn(model->fieldIndex("partnum"));

    ui->tview->setColumnWidth(model->fieldIndex("name"), 350);
    ui->tview->setColumnWidth(model->fieldIndex("price"), 70);
    ui->tview->setColumnWidth(model->fieldIndex("quantity"), 50);

    model->setHeaderData(model->fieldIndex("name"), Qt::Horizontal, tr("Name"));
    model->setHeaderData(model->fieldIndex("price"), Qt::Horizontal, tr("Price"));
    model->setHeaderData(model->fieldIndex("quantity"), Qt::Horizontal, tr("Qty"));

    ui->tview->verticalHeader()->setDefaultSectionSize(24);
    ui->tview->verticalHeader()->hide();
    ui->tview->horizontalHeader()->show();
    ui->tview->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->eType->setModel(model->relationModel(type_idx));
    ui->eType->setModelColumn(model->relationModel(type_idx)->fieldIndex("name"));
    ui->cSupplier->setModel(model->relationModel(supp_idx));
    ui->cSupplier->setModelColumn(model->relationModel(supp_idx)->fieldIndex("name"));

    model_t = new QSqlTableModel();
    model_t->setTable("spare_types");
    model_t->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->cSearchType->setModel(model_t);
    ui->cSearchType->setModelColumn(model_t->fieldIndex("name"));
    model_t->select();

    model_s = new QSqlTableModel();
    model_s->setTable("suppliers");
    model_s->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->cSearchSupplier->setModel(model_s);
    ui->cSearchSupplier->setModelColumn(model_s->fieldIndex("name"));
    model_s->select();

    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->setItemDelegate(new QSqlRelationalDelegate(this));
    mapper->addMapping(ui->eName, model->fieldIndex("name"));
    mapper->addMapping(ui->ePrice, model->fieldIndex("price"));
    mapper->addMapping(ui->eBuyPrice, model->fieldIndex("buyingprice"));
    mapper->addMapping(ui->eQty, model->fieldIndex("quantity"));
    mapper->addMapping(ui->eType, type_idx);
    mapper->addMapping(ui->cSupplier, supp_idx);

    connect(ui->tview->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            mapper, SLOT(setCurrentModelIndex(QModelIndex)));

    model->select();
}

void CatSpares::on_cSearchType_activated(int index)
{
    if (index != -1)
    {
        rec_t = model_t->record(index);
        id_t = rec_t.value(rec_t.indexOf("id")).toString();
        model->setFilter("type = '" + id_t + "'");
    }
}


void CatSpares::on_bAdd_clicked()
{
    int rc;
    rc = model->rowCount();
    model->insertRows(rc, 1);
    ui->tview->selectRow(rc);
    ui->eBuyPrice->clear();
    ui->ePrice->clear();
    ui->eQty->clear();
    ui->eType->setCurrentIndex(-1);
    ui->cSupplier->setCurrentIndex(-1);
}

void CatSpares::on_bSave_clicked(){
    model->submitAll();
}

void CatSpares::on_bClose_clicked()
{
    model->revertAll();
    close();
}

void CatSpares::on_bDelete_clicked()
{
    QItemSelectionModel *sm = ui->tview->selectionModel();
    if (sm->hasSelection()){
        model->removeRow(sm->selectedRows().first().row());
        model->submitAll();
        model->select();
    }
}

void CatSpares::on_bClear_clicked()
{
    ui->eSearchName->clear();
    ui->cSearchSupplier->setCurrentIndex(-1);
    ui->cSearchType->setCurrentIndex(-1);
    model->setFilter(QString());
    model->select();
    model_t->select();
}

void CatSpares::on_cSearchSupplier_activated(int index)
{
    if (index != -1)
    {
        rec_s = model_s->record(index);
        id_s = rec_s.value(rec_s.indexOf("id")).toString();
        model->setFilter("supplier = '" + id_s + "'");
    }
}

void CatSpares::on_eSearchName_returnPressed()
{
    if(ui->eSearchName->text() != "")
    {
        model->setFilter("spares.name LIKE '%" + ui->eSearchName->text() + "%'");
        qDebug() << "filter:" << model->filter();
    }
    else model->setFilter(QString());
}
