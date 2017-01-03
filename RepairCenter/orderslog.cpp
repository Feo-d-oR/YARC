#include "orderslog.h"
#include "ui_orderslog.h"
#include "mainwindow.h"

OrdersLog::OrdersLog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OrdersLog)
{
    ui->setupUi(this);

    ui->eDateStart->setDate(QDate::currentDate());
    ui->eDateEnd->setDate(QDate::currentDate());
    initModels();
}

OrdersLog::~OrdersLog()
{
    delete ui;
}

void OrdersLog::on_bClose_clicked()
{
    model->revertAll();
    close();
}

void OrdersLog::initModels()
{
    model = new QSqlRelationalTableModel(ui->tview);
    model->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("orders_log");
    model->setSort(model->fieldIndex("id"),Qt::DescendingOrder);

    employee_idx = model->fieldIndex("employee");
    state_idx = model->fieldIndex("state");

    model->setRelation(state_idx, QSqlRelation("states", "id", "name"));
    model->setRelation(employee_idx, QSqlRelation("employees", "id", "name"));

    ui->tview->setModel(model);

    ui->tview->hideColumn(model->fieldIndex("id"));

    ui->tview->setColumnWidth(model->fieldIndex("date"), 100);
    ui->tview->setColumnWidth(model->fieldIndex("orderid"), 70);
    ui->tview->setColumnWidth(model->fieldIndex("operation"), 200);
    ui->tview->setColumnWidth(model->fieldIndex("state"), 130);
    ui->tview->setColumnWidth(model->fieldIndex("employee"), 130);
    ui->tview->setColumnWidth(model->fieldIndex("comment"), 300);

    model->setHeaderData(model->fieldIndex("date"), Qt::Horizontal, tr("Date&Time"));
    model->setHeaderData(model->fieldIndex("orderid"), Qt::Horizontal, tr("Order #"));
    model->setHeaderData(model->fieldIndex("Operation"), Qt::Horizontal, tr("Operation"));
    model->setHeaderData(model->fieldIndex("state"), Qt::Horizontal, tr("State"));
    model->setHeaderData(model->fieldIndex("employee"), Qt::Horizontal, tr("Employee"));
    model->setHeaderData(model->fieldIndex("comment"), Qt::Horizontal, tr("Comment"));

    ui->tview->verticalHeader()->setDefaultSectionSize(24);
    ui->tview->verticalHeader()->hide();
    ui->tview->horizontalHeader()->show();
    ui->tview->setEditTriggers(QAbstractItemView::NoEditTriggers);

    model->setFilter("orderid >= " + MainWindow::showlimit);
    model->select();

    model_e = new QSqlQueryModel();
    model_e->setQuery("SELECT id, name FROM employees");
    ui->eEmployee->setModel(model_e);
    ui->eEmployee->setModelColumn(1);
    ui->eEmployee->model()->sort(1, Qt::AscendingOrder);
    ui->eEmployee->setCurrentIndex(-1);
}

void OrdersLog::on_eEmployee_activated(int index)
{
    if (index != -1)
    {
//        model->setFilter(QString());
        rec_e = model_e->record(index);
        id_e = rec_e.value(rec_e.indexOf("id")).toString();
        if (MainWindow::limitallfilters)
            model->setFilter("employee = '" + id_e + "' AND orderid >= " + MainWindow::showlimit);
        else
            model->setFilter("employee = '" + id_e + "'");    }
}

void OrdersLog::on_eOrderID_returnPressed()
{
//    model->setFilter(QString());
    if(ui->eOrderID->text() != "")
        model->setFilter("orderid = " + ui->eOrderID->text());
    else return;
}

void OrdersLog::on_bClear_clicked()
{
    ui->eOrderID->clear();
    model->setFilter(QString());
    model->setFilter("orderid >= " + MainWindow::showlimit);
    model->select();
}

void OrdersLog::on_bSearchByDate_clicked()
{
    model->setFilter("CAST(date as DATE) BETWEEN '" + ui->eDateStart->date().toString("yyyy-MM-dd") + "' AND '" + ui->eDateEnd->date().toString("yyyy-MM-dd") + "'");
    model->select();
}
