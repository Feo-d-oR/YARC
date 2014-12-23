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
    ui->tview->setModel(model);

    ui->tview->hideColumn(model->fieldIndex("id"));
    ui->tview->hideColumn(model->fieldIndex("type"));

    ui->tview->setColumnWidth(model->fieldIndex("name"), 350);
    ui->tview->setColumnWidth(model->fieldIndex("price"), 70);

    model->setHeaderData(model->fieldIndex("name"), Qt::Horizontal, "Наименование");
    model->setHeaderData(model->fieldIndex("price"), Qt::Horizontal, "Цена");

    ui->tview->verticalHeader()->setDefaultSectionSize(24);
    ui->tview->verticalHeader()->hide();
    ui->tview->horizontalHeader()->show();

    ui->eType->setModel(model->relationModel(type_idx));
    ui->eType->setModelColumn(model->relationModel(type_idx)->fieldIndex("name"));

    model_t = new QSqlTableModel();
    model_t->setTable("spare_types");
    model_t->setEditStrategy(QSqlTableModel::OnManualSubmit);

    ui->cSearchType->setModel(model_t);
    ui->cSearchType->setModelColumn(model_t->fieldIndex("name"));
    model_t->select();

    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->setItemDelegate(new QSqlRelationalDelegate(this));
    mapper->addMapping(ui->eName, model->fieldIndex("name"));
    mapper->addMapping(ui->ePrice, model->fieldIndex("price"));
    mapper->addMapping(ui->eType, type_idx);

    connect(ui->tview->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            mapper, SLOT(setCurrentModelIndex(QModelIndex)));

    model->select();
}

void CatSpares::on_cSearchType_currentIndexChanged(int index)
{
    if (index != -1)
    {
//        model->setFilter(QString());
        rec_t = model_t->record(index);
        id_t = rec_t.value(rec_t.indexOf("id")).toString();
        model->setFilter("type = '" + id_t + "'");
    }
}

void CatSpares::on_eSearchName_textEdited(const QString &arg1)
{
//    model->setFilter(QString());
    if(arg1 != "")
    {
        model->setFilter("spares.name LIKE '%" + arg1 + "%'");
        qDebug() << "filter:" << model->filter();
    }
    else model->setFilter(QString());

}

void CatSpares::on_bAdd_clicked()
{
    model->insertRows(model->rowCount(), 1);
    ui->tview->setCurrentIndex(model->index(model->rowCount()-1, 1));
    qDebug() << "rc:" << model->rowCount();
}

void CatSpares::on_bSave_clicked()
{
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
    model->setFilter(QString());
    model->select();
    model_t->select();
}
