#include "editpartsrequest.h"
#include "ui_editpartsrequest.h"
#include "mainwindow.h"

EditPartsRequest::EditPartsRequest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditPartsRequest)
{
    ui->setupUi(this);
    isnew = true;
}

EditPartsRequest::~EditPartsRequest()
{
    delete ui;
}

void EditPartsRequest::closeEvent(QCloseEvent *event)
{
    if (saved == false)
    {
        QMessageBox mb;
        mb.setWindowTitle(tr("Parts request"));
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

void EditPartsRequest::getMode(QString mode, QString num)
 {
     if (mode == "new")
     {
         QWidget::setWindowTitle(tr("New parts request"));
         ui->eOrderID->setText(num);
         ui->eDate->setDate(QDate::currentDate());
         setModels();
         isnew = true;
     }
     else if (mode == "view")
     {
         saved = true;
         QWidget::setWindowTitle(tr("View parts request"));
         ui->bSave->setDisabled(true);
         setModels();
         requestID = num;
         fillFields();
         ui->bSave->setEnabled(false);
         isnew = false;
     }
     else if (mode == "edit")
     {
         saved = true;
         QWidget::setWindowTitle(tr("Edit parts request"));
         setModels();
         requestID = num;
         fillFields();
         isnew = false;
     }
 }

void EditPartsRequest::setModels()
{
    model_m = new QSqlQueryModel();
    model_m->setQuery("SELECT id, name FROM employees WHERE position_type = '1' AND isactive = '1'");
    ui->eMaster->setModel(model_m);
    ui->eMaster->setModelColumn(1);
    ui->eMaster->model()->sort(1, Qt::AscendingOrder);

    QModelIndexList idx_m = ui->eMaster->model()->match(ui->eMaster->model()->index(0, 0), Qt::EditRole, MainWindow::defMaster, 1, Qt::MatchExactly);
    ui->eMaster->setCurrentIndex(idx_m.value(0).row());

    model_s = new QSqlTableModel();
    model_s->setTable("spares");
    model_s->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->eSpare->setModel(model_s);
    ui->eSpare->setModelColumn(model_s->fieldIndex("name"));
    model_s->select();
    ui->eSpare->setCurrentIndex(-1);

    model_st = new QSqlQueryModel();
    model_st->setQuery("SELECT id, name FROM pr_states");
    ui->eState->setModel(model_st);
    ui->eState->model()->sort(1, Qt::AscendingOrder);
    ui->eState->setModelColumn(1);
    if (isnew == true){
        QModelIndexList idx_s = ui->eState->model()->match(ui->eState->model()->index(0, 0), Qt::EditRole, 1, 1, Qt::MatchExactly);
        ui->eState->setCurrentIndex(idx_s.value(0).row());}

    if (MainWindow::role == 1 || MainWindow::role == 2)
        ui->eState->setEnabled(false);
    else
        ui->eState->setEnabled(true);

    ui->tview->setColumnWidth(0, 300);
    ui->tview->setColumnWidth(1, 50);
    ui->tview->setColumnWidth(2, 100);
    ui->tview->hideColumn(3);
}

void EditPartsRequest::fillFields()
{
    qf.exec("SELECT * FROM part_requests WHERE id = " + requestID);
    recf = qf.record();
    qf.first();

    ui->eOrderID->setText(qf.value(recf.indexOf("orderid")).toString());
    ui->eDate->setDate(qf.value(recf.indexOf("date")).toDate());
    ui->eSparesNew->setPlainText(qf.value(recf.indexOf("sparesnew")).toString());
    ui->eComment->setPlainText(qf.value(recf.indexOf("comment")).toString());


    QModelIndexList idx_m = ui->eMaster->model()->match(ui->eMaster->model()->index(0, 0), Qt::EditRole, qf.value(recf.indexOf("master")), 1, Qt::MatchExactly);
    ui->eMaster->setCurrentIndex(idx_m.value(0).row());

    QModelIndexList idx_s = ui->eState->model()->match(ui->eState->model()->index(0, 0), Qt::EditRole, qf.value(recf.indexOf("state")), 1, Qt::MatchExactly);
    ui->eState->setCurrentIndex(idx_s.value(0).row());

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
        ui->tview->setItem(i, 1, new QTableWidgetItem(lqt.at(i)));
        ui->tview->setItem(i, 2, new QTableWidgetItem(qfs.value(recfs.indexOf("price")).toString()));
        ui->tview->setItem(i, 3, new QTableWidgetItem(qfs.value(recfs.indexOf("id")).toString()));
    }
}

void EditPartsRequest::submitReport()
{
    QSqlRecord rec_m = model_m->record(ui->eMaster->currentIndex());
    QString id_m = rec_m.value(rec_m.indexOf("id")).toString();

    QSqlRecord rec_s = model_s->record(ui->eState->currentIndex());
    QString id_s = rec_s.value(rec_s.indexOf("id")).toString();

    QString spares;
    QString quants;

    lqt.clear();
    lsp.clear();

    i = ui->tview->rowCount();
    int r;
    for(r=0; r<i; r++)
    {
        lqt.append(ui->tview->item(r,1)->text());
        lsp.append(ui->tview->item(r,3)->text());
    }
    spares = lsp.join(",");
    quants = lqt.join(",");

    QSqlQuery q;
    if (isnew)
        q.prepare("INSERT INTO part_requests VALUES (NULL, NULL, :master, :orderid, :spares, :quants, :sparesnew, :state, :comment)");
    else
        q.prepare("UPDATE part_requests SET master = :master, spares = :spares, quants = :quants, sparesnew = :sparesnew, \
                  comment = :comment,  WHERE id = " + requestID);
    q.bindValue(":orderid", ui->eOrderID->text());
    q.bindValue(":master", id_m);
    q.bindValue(":spares", spares);
    q.bindValue(":quants", quants);
    q.bindValue(":sparesnew", ui->eSparesNew->toPlainText());
    q.bindValue(":state", id_s);
    q.bindValue(":comment", ui->eComment->toPlainText());
    q.exec();
    saved = true;
    qDebug() << q.lastError().text();
}

void EditPartsRequest::on_eSpare_currentIndexChanged(int index)
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

void EditPartsRequest::on_bUse_clicked()
{
    int rc = ui->tview->rowCount();
    ui->tview->insertRow(rc);
    ui->tview->setItem(rc, 0, new QTableWidgetItem(ui->eSpare->currentText()));
    ui->tview->setItem(rc, 1, new QTableWidgetItem("1"));
    ui->tview->setItem(rc, 2, new QTableWidgetItem(ui->eSPrice->text()));
    ui->tview->setItem(rc, 3, new QTableWidgetItem(id_s));
}

void EditPartsRequest::on_bRemove_clicked(){
    ui->tview->removeRow(ui->tview->currentRow());}

void EditPartsRequest::on_bCancel_clicked(){
    close();}

void EditPartsRequest::on_bSave_clicked(){
    submitReport();
    close();
    emit requestSubmited();}

void EditPartsRequest::reject(){
    close();}

