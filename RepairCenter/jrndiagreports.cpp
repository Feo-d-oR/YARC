#include "jrndiagreports.h"
#include "ui_jrndiagreports.h"
#include "editdiagreport.h"
#include "mainwindow.h"

JrnDiagReports::JrnDiagReports(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JrnDiagReports)
{
    ui->setupUi(this);
    initModels();
    if(MainWindow::role == 2 && !MainWindow::acceptorCanEditDiag){
        ui->bEdit->setDisabled(1);
        ui->bAdd->setDisabled(1);
        ui->bDelete->setDisabled(1);}
}

JrnDiagReports::~JrnDiagReports()
{
    delete ui;
}

void JrnDiagReports::initModels()
{
    model = new QSqlRelationalTableModel(ui->tview);
    model->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("diag_reports");
    model->setSort(model->fieldIndex("id"),Qt::DescendingOrder);
    master_idx = model->fieldIndex("master");
    model->setRelation(master_idx, QSqlRelation("employees", "id", "name"));
    ui->tview->setModel(model);

    ui->tview->hideColumn(model->fieldIndex("id"));
    ui->tview->hideColumn(model->fieldIndex("inspect"));
    ui->tview->hideColumn(model->fieldIndex("defects"));
    ui->tview->hideColumn(model->fieldIndex("recomm"));

    ui->tview->setColumnWidth(model->fieldIndex("date"), 130);
    ui->tview->setColumnWidth(model->fieldIndex("orderid"), 70);
    ui->tview->setColumnWidth(model->fieldIndex("master"), 120);

    model->setHeaderData(model->fieldIndex("date"), Qt::Horizontal, tr("Date"));
    model->setHeaderData(model->fieldIndex("orderid"), Qt::Horizontal, tr("Order #"));
    model->setHeaderData(model->fieldIndex("master"), Qt::Horizontal, tr("Master"));

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

void JrnDiagReports::on_cSearchEmployee_currentIndexChanged(int index)
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

void JrnDiagReports::on_eSearchNumber_textEdited(const QString &arg1)
{
//    model->setFilter(QString());
    if(arg1 != "")
    {
        model->setFilter("orderid = '" + arg1 + "'");
    }
    else model->setFilter(QString());

}

void JrnDiagReports::on_bClear_clicked()
{
    ui->eSearchNumber->clear();
    model->setFilter(QString());
    model->setFilter("orderid >= " + MainWindow::showlimit);
    model->select();
    model_e->select();
}

void JrnDiagReports::on_tview_clicked(const QModelIndex &index)
{
    int row = index.row();
    const QAbstractItemModel * mdl = index.model();
    iddr = mdl->data(mdl->index(row, 0), Qt::DisplayRole).toString();
    qDebug()<<iddr;
}

void JrnDiagReports::on_dialog_closed()
{
    model->select();
}


void JrnDiagReports::showEditDiagReport()
{
    EditDiagReport *drep = new EditDiagReport();
    drep->show();
    connect(this, SIGNAL(sendMode(QString, QString)), drep, SLOT(getMode(QString, QString)));
    connect(drep,SIGNAL(reportSubmited()), this, SLOT(on_dialog_closed()));
}

void JrnDiagReports::on_bAdd_clicked()
{
    showEditDiagReport();
    emit sendMode("new", "0");
}

void JrnDiagReports::on_bView_clicked()
{
    showEditDiagReport();
    emit sendMode("view", iddr);
}

void JrnDiagReports::on_bEdit_clicked()
{
    showEditDiagReport();
    emit sendMode("edit", iddr);
}

void JrnDiagReports::on_bClose_clicked()
{
    model->revertAll();
    close();
}

void JrnDiagReports::on_bDelete_clicked()
{
    QItemSelectionModel *sm = ui->tview->selectionModel();
    if (sm->hasSelection()){
        model->removeRow(sm->selectedRows().first().row());
        model->submitAll();
        model->select();
    }
}
