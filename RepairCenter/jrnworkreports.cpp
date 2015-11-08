#include "jrnworkreports.h"
#include "ui_jrnworkreports.h"
#include "editworkreport.h"
#include "mainwindow.h"

JrnWorkReports::JrnWorkReports(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JrnWorkReports)
{
    ui->setupUi(this);
    initModels();
    if(MainWindow::role == 2 && !MainWindow::acceptorCanEditWorks){
        ui->bEdit->setDisabled(1);
        ui->bAdd->setDisabled(1);
        ui->bDelete->setDisabled(1);}
}

JrnWorkReports::~JrnWorkReports()
{
    delete ui;
}

void JrnWorkReports::initModels()
{
    model = new QSqlRelationalTableModel(ui->tview);
    model->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("work_reports");
    model->setSort(model->fieldIndex("id"),Qt::DescendingOrder);
    master_idx = model->fieldIndex("master");
    work_idx = model->fieldIndex("work");
    model->setRelation(master_idx, QSqlRelation("employees", "id", "name"));
    model->setRelation(work_idx, QSqlRelation("works", "id", "name"));
    ui->tview->setModel(model);

    ui->tview->hideColumn(model->fieldIndex("id"));
    ui->tview->hideColumn(model->fieldIndex("spares"));
    ui->tview->hideColumn(model->fieldIndex("quant"));
    ui->tview->hideColumn(model->fieldIndex("quants"));

    ui->tview->setColumnWidth(model->fieldIndex("date"), 130);
    ui->tview->setColumnWidth(model->fieldIndex("orderid"), 70);
    ui->tview->setColumnWidth(model->fieldIndex("master"), 120);
    ui->tview->setColumnWidth(model->fieldIndex("work"), 350);

    model->setHeaderData(model->fieldIndex("date"), Qt::Horizontal, tr("Date"));
    model->setHeaderData(model->fieldIndex("orderid"), Qt::Horizontal, tr("Order #"));
    model->setHeaderData(model->fieldIndex("master"), Qt::Horizontal, tr("Master"));
    model->setHeaderData(model->fieldIndex("work"), Qt::Horizontal, tr("Work"));

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

void JrnWorkReports::on_cSearchEmployee_currentIndexChanged(int index)
{
    if (index != -1)
    {
//        model->setFilter(QString());
        rec_e = model_e->record(index);
        id_m = rec_e.value(rec_e.indexOf("id")).toString();
        if (MainWindow::limitallfilters)
            model->setFilter("master = '" + id_m + "' AND orderid >= " + MainWindow::showlimit);
        else
            model->setFilter("master = '" + id_m + "'");
    }
}

void JrnWorkReports::on_eSearchNumber_textEdited(const QString &arg1)
{
//    model->setFilter(QString());
    if(arg1 != "")
    {
        model->setFilter("orderid = '" + arg1 + "'");
    }
    else model->setFilter(QString());

}

void JrnWorkReports::on_bClear_clicked()
{
    ui->eSearchNumber->clear();
    model->setFilter(QString());
    model->setFilter("orderid >= " + MainWindow::showlimit);
    model->select();
    model_e->select();
}

void JrnWorkReports::on_tview_clicked(const QModelIndex &index)
{
    int row = index.row();
    const QAbstractItemModel * mdl = index.model();
    idwr = mdl->data(mdl->index(row, 0), Qt::DisplayRole).toString();
}

void JrnWorkReports::on_dialog_closed()
{
    model->select();
}


void JrnWorkReports::showEditWorkReport()
{
    EditWorkReport *wrep = new EditWorkReport();
    wrep->show();
    connect(this, SIGNAL(sendMode(QString, QString)), wrep, SLOT(getMode(QString, QString)));
    connect(wrep,SIGNAL(reportSubmited()), this, SLOT(on_dialog_closed()));
}

void JrnWorkReports::on_bAdd_clicked()
{
    showEditWorkReport();
    emit sendMode("new", "0");
}

void JrnWorkReports::on_bView_clicked()
{
    showEditWorkReport();
    emit sendMode("view", idwr);
}

void JrnWorkReports::on_bEdit_clicked()
{
    showEditWorkReport();
    emit sendMode("edit", idwr);
}

void JrnWorkReports::on_bClose_clicked()
{
    model->revertAll();
    close();
}

void JrnWorkReports::on_bDelete_clicked()
{
    QItemSelectionModel *sm = ui->tview->selectionModel();
    if (sm->hasSelection()){
        model->removeRow(sm->selectedRows().first().row());
        model->submitAll();
        model->select();
    }
}

