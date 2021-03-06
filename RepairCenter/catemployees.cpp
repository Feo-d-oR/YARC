#include "catemployees.h"
#include "ui_catemployees.h"

CatEmployees::CatEmployees(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CatEmployees)
{
    ui->setupUi(this);
    initModel();
}

CatEmployees::~CatEmployees()
{
    delete ui;
}

void CatEmployees::initModel()
{
    model = new QSqlRelationalTableModel(ui->tview);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    model->setTable("employees");
    pt_idx = model->fieldIndex("position_type");
    model->setRelation(pt_idx, QSqlRelation("position_types", "id", "name"));
    ui->tview->setModel(model);

    ui->tview->hideColumn(model->fieldIndex("id"));
    ui->tview->hideColumn(model->fieldIndex("fullname"));
    ui->tview->hideColumn(model->fieldIndex("phone"));
    ui->tview->hideColumn(model->fieldIndex("address"));
    ui->tview->hideColumn(model->fieldIndex("isactive"));
    ui->tview->hideColumn(model->fieldIndex("username"));
    ui->tview->hideColumn(model->fieldIndex("password"));

    ui->tview->setColumnWidth(model->fieldIndex("name"), 150);
    ui->tview->setColumnWidth(model->fieldIndex("position"), 150);
    ui->tview->setColumnWidth(pt_idx, 120);

    model->setHeaderData(model->fieldIndex("name"), Qt::Horizontal, tr("Name"));
    model->setHeaderData(model->fieldIndex("position"), Qt::Horizontal, tr("Position"));
    model->setHeaderData(pt_idx, Qt::Horizontal, tr("Role"));

    ui->tview->verticalHeader()->setDefaultSectionSize(24);
    ui->tview->verticalHeader()->hide();
    ui->tview->horizontalHeader()->show();
    ui->tview->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->ePositionType->setModel(model->relationModel(pt_idx));
    ui->ePositionType->setModelColumn(model->relationModel(pt_idx)->fieldIndex("name"));

    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->setItemDelegate(new QSqlRelationalDelegate(this));
    mapper->addMapping(ui->eName, model->fieldIndex("name"));
    mapper->addMapping(ui->eFullName, model->fieldIndex("fullname"));
    mapper->addMapping(ui->ePhone, model->fieldIndex("phone"));
    mapper->addMapping(ui->eAddress, model->fieldIndex("address"));
    mapper->addMapping(ui->ePositionType, pt_idx);
    mapper->addMapping(ui->ePosition, model->fieldIndex("position"));
    mapper->addMapping(ui->eisActive, model->fieldIndex("isactive"));
    mapper->addMapping(ui->eUsername, model->fieldIndex("username"));
    mapper->addMapping(ui->ePassword, model->fieldIndex("password"));

    connect(ui->tview->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            mapper, SLOT(setCurrentModelIndex(QModelIndex)));

    model->select();
}

void CatEmployees::on_bAdd_clicked()
{
    int rc;
    rc = model->rowCount();
    model->insertRows(rc, 1);
    ui->tview->selectRow(rc);
    ui->ePositionType->setCurrentIndex(-1);
    ui->eisActive->setChecked(0);
}

void CatEmployees::on_bSave_clicked()
{
    model->submitAll();
}

void CatEmployees::on_bClose_clicked()
{
    model->revertAll();
    close();
}

void CatEmployees::on_bDelete_clicked()
{
    QItemSelectionModel *sm = ui->tview->selectionModel();
    if (sm->hasSelection()){
        model->removeRow(sm->selectedRows().first().row());
        model->submitAll();
        model->select();
    }
}

