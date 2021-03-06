#include "editworkreport.h"
#include "ui_editworkreport.h"
#include "mainwindow.h"

EditWorkReport::EditWorkReport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditWorkReport)
{
    EditWorkReport::activateWindow();
    ui->setupUi(this);
    isnew = true;
    if(MainWindow::role == 1 && !MainWindow::masterCanEditWorks)
        ui->bAddWork->setDisabled(1);
    if(MainWindow::role == 1 && !MainWindow::masterCanEditSpares)
        ui->bAddSpare->setDisabled(1);
    if(MainWindow::role == 2 && !MainWindow::acceptorCanEditWorks)
        ui->bAddWork->setDisabled(1);
    if(MainWindow::role == 2 && !MainWindow::acceptorCanEditSpares)
        ui->bAddSpare->setDisabled(1);
}

EditWorkReport::~EditWorkReport()
{
    delete ui;
}

void EditWorkReport::closeEvent(QCloseEvent *event)
{
    if (saved == false)
    {
        QMessageBox mb;
        mb.setWindowTitle(tr("Work report"));
        mb.setText(tr("Save changes?"));
        QPushButton *bSave = mb.addButton(tr("Yes"), QMessageBox::ActionRole);
        QPushButton *bDiscard = mb.addButton(tr("No"), QMessageBox::ActionRole);
        QPushButton *bCancel = mb.addButton(tr("Cancel"), QMessageBox::ActionRole);
        mb.setDefaultButton(bCancel);
        mb.exec();

        if (mb.clickedButton() == bSave){
            submitReport();
            saved = true;
            event->accept();
        }
        if (mb.clickedButton() == bDiscard){
            event->accept();
        }
        if (mb.clickedButton() == bCancel){
            event->ignore();
        }

    }
    else if (saved == true)
        event->accept();
}

void EditWorkReport::getMode(QString mode, QString num)
{
    if (mode == "new")
    {
        QWidget::setWindowTitle(tr("New work report"));
        ui->eOrderID->setText(num);
        ui->eDate->setDateTime(QDateTime::currentDateTime());
        setModels();
        isnew = true;
    }
    else if (mode == "view")
    {
        saved = true;
        QWidget::setWindowTitle(tr("View work report"));
        ui->bSave->setDisabled(true);
        setModels();
        reportID = num;
        fillFields();
        ui->bSave->setEnabled(false);
        isnew = false;
    }
    else if (mode == "edit")
    {
        saved = true;
        QWidget::setWindowTitle(tr("Edit work report"));
        setModels();
        reportID = num;
        fillFields();
        isnew = false;
    }
}

void EditWorkReport::setModels()
{
    model_m = new QSqlQueryModel();
    model_m->setQuery("SELECT id, name FROM employees WHERE position_type = '1' AND isactive = '1'");
    ui->eMaster->setModel(model_m);
    ui->eMaster->setModelColumn(1);
    ui->eMaster->model()->sort(1, Qt::AscendingOrder);

    QModelIndexList idx_m = ui->eMaster->model()->match(ui->eMaster->model()->index(0, 0), Qt::EditRole, MainWindow::defMaster, 1, Qt::MatchExactly);
    ui->eMaster->setCurrentIndex(idx_m.value(0).row());

    model_w = new QSqlTableModel();
    model_w->setTable("works");
    model_w->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->eWork->setModel(model_w);
    ui->eWork->setModelColumn(model_w->fieldIndex("name"));
    model_w->select();
    ui->eWork->setCurrentIndex(-1);

    model_s = new QSqlTableModel();
    model_s->setTable("spares");
    model_s->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->eSpare->setModel(model_s);
    ui->eSpare->setModelColumn(model_s->fieldIndex("name"));
    model_s->select();
    ui->eSpare->setCurrentIndex(-1);

    ui->tview->setColumnWidth(0, 300);
    ui->tview->setColumnWidth(1, 100);
    ui->tview->setColumnWidth(2, 100);
    ui->tview->hideColumn(3);
}

void EditWorkReport::fillFields()
{
    qf.exec("SELECT * FROM work_reports WHERE id = " + reportID);
    recf = qf.record();
    qf.first();

    ui->eOrderID->setText(qf.value(recf.indexOf("orderid")).toString());
    ui->eDate->setDateTime(qf.value(recf.indexOf("date")).toDateTime());

    QModelIndexList idx_m = ui->eMaster->model()->match(ui->eMaster->model()->index(0, 0), Qt::EditRole, qf.value(recf.indexOf("master")), 1, Qt::MatchExactly);
    ui->eMaster->setCurrentIndex(idx_m.value(0).row());

    QModelIndexList idx_w = ui->eWork->model()->match(ui->eWork->model()->index(0, 0), Qt::EditRole, qf.value(recf.indexOf("work")), 1, Qt::MatchExactly);
    ui->eWork->setCurrentIndex(idx_w.value(0).row());

    lqt.clear();
    lsp.clear();
    lsp = qf.value(recf.indexOf("spares")).toString().split(",");
    lqt = qf.value(recf.indexOf("quants")).toString().split(",");

    for (int i=0; i<lsp.size(); i++)
    {
        ui->tview->insertRow(i);
        qfs.exec("SELECT * FROM spares WHERE id = " + lsp.at(i));
        qfs.first();
        recfs = qfs.record();
        ui->tview->setItem(i, 0, new QTableWidgetItem(qfs.value(recfs.indexOf("name")).toString()));
        ui->tview->setItem(i, 1, new QTableWidgetItem(qfs.value(recfs.indexOf("price")).toString()));
        ui->tview->setItem(i, 2, new QTableWidgetItem(lqt.at(i)));
        ui->tview->setItem(i, 3, new QTableWidgetItem(qfs.value(recfs.indexOf("id")).toString()));
    }
}

void EditWorkReport::on_eWork_currentIndexChanged(int index)
{
    if (index != -1)
    {
        QSqlRecord rec_w = model_w->record(index);
        ui->eWPrice->setText(rec_w.value(rec_w.indexOf("price")).toString());
    }
    else ui->eWPrice->clear();
}

void EditWorkReport::on_bAddWork_clicked()
{
    QSqlQuery qw;
    qw.exec("INSERT INTO works (name, price) VALUES ('" + ui->eWork->currentText() + "','" + ui->eWPrice->text() + "')");
    int lastidw = qw.lastInsertId().toInt();  //QtSql,. as of late, returns 0 lastInsertId after model->select(),so additional variable needeed
    model_w->select();
    QModelIndexList idx_w = ui->eWork->model()->match(ui->eWork->model()->index(0, 0), Qt::EditRole, lastidw, 1, Qt::MatchExactly);
    ui->eWork->setCurrentIndex(idx_w.value(0).row());
}

void EditWorkReport::submitReport()
{
    QSqlRecord rec_m = model_m->record(ui->eMaster->currentIndex());
    QString id_m = rec_m.value(rec_m.indexOf("id")).toString();

    QSqlRecord rec_w = model_w->record(ui->eWork->currentIndex());
    QString id_w = rec_w.value(rec_w.indexOf("id")).toString();

    QString spares;
    QString quants;

    lqt.clear();
    lsp.clear();

    i = ui->tview->rowCount();
    int r;
    for(r=0; r<i; r++)
    {
        lqt.append(ui->tview->item(r,2)->text());
        lsp.append(ui->tview->item(r,3)->text());
    }
    spares = lsp.join(",");
    quants = lqt.join(",");

    QSqlQuery q;
    if (isnew){
        q.prepare("INSERT INTO work_reports VALUES (NULL, NULL, :orderid, :master, :work, :quant, :spares, :quants)");
        reportID = q.lastInsertId().toString();}
    else
        q.prepare("UPDATE work_reports SET date = :date, master = :master, work = :work, quant = :quant, spares = :spares, quants = :quants WHERE id = " + reportID);
    q.bindValue(":date", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    q.bindValue(":orderid", ui->eOrderID->text());
    q.bindValue(":master", id_m);
    q.bindValue(":work", id_w);
    q.bindValue(":quant", ui->eQuant->text());
    q.bindValue(":spares", spares);
    q.bindValue(":quants", quants);
    q.exec();
    q.prepare("INSERT INTO orders_log SET date = :date, orderid = :orderid, operation = :operation, state = :state, employee = :employee");
    q.bindValue(":date", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    q.bindValue(":orderid", ui->eOrderID->text());
    q.bindValue(":employee", id_m.toInt());
    if (isnew)
        q.bindValue(":operation", tr("Work report submited"));
    else
        q.bindValue(":operation", tr("Work report edited"));
    if(ui->cbRepairComplete->isChecked())
        q.bindValue(":state", 6);
    q.exec();
    saved = true;
    if(ui->cbRepairComplete->isChecked())
        q.exec("UPDATE orders SET state = 6 WHERE number = " + ui->eOrderID->text());
}

void EditWorkReport::on_eSpare_currentIndexChanged(int index)
{
    if (index != -1)
    {
        QSqlRecord rec_s = model_s->record(index);
        id_s = rec_s.value(rec_s.indexOf("id")).toString();
        QString price = rec_s.value(rec_s.indexOf("price")).toString();
        ui->eSPrice->setText(price);
    }
    else ui->eSPrice->clear();
}

void EditWorkReport::on_bAddSpare_clicked()
{
    QSqlQuery qas;
    qas.exec("INSERT INTO spares (name, price) VALUES ('" + ui->eSpare->currentText() + "','" + ui->eSPrice->text() + "')");
    int lastids = qas.lastInsertId().toInt();  //QtSql, as of late, returns 0 lastInsertId after model->select(),so additional variable needeed
    model_s->select();
    QModelIndexList idx_w = ui->eSpare->model()->match(ui->eSpare->model()->index(0, 0), Qt::EditRole, lastids, 1, Qt::MatchExactly);
    ui->eSpare->setCurrentIndex(idx_w.value(0).row());
}

void EditWorkReport::on_bUse_clicked()
{
    int rc = ui->tview->rowCount();
    ui->tview->insertRow(rc);
    ui->tview->setItem(rc, 0, new QTableWidgetItem(ui->eSpare->currentText()));
    ui->tview->setItem(rc, 1, new QTableWidgetItem(ui->eSPrice->text()));
    ui->tview->setItem(rc, 2, new QTableWidgetItem("1"));
    ui->tview->setItem(rc, 3, new QTableWidgetItem(id_s));
}


void EditWorkReport::on_bRemove_clicked()
{
    ui->tview->removeRow(ui->tview->currentRow());
}

void EditWorkReport::on_bCancel_clicked()
{
    close();
}

void EditWorkReport::on_bSave_clicked()
{
    submitReport();
    close();
    emit reportSubmited();
}

void EditWorkReport::reject()
{
    close();
}
