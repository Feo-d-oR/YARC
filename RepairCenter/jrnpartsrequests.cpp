#include "jrnpartsrequests.h"
#include "ui_jrnpartsrequests.h"
#include "mainwindow.h"
#include "editpartsrequest.h"

JrnPartsRequests::JrnPartsRequests(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JrnPartsRequests)
{
    ui->setupUi(this);
    initModels();

    if(MainWindow::role == 2 && !MainWindow::acceptorCanEditSpares){
        ui->bEdit->setDisabled(1);
        ui->bAdd->setDisabled(1);
        ui->bDelete->setDisabled(1);}
    if(MainWindow::role == 1 && !MainWindow::masterCanEditSpares){
        ui->bEdit->setDisabled(1);
        ui->bAdd->setDisabled(1);
        ui->bDelete->setDisabled(1);}
}

JrnPartsRequests::~JrnPartsRequests()
{
    delete ui;
}

void JrnPartsRequests::initModels()
{
    model = new QSqlRelationalTableModel(ui->tview);
    model->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("part_requests");
    model->setSort(model->fieldIndex("id"),Qt::DescendingOrder);
    master_idx = model->fieldIndex("master");
    state_idx = model->fieldIndex("work");
    model->setRelation(master_idx, QSqlRelation("employees", "id", "name"));
    model->setRelation(state_idx, QSqlRelation("pr_states", "id", "name"));
    ui->tview->setModel(model);

    ui->tview->hideColumn(model->fieldIndex("spares"));
    ui->tview->hideColumn(model->fieldIndex("sparesnew"));
    ui->tview->hideColumn(model->fieldIndex("quants"));
    ui->tview->hideColumn(model->fieldIndex("comment"));

    ui->tview->setColumnWidth(model->fieldIndex("id"), 70);
    ui->tview->setColumnWidth(model->fieldIndex("date"), 130);
    ui->tview->setColumnWidth(model->fieldIndex("orderid"), 70);
    ui->tview->setColumnWidth(model->fieldIndex("master"), 130);
    ui->tview->setColumnWidth(model->fieldIndex("state"), 120);

    model->setHeaderData(model->fieldIndex("date"), Qt::Horizontal, tr("Date"));
    model->setHeaderData(model->fieldIndex("orderid"), Qt::Horizontal, tr("Order #"));
    model->setHeaderData(model->fieldIndex("master"), Qt::Horizontal, tr("Master"));
    model->setHeaderData(model->fieldIndex("state"), Qt::Horizontal, tr("State"));

    ui->tview->verticalHeader()->setDefaultSectionSize(24);
    ui->tview->verticalHeader()->hide();
    ui->tview->horizontalHeader()->show();
    ui->tview->setEditTriggers(QAbstractItemView::NoEditTriggers);

    model_e = new QSqlTableModel();
    model_e->setTable("employees");
    model_e->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->cSearchEmployee->setModel(model_e);
    ui->cSearchEmployee->setModelColumn(model_e->fieldIndex("name"));
    model_e->select();

    model->setFilter("orderid >= " + MainWindow::showlimit);
    model->select();
}

void JrnPartsRequests::on_cSearchEmployee_currentIndexChanged(int index)
{
    if (index != -1)
    {
//        model->setFilter(QString());
        rec_e = model_e->record(index);
        id_m = rec_e.value(rec_e.indexOf("id")).toString();
        if (MainWindow::limitallfilters)
            model->setFilter("master = '" + id_m + "' AND orderid >= " + MainWindow::showlimit);
        else
            model->setFilter("master = '" + id_m + "'");    }
}

void JrnPartsRequests::on_eSearchNumber_textEdited(const QString &arg1)
{
//    model->setFilter(QString());
    if(arg1 != "")
    {
        model->setFilter("orderid = '" + arg1 + "'");
    }
    else model->setFilter(QString());

}

void JrnPartsRequests::on_bClear_clicked()
{
    ui->eSearchNumber->clear();
    model->setFilter(QString());
    model->setFilter("orderid >= " + MainWindow::showlimit);
    model->select();
    model_e->select();
}

void JrnPartsRequests::on_tview_clicked(const QModelIndex &index)
{
    int row = index.row();
    const QAbstractItemModel * mdl = index.model();
    idpr = mdl->data(mdl->index(row, 0), Qt::DisplayRole).toString();
}

void JrnPartsRequests::on_dialog_closed()
{
    model->select();
}


void JrnPartsRequests::showEditPartRequest()
{
    EditPartsRequest *wrep = new EditPartsRequest();
    wrep->show();
    connect(this, SIGNAL(sendMode(QString, QString)), wrep, SLOT(getMode(QString, QString)));
    connect(wrep,SIGNAL(requestSubmited()), this, SLOT(on_dialog_closed()));
}

void JrnPartsRequests::on_bAdd_clicked()
{
    showEditPartRequest();
    emit sendMode("new", "0");
}

void JrnPartsRequests::on_bView_clicked()
{
    showEditPartRequest();
    emit sendMode("view", idpr);
}

void JrnPartsRequests::on_bEdit_clicked()
{
    showEditPartRequest();
    emit sendMode("edit", idpr);
}

void JrnPartsRequests::on_bClose_clicked()
{
    model->revertAll();
    close();
}

void JrnPartsRequests::on_bDelete_clicked()
{
    QItemSelectionModel *sm = ui->tview->selectionModel();
    if (sm->hasSelection()){
        model->removeRow(sm->selectedRows().first().row());
        model->submitAll();
        model->select();
    }
}

