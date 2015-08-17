#include "giveorderdiag.h"
#include "ui_giveorderdiag.h"

GiveOrderDiag::GiveOrderDiag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GiveOrderDiag)
{
    GiveOrderDiag::activateWindow();
    ui->setupUi(this);
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
        QPushButton *bSave = mb.addButton(tr("Save"), QMessageBox::ActionRole);
        QPushButton *bDiscard = mb.addButton(tr("Delete"), QMessageBox::ActionRole);
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
        ui->eDate->setDate(QDate::currentDate());
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
    qf.first();
    ui->eDate->setDate(qf.value(recf.indexOf("date")).toDate());
    ui->eInspect->setPlainText(qf.value(recf.indexOf("inspect")).toString());
    ui->eDefects->setPlainText(qf.value(recf.indexOf("defects")).toString());
    ui->eRecomm->setPlainText(qf.value(recf.indexOf("recomm")).toString());
}

void GiveOrderDiag::submitOrder()
{
    QSqlRecord rec_e = model_e->record(ui->eGiver->currentIndex());
    QString id_e = rec_e.value(rec_e.indexOf("id")).toString();

    q.prepare("UPDATE orders SET state = :state, date_out = :date_out, giver = :giver "
              "WHERE number = " + orderID);
    q.bindValue(":state", "9");
    q.bindValue(":date_out", ui->eDate->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
    q.bindValue(":giver", id_e);

    q.exec();
    saved = true;
    q.clear();
}

void GiveOrderDiag::setRptValue(const int recNo, const QString paramName, QVariant &paramValue, const int reportPage)
{
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
