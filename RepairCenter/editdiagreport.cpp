#include "editdiagreport.h"
#include "ui_editdiagreport.h"
#include "mainwindow.h"

EditDiagReport::EditDiagReport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDiagReport)
{
    EditDiagReport::activateWindow();
    ui->setupUi(this);
    isnew = true;
}

EditDiagReport::~EditDiagReport(){
    delete ui;}

void EditDiagReport::closeEvent(QCloseEvent *event)
{
    if (saved == false){
        QMessageBox mb;
        mb.setWindowTitle(tr("Diagnostics report"));
        mb.setText(tr("Save changes?"));
        QPushButton *bSave = mb.addButton(tr("Yes"), QMessageBox::ActionRole);
        QPushButton *bDiscard = mb.addButton(tr("No"), QMessageBox::ActionRole);
        QPushButton *bCancel = mb.addButton(tr("Cancel"), QMessageBox::ActionRole);
        mb.setDefaultButton(bCancel);
        mb.exec();

        if (mb.clickedButton() == bSave){
            submitReport();
            saved = true;
            event->accept();}
        if (mb.clickedButton() == bDiscard)
            event->accept();
        if (mb.clickedButton() == bCancel)
            event->ignore();
    }
    else if (saved == true)
        event->accept();
}

void EditDiagReport::getMode(QString mode, QString num)
{
    if (mode == "new"){
        QWidget::setWindowTitle(tr("New diagnostics report"));
        ui->eDate->setDateTime(QDateTime::currentDateTime());
        ui->eOrderID->setText(num);
        setModels();
        isnew = true;
    }
    else if (mode == "view"){
        saved = true;
        QWidget::setWindowTitle(tr("View diagnostics report"));
        setModels();
        reportID = num;
        fillFields();
        ui->bSave->setEnabled(false);
        isnew = false;
    }
    else if (mode == "edit"){
        saved = true;
        QWidget::setWindowTitle(tr("Edit diagnostics report"));
        setModels();
        reportID = num;
        fillFields();
        isnew = false;
    }
}

void EditDiagReport::setModels()
{
    model_m = new QSqlQueryModel();
    model_m->setQuery("SELECT id, name FROM employees WHERE position_type = '1' AND isactive = '1'");
    ui->eMaster->setModel(model_m);
    ui->eMaster->setModelColumn(1);
    ui->eMaster->model()->sort(1, Qt::AscendingOrder);

    QModelIndexList idx_m = ui->eMaster->model()->match(ui->eMaster->model()->index(0, 0), Qt::EditRole, MainWindow::defMaster, 1, Qt::MatchExactly);
    ui->eMaster->setCurrentIndex(idx_m.value(0).row());
}

void EditDiagReport::checkExist()
{
    QSqlQuery qc;
    QSqlRecord recc;
    qc.exec("SELECT * FROM diag_reports WHERE orderid = " + ui->eOrderID->text());
    if (qc.first()) {
        QMessageBox mbex;
        mbex.setWindowTitle(tr("Diagnostics report"));
        mbex.setText(tr("Diagnostics report for that order already exist!"));
        QPushButton *bEdit = mbex.addButton(tr("Edit"), QMessageBox::ActionRole);
        QPushButton *bClose = mbex.addButton(tr("Close"), QMessageBox::ActionRole);
        mbex.setDefaultButton(bEdit);
        mbex.exec();

        if (mbex.clickedButton() == bEdit){
            saved = true;
            QWidget::setWindowTitle(tr("Edit diagnostics report"));
            setModels();
            reportID = qc.value(recc.indexOf("id")).toString();
            fillFields();
            isnew = false;
        }
        if (mbex.clickedButton() == bClose)
            close();
    }
    else
        return;
}

void EditDiagReport::fillFields()
{
    qf.exec("SELECT * FROM diag_reports WHERE id = " + reportID);
    recf = qf.record();
    qf.first();

    ui->eOrderID->setText(qf.value(recf.indexOf("orderid")).toString());
    ui->eDate->setDateTime(qf.value(recf.indexOf("date")).toDateTime());

    QModelIndexList idx_m = ui->eMaster->model()->match(ui->eMaster->model()->index(0, 0), Qt::EditRole, qf.value(recf.indexOf("master")), 1, Qt::MatchExactly);
    ui->eMaster->setCurrentIndex(idx_m.value(0).row());

    ui->eInspect->setPlainText(qf.value(recf.indexOf("inspect")).toString());
    ui->eDefects->setPlainText(qf.value(recf.indexOf("defects")).toString());
    ui->eRecomm->setPlainText(qf.value(recf.indexOf("recomm")).toString());
}

void EditDiagReport::submitReport()
{
    QSqlRecord rec_m = model_m->record(ui->eMaster->currentIndex());
    QString id_m = rec_m.value(rec_m.indexOf("id")).toString();

    QSqlQuery q;
    if (isnew)
        q.prepare("INSERT INTO diag_reports VALUES (NULL, NULL, :orderid, :master, :inspect, :defects, :recomm)");
    else
        q.prepare("UPDATE diag_reports SET date = :date, master = :master, inspect = :inspect, defects = :defects, recomm = :recomm WHERE id = " + reportID);
    q.bindValue(":date", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    q.bindValue(":orderid", ui->eOrderID->text());
    q.bindValue(":master", id_m);
    q.bindValue(":inspect", ui->eInspect->toPlainText());
    q.bindValue(":defects", ui->eDefects->toPlainText());
    q.bindValue(":recomm", ui->eRecomm->toPlainText());
    q.exec();
    q.prepare("INSERT INTO orders_log SET date = :date, orderid = :orderid, state = :state, operation = :operation, employee = :employee");
    q.bindValue(":date", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    q.bindValue(":orderid", ui->eOrderID->text());
    q.bindValue(":employee", id_m.toInt());
    if (isnew)
        q.bindValue(":operation", tr("Diagnosis report submited"));
    else
        q.bindValue(":operation", tr("Diagnosis report edited"));
    if(ui->cbDiagComplete->isChecked())
        q.bindValue(":state", 5);
    q.exec();
    if(ui->cbDiagComplete->isChecked())
        q.exec("UPDATE orders SET state = 5 WHERE number = " + ui->eOrderID->text());
    saved = true;
}

void EditDiagReport::on_bCancel_clicked(){
    close();}

void EditDiagReport::on_bSave_clicked(){
    submitReport();
    close();
    emit reportSubmited();}

void EditDiagReport::reject()
{
    close();
}

void EditDiagReport::on_eOrderID_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
//    checkExist();
}
