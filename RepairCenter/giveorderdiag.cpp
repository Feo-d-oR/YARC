#include "giveorderdiag.h"
#include "ui_giveorderdiag.h"
#include "mainwindow.h"

GiveOrderDiag::GiveOrderDiag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GiveOrderDiag)
{
    GiveOrderDiag::activateWindow();
    ui->setupUi(this);

    isnew = false;

    if(MainWindow::role ==2 && !MainWindow::acceptorCanEditDiag){
        ui->eInspect->setDisabled(1);
        ui->eDefects->setDisabled(1);
        ui->eRecomm->setDisabled(1);}
}

GiveOrderDiag::~GiveOrderDiag()
{
    delete ui;
}

void GiveOrderDiag::closeEvent(QCloseEvent *event)
{
    if (saved == false)
    {
        QMessageBox mb;
        mb.setWindowTitle(tr("Issue off diagnostics"));
        mb.setText(tr("Save changes?"));
        QPushButton *bSave = mb.addButton(tr("Yes"), QMessageBox::ActionRole);
        QPushButton *bDiscard = mb.addButton(tr("No"), QMessageBox::ActionRole);
        QPushButton *bCancel = mb.addButton(tr("Cancel"), QMessageBox::ActionRole);
        mb.setDefaultButton(bCancel);
        mb.exec();

        if (mb.clickedButton() == bSave){
            submitOrder();
            saved = true;
            event->accept();
        }
        if (mb.clickedButton() == bDiscard)
            event->accept();
        if (mb.clickedButton() == bCancel)
            event->ignore();
    }
    else if (saved == true)
        event->accept();
}

void GiveOrderDiag::getMode(QString mode, QString num)
{
    if (mode == "new")
    {
        ui->eDate->setDateTime(QDateTime::currentDateTime());
        ui->eOrderID->setText(num);
        qDebug()<<num;
        setModels();
        ui->eGiver->setCurrentIndex(-1);
    }
}

void GiveOrderDiag::on_eOrderID_textChanged(const QString &arg1)
{
    orderID = arg1;
    fillFields();
}

void GiveOrderDiag::setModels()
{
    model_e = new QSqlQueryModel();
    model_e->setQuery("SELECT id, name FROM employees WHERE position_type = '2' AND isactive = '1'");
    ui->eGiver->setModel(model_e);
    ui->eGiver->setModelColumn(1);
    ui->eGiver->model()->sort(1, Qt::AscendingOrder);
}

void GiveOrderDiag::fillFields()
{
    qf.exec("SELECT * FROM diag_reports WHERE orderid = " + orderID);
    recf = qf.record();
    if (qf.last())
    {
        ui->eDate->setDateTime(qf.value(recf.indexOf("date")).toDateTime());
        ui->eInspect->setPlainText(qf.value(recf.indexOf("inspect")).toString());
        ui->eDefects->setPlainText(qf.value(recf.indexOf("defects")).toString());
        ui->eRecomm->setPlainText(qf.value(recf.indexOf("recomm")).toString());
        reportID = qf.value(recf.indexOf("id")).toString();
    }
    else isnew = true;
}

void GiveOrderDiag::submitOrder()
{
    QSqlRecord rec_e = model_e->record(ui->eGiver->currentIndex());
    QString id_e = rec_e.value(rec_e.indexOf("id")).toString();

    if (isnew)
        q.prepare("INSERT INTO diag_reports VALUES (NULL, NULL, :orderid, :employee, :inspect, :defects, :recomm)");
    else
        q.prepare("UPDATE diag_reports SET date = :date, employee = :employee, inspect = :inspect, defects = :defects, recomm = :recomm WHERE id = " + reportID);
    q.bindValue(":date", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    q.bindValue(":orderid", orderID);
    q.bindValue(":employee", id_e);
    q.bindValue(":inspect", ui->eInspect->toPlainText());
    q.bindValue(":defects", ui->eDefects->toPlainText());
    q.bindValue(":recomm", ui->eRecomm->toPlainText());
    q.exec();

    q.prepare("UPDATE orders SET state = :state, date_out = :date_out, giver = :giver "
              "WHERE number = " + orderID);
    q.bindValue(":state", "9");
    q.bindValue(":date_out", ui->eDate->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
    q.bindValue(":giver", id_e);
    q.exec();
    q.prepare("INSERT INTO orders_log SET date = :date, orderid = :orderid, operation = :operation, state = :state, employee = :employee");
    q.bindValue(":date", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    q.bindValue(":orderid", orderID);
    if (ui->cbIssuedDiag->isChecked()){
            q.bindValue(":state", 9);
            q.bindValue(":operation", tr("Order issued")); }
    else {
        q.bindValue(":operation", tr("Someone playing around...")); }
    q.bindValue(":employee", id_e.toInt());
    q.exec();

    if(ui->cbIssuedDiag->isChecked())
        q.exec("UPDATE orders SET state = 9 WHERE number = " + orderID);

    saved = true;
}

void GiveOrderDiag::setRptValue(const int recNo, const QString paramName, QVariant &paramValue, const int reportPage)
{
    Q_UNUSED(recNo)
    Q_UNUSED(reportPage)
    q.exec("SELECT * FROM orders WHERE number = " + orderID);
    q.first();
    rec = q.record();
    if (paramName == "number")
        paramValue = ui->eOrderID->text();
    if (paramName == "date")
        paramValue = ui->eDate->text();
    if (paramName == "product")
        paramValue = q.value(rec.indexOf("product")).toString();
    if (paramName == "serial")
        paramValue = q.value(rec.indexOf("serial")).toString();
    if (paramName == "giver")
        paramValue = ui->eGiver->currentText();
    if (paramName == "customer") {
        QString customerID = q.value(rec.indexOf("customer")).toString();
        qc.exec("SELECT name FROM customers WHERE id = " + customerID);
        qc.first();
        recc = qc.record();
        paramValue = qc.value(recc.indexOf("name")).toString();
    }
    if (paramName == "product_type") {
        QString ptypeID = q.value(rec.indexOf("product_type")).toString();
        qt.exec("SELECT name FROM product_types WHERE id = " + ptypeID);
        qt.first();
        rect = qt.record();
        paramValue = qt.value(rect.indexOf("name")).toString();
    }
    if (paramName == "inspect")
        paramValue = ui->eInspect->toPlainText();
    if (paramName == "defects")
        paramValue = ui->eDefects->toPlainText();
    if (paramName == "recomm")
        paramValue = ui->eRecomm->toPlainText();
}

void GiveOrderDiag::print()
{
    report1 = new QtRPT(this);
    QString fileName = "./print_forms/act_diag.xml";
    if (report1->loadReport(fileName) == false) {
    qDebug()<<"Report file not found: " << fileName;
    }
    connect(report1,SIGNAL(setValue(const int, const QString, QVariant&, const int)), this, SLOT(setRptValue(const int, const QString, QVariant&, const int)));

    if (ui->cPreview->isChecked())
        report1->printExec(true);
    else
        report1->printExec(true,true);
}

void GiveOrderDiag::on_bCancel_clicked(){
    close();}

void GiveOrderDiag::on_bPrint_clicked(){
    print();}

void GiveOrderDiag::on_bSave_clicked(){
    submitOrder();
    close();
    emit orderSubmited();}

void GiveOrderDiag::reject()
{
    close();
}
