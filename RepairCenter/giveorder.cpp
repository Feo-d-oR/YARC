#include "giveorder.h"
#include "ui_giveorder.h"
#include "mainwindow.h"

GiveOrder::GiveOrder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GiveOrder)
{
    GiveOrder::activateWindow();
    ui->setupUi(this);
}

GiveOrder::~GiveOrder()
{
    delete ui;
}

void GiveOrder::closeEvent(QCloseEvent *event)
{
    if (saved == false)
    {
        QMessageBox mb;
        mb.setWindowTitle(tr("Issue off repair"));
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

void GiveOrder::getMode(QString mode, QString num)
{
    if (mode == "new")
    {
        ui->eDate->setDate(QDate::currentDate());
        ui->eOrderID->setText(num);
        setModels();
        ui->eGiver->setCurrentIndex(-1);
    }
}

void GiveOrder::on_eOrderID_textChanged(const QString &arg1)
{
    ui->tvieww->setRowCount(0);
    ui->tviews->setRowCount(0);
    orderID = arg1;
    fillFields();
    calculateSumm();
}

void GiveOrder::setModels()
{
    model_e = new QSqlQueryModel();
    model_e->setQuery("SELECT id, name FROM employees WHERE position_type = '2' AND isactive = '1'");
    ui->eGiver->setModel(model_e);
    ui->eGiver->setModelColumn(1);
    ui->eGiver->model()->sort(1, Qt::AscendingOrder);

    ui->tvieww->setColumnWidth(0, 300);
    ui->tvieww->setColumnWidth(1, 100);
    ui->tvieww->setColumnWidth(2, 100);
    ui->tvieww->setColumnWidth(3, 150);
    ui->tvieww->hideColumn(4);

    ui->tviews->setColumnWidth(0, 300);
    ui->tviews->setColumnWidth(1, 100);
    ui->tviews->setColumnWidth(2, 100);
    ui->tviews->hideColumn(3);
    ui->tviews->hideColumn(4);
}

void GiveOrder::fillFields()
{
    qw.exec("SELECT * FROM work_reports WHERE orderid = " + orderID);
    qw.first();
    recw = qw.record();

    for (roww=0; roww<qw.size(); roww++)
    {
        lsp = qw.value(recw.indexOf("spares")).toString().split(",");
        lqt = qw.value(recw.indexOf("quants")).toString().split(",");
        rcw = ui->tvieww->rowCount();
        ui->tvieww->insertRow(rcw);

        qgn.exec("SELECT name, price FROM works WHERE id = " + qw.value(recw.indexOf("work")).toString());
        qgn.first();
        ui->tvieww->setItem(rcw, 0, new QTableWidgetItem(qgn.value(0).toString()));
        ui->tvieww->setItem(rcw, 2, new QTableWidgetItem(qgn.value(1).toString()));
        qgn.clear();

        qgn.exec("SELECT name FROM employees WHERE id = " + qw.value(recw.indexOf("master")).toString());
        qgn.first();
        ui->tvieww->setItem(rcw, 3, new QTableWidgetItem(qgn.value(0).toString()));
        qgn.clear();

        ui->tvieww->setItem(rcw, 4, new QTableWidgetItem(qw.value(recw.indexOf("work")).toString()));
        ui->tvieww->setItem(rcw, 1, new QTableWidgetItem(qw.value(recw.indexOf("quant")).toString()));

        for (rows=0; rows<lsp.size(); rows++)
        {
            rcs = ui->tviews->rowCount();
            ui->tviews->insertRow(rcs);
            qs.exec("SELECT * FROM spares WHERE id = " + lsp.at(rows));
            qs.first();
            recfs = qs.record();
            ui->tviews->setItem(rcs, 0, new QTableWidgetItem(qs.value(recfs.indexOf("name")).toString()));
            ui->tviews->setItem(rcs, 1, new QTableWidgetItem(lqt.at(rows)));
            ui->tviews->setItem(rcs, 2, new QTableWidgetItem(qs.value(recfs.indexOf("price")).toString()));
            ui->tviews->setItem(rcs, 3, new QTableWidgetItem(qw.value(recw.indexOf("work")).toString()));
            ui->tviews->setItem(rcs, 4, new QTableWidgetItem(qs.value(recfs.indexOf("id")).toString()));
        }
        qw.next();
    }
}

void GiveOrder::calculateSumm()
{
    summ = 0;
    int rcw = ui->tvieww->rowCount();
    int rcs = ui->tviews->rowCount();

    for (roww=0; roww < rcw; roww++)
    {
        summ += ui->tvieww->item(roww, 1)->text().toInt() * ui->tvieww->item(roww, 2)->text().toFloat();
    }
    for (rows=0; rows < rcs; rows++)
    {
        summ += ui->tviews->item(rows, 1)->text().toInt() * ui->tviews->item(rows, 2)->text().toFloat();
    }

    summstr = QString::number(summ);
    ui->eSumm->setText(summstr);
}

void GiveOrder::on_bSumm_clicked()
{
    calculateSumm();
}

void GiveOrder::submitOrder()
{
    q.exec("SELECT state FROM orders WHERE number = "+ orderID);
    q.first();
    if(q.value(0).toInt() != 10)
    {
        qDebug() << "Going salary";

        sala = 0;
        salf = 0;
        QString st;
        for(roww=0; roww<ui->tvieww->rowCount(); roww++)
        {
            q.exec("SELECT id FROM employees WHERE name = '"+ ui->tvieww->item(roww,3)->text() +"'");
            q.first();
            emp = q.value(0).toString();
            sal = ui->tvieww->item(roww,1)->text().toFloat() * ui->tvieww->item(roww,2)->text().toFloat();
            salm = sal * MainWindow::sPercMast;
            sala += sal * MainWindow::sPercAcc;
            salf += sal * MainWindow::sPercFirm;
            q.exec(QString("INSERT INTO salaries VALUES (NULL, "+ emp +", "+ st.setNum(salm) +")"));
        }
        q.exec("SELECT acceptor FROM orders WHERE number = "+ orderID);
        q.first();
        emp = q.value(0).toString();
        q.exec(QString("INSERT INTO salaries VALUES (NULL, "+ emp +", "+ st.setNum(sala) +")"));
        q.exec(QString("INSERT INTO salaries VALUES (NULL, -5, "+ st.setNum(salf) +")"));
    }

    QSqlRecord rec_e = model_e->record(ui->eGiver->currentIndex());
    QString id_e = rec_e.value(rec_e.indexOf("id")).toString();

    q.prepare("UPDATE orders SET state = :state, date_out = :date_out, giver = :giver, warranty = :warranty "
              "WHERE number = " + orderID);
    q.bindValue(":state", "10");
    q.bindValue(":date_out", ui->eDate->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
    q.bindValue(":giver", id_e);
    q.bindValue(":warranty", ui->eWarranty->text());
    q.exec();
    q.clear();
    saved = true;
}

void GiveOrder::setRptValue(const int recNo, const QString paramName, QVariant &paramValue, const int reportPage)
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
    if (paramName == "warranty")
        paramValue = ui->eWarranty->text();
    if (paramName == "NN")
        paramValue = recNo+1;
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
    if (paramName == "work") {
        if (ui->tvieww->item(recNo,0) == 0) return;
        paramValue = ui->tvieww->item(recNo,0)->text();
    }
    if (paramName == "quant") {
        if (ui->tvieww->item(recNo,1) == 0) return;
        paramValue = ui->tvieww->item(recNo,1)->text();
    }
    if (paramName == "summ") {
        if (ui->tvieww->item(recNo,0) == 0) return;
        summ = ui->tvieww->item(recNo, 1)->text().toFloat() * ui->tvieww->item(recNo, 2)->text().toFloat();
        rcs = ui->tviews->rowCount();
        for (rows=0; rows < rcs; rows++) {
            if (ui->tviews->item(rows, 3)->text() == ui->tvieww->item(recNo, 4)->text()) {
                summ += ui->tviews->item(rows, 1)->text().toFloat() * ui->tviews->item(rows, 2)->text().toFloat();
            }
        }
        summstr = QString::number(summ);
        paramValue = summstr;
    }
}

void GiveOrder::print()
{
    if (ui->cAct->isChecked())
    {
        report1 = new QtRPT(this);
        report1->recordCount << ui->tvieww->rowCount();
        QString fileName = "./print_forms/act_works.xml";
        if (report1->loadReport(fileName) == false) {
        qDebug()<<"Report file not found: " << fileName;
        }
        connect(report1,SIGNAL(setValue(const int, const QString, QVariant&, const int)), this, SLOT(setRptValue(const int, const QString, QVariant&, const int)));

        if (ui->cPreview->isChecked())
            report1->printExec(true);
        else
            report1->printExec(true,true);
    }
    if (ui->cWarranty->isChecked())
    {
        report2 = new QtRPT(this);
        report2->recordCount << ui->tvieww->rowCount();
        QString fileName = "./print_forms/warranty_works.xml";
        if (report2->loadReport(fileName) == false) {
        qDebug()<<"Report file not found: " << fileName;
        }
        connect(report2,SIGNAL(setValue(const int, const QString, QVariant&, const int)), this, SLOT(setRptValue(const int, const QString, QVariant&, const int)));

        if (ui->cPreview->isChecked())
            report2->printExec(true);
        else
            report2->printExec(true,true);
    }
}

void GiveOrder::on_bCancel_clicked()
{
    close();
}

void GiveOrder::on_bPrint_clicked()
{
    print();
}

void GiveOrder::on_bSave_clicked()
{
    submitOrder();
    close();
    emit orderSubmited();
}

void GiveOrder::on_eWarranty_textChanged(const QString &arg1)
{
    if (arg1 != "")
        ui->cWarranty->setChecked(true);
    else
        ui->cWarranty->setChecked(false);
}

void GiveOrder::reject()
{
    close();
}
