#include "editorder.h"
#include "ui_editorder.h"
#include "mainwindow.h"

EditOrder::EditOrder(QWidget *parent):
    QDialog(parent),
    ui(new Ui::EditOrder)
{
    EditOrder::activateWindow();

    block = false;
    ui->setupUi(this);
}

EditOrder::~EditOrder()
{
    delete ui;
}

void EditOrder::closeEvent(QCloseEvent *event)
{
    if (saved == false)
    {
        QMessageBox mb;
        mb.setWindowTitle(tr("Order"));
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
            if (isnew == true)
                removeAllocated();
            event->accept();
        }
        if (mb.clickedButton() == bCancel){
            event->ignore();
        }

    }
    else if (saved == true)
        event->accept();
}

void EditOrder::getMode(QString mode, QString num)
{
    if (mode == "new" && block == false)
    {
        block = true; //this prevents multiple records creation
        saved = false;
        isnew = true;
        QWidget::setWindowTitle(tr("New order"));
        ui->eDate->setDateTime(QDateTime::currentDateTime());
        setModels();
        allocateNumber();
        setDefaults();
        setCheckboxTemplates();
        ui->eProductType->setCurrentIndex(-1);
    }
    else if (mode == "view")
    {
        isnew = false;
        saved = true;
        orderID = num;
        QWidget::setWindowTitle(tr("View order"));
        ui->bSave->setDisabled(true);
        setModels();
        fillFields();
    }
    else if (mode == "edit")
    {
        isnew = false;
        saved = false;
        orderID = num;
        QWidget::setWindowTitle(tr("Edit order"));
        setModels();
        fillFields();
    }
}

void EditOrder::allocateNumber()
{
    q.exec("INSERT INTO orders (number) VALUES (null)");  //inserting empty string
    orderID = q.lastInsertId().toString();  //gets auto-incremet value

    qc.exec("INSERT INTO customers (id) VALUES (null)");
    newCustomerID = qc.lastInsertId().toString();
    customerID = newCustomerID;

    ui->eNumber->setText(orderID);
    ui->eNumber->setReadOnly(true);
}

void EditOrder::setDefaults()
{
    idx_a = ui->eAcceptor->model()->match(ui->eAcceptor->model()->index(0, 0), Qt::EditRole, MainWindow::defAcceptor, 1, Qt::MatchExactly);
    ui->eAcceptor->setCurrentIndex(idx_a.value(0).row());

    idx_m = ui->eMaster->model()->match(ui->eMaster->model()->index(0, 0), Qt::EditRole, MainWindow::defMaster, 1, Qt::MatchExactly);
    ui->eMaster->setCurrentIndex(idx_m.value(0).row());

    idx_s = ui->eState->model()->match(ui->eState->model()->index(0, 0), Qt::EditRole, MainWindow::defState, 1, Qt::MatchExactly);
    ui->eState->setCurrentIndex(idx_s.value(0).row());

    if (MainWindow::productTypeM)
        ui->llProductType->setStyleSheet("QLabel{color: crimson}");
    if (MainWindow::productM)
        ui->llProduct->setStyleSheet("QLabel{color: crimson}");
    if (MainWindow::serialM)
        ui->llSerial->setStyleSheet("QLabel{color: crimson}");
    if (MainWindow::defectM)
        ui->llDefect->setStyleSheet("QLabel{color: crimson}");
    if (MainWindow::conditionM)
        ui->llCondition->setStyleSheet("QLabel{color: crimson}");
    if (MainWindow::completenessM)
        ui->llCompleteness->setStyleSheet("QLabel{color: crimson}");
    if (MainWindow::customerM)
        ui->llCustomer->setStyleSheet("QLabel{color: crimson}");
    if (MainWindow::phoneM)
        ui->llPhone->setStyleSheet("QLabel{color: crimson}");
}

void EditOrder::setModels()
{
    model_s = new QSqlQueryModel();
    if (isnew == true)
        model_s->setQuery("SELECT id, name FROM states WHERE id IN (1, 2, 14, 16, 19)");
    if (isnew == false)
        model_s->setQuery("SELECT id, name FROM states");
    ui->eState->setModel(model_s);
    ui->eState->model()->sort(1, Qt::AscendingOrder);
    ui->eState->setModelColumn(1);

    model_a = new QSqlQueryModel();
    model_a->setQuery("SELECT id, name FROM employees WHERE position_type = 2 AND isactive = 1");
    ui->eAcceptor->setModel(model_a);
    ui->eAcceptor->model()->sort(1, Qt::AscendingOrder);
    ui->eAcceptor->setModelColumn(1);


    model_m = new QSqlQueryModel();
    model_m->setQuery("SELECT id, name FROM employees WHERE position_type = 1 AND isactive = 1");
    ui->eMaster->setModel(model_m);
    ui->eMaster->model()->sort(1, Qt::AscendingOrder);
    ui->eMaster->setModelColumn(1);

    model_t = new QSqlTableModel();
    model_t->setTable("product_types");
    model_t->setEditStrategy(QSqlTableModel::OnFieldChange);
    ui->eProductType->setModel(model_t);
    ui->eProductType->setModelColumn(model_t->fieldIndex("name"));
    model_t->select();
}

void EditOrder::removeAllocated()
{
    q.exec("DELETE FROM orders WHERE number = " + orderID);
    q.exec("DELETE FROM customers WHERE id =" + newCustomerID);
    saved = true;
}

void EditOrder::getCustomer()
{
    qc.exec("SELECT name, phone FROM customers WHERE id = " + customerID);
    recc = qc.record();
    qc.first();
    ui->eCustomer->setText(qc.value(recc.indexOf("name")).toString());
    ui->ePhone->setText(qc.value(recc.indexOf("phone")).toString());
}

void EditOrder::fillFields()
{
    q.exec("SELECT * FROM orders WHERE number = " + orderID);
    rec = q.record();
    q.first();

    ui->eNumber->setText(orderID);
    ui->eDate->setDateTime(q.value(rec.indexOf("date_in")).toDateTime());
    ui->eProduct->setText(q.value(rec.indexOf("product")).toString());
    ui->eSerial->setText(q.value(rec.indexOf("serial")).toString());
    ui->eSerial->setText(q.value(rec.indexOf("serial")).toString());
    ui->eDisease->setText(q.value(rec.indexOf("disease")).toString());
    ui->eCond->setText(q.value(rec.indexOf("cond")).toString());
    ui->eComplect->setText(q.value(rec.indexOf("complect")).toString());
    ui->eCost->setText(q.value(rec.indexOf("cost")).toString());
    ui->eComment->setPlainText(q.value(rec.indexOf("comment")).toString());

    if ((q.value(rec.indexOf("product")).toString() == "reserved") && block == false)
    {
        block = true;
        qc.exec("INSERT INTO customers (id) VALUES (null)");
        newCustomerID = qc.lastInsertId().toString();
        ui->eDate->setDateTime(QDateTime::currentDateTime());
        ui->eDate->setReadOnly(false);
        customerID = newCustomerID;
    }
    else
    {
        customerID = q.value(rec.indexOf("customer")).toString();
        getCustomer();
    }

    idx_s = ui->eState->model()->match(ui->eState->model()->index(0, 0), Qt::EditRole, q.value(rec.indexOf("state")), 1, Qt::MatchExactly);
    ui->eState->setCurrentIndex(idx_s.value(0).row());

    idx_t = ui->eProductType->model()->match(ui->eProductType->model()->index(0, 0), Qt::EditRole, q.value(rec.indexOf("product_type")), 1, Qt::MatchExactly);
    ui->eProductType->setCurrentIndex(idx_t.value(0).row());

    idx_a = ui->eAcceptor->model()->match(ui->eAcceptor->model()->index(0, 0), Qt::EditRole, q.value(rec.indexOf("acceptor")), 1, Qt::MatchExactly);
    ui->eAcceptor->setCurrentIndex(idx_a.value(0).row());

    idx_m = ui->eMaster->model()->match(ui->eMaster->model()->index(0, 0), Qt::EditRole, q.value(rec.indexOf("master")), 1, Qt::MatchExactly);
    ui->eMaster->setCurrentIndex(idx_m.value(0).row());
}

void EditOrder::submitOrder()
{
    QSqlRecord rec_s = model_s->record(ui->eState->currentIndex());
    QString id_s = rec_s.value(rec_s.indexOf("id")).toString();

    QSqlRecord rec_t = model_t->record(ui->eProductType->currentIndex());
    QString id_t = rec_t.value(rec_t.indexOf("id")).toString();

    QSqlRecord rec_a = model_a->record(ui->eAcceptor->currentIndex());
    QString id_a = rec_a.value(rec_a.indexOf("id")).toString();

    QSqlRecord rec_m = model_m->record(ui->eMaster->currentIndex());
    QString id_m = rec_m.value(rec_m.indexOf("id")).toString();

    qc.prepare("UPDATE customers SET name = :name, phone = :phone WHERE id = " + customerID);
    qc.bindValue(":name", ui->eCustomer->text());
    qc.bindValue(":phone", ui->ePhone->text());
    qc.exec();

    q.prepare("UPDATE orders SET date_in = :date_in, state = :state, customer = :customer, phone = :phone, product_type = :product_type, product = :product, "
              " serial = :serial, disease = :disease, cond = :cond, complect = :complect, cost = :cost, acceptor = :acceptor, master = :master, comment = :comment, prepay = :prepay "
              "WHERE number = " + orderID);
    q.bindValue(":date_in", ui->eDate->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
    q.bindValue(":state", id_s.toInt());
    q.bindValue(":customer", customerID);
    q.bindValue(":phone", customerID);
    q.bindValue(":product_type", id_t.toInt());
    q.bindValue(":product", ui->eProduct->text());
    q.bindValue(":serial", ui->eSerial->text());
    q.bindValue(":disease", composeString(ui->layout_defects, ui->eDisease->text()));
    q.bindValue(":cond", composeString(ui->layout_conds, ui->eCond->text()));
    q.bindValue(":complect", composeString(ui->layout_compls, ui->eComplect->text()));
    q.bindValue(":cost", ui->eCost->text());
    q.bindValue(":prepay", ui->ePrepay->text());
    q.bindValue(":acceptor", id_a.toInt());
    q.bindValue(":master", id_m.toInt());
    q.bindValue(":comment", ui->eComment->toPlainText());
    q.exec();
    q.prepare("INSERT INTO orders_log SET date = :date, orderid = :orderid, operation = :operation, state = :state, employee = :employee, comment = :comment");
    q.bindValue(":date", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    q.bindValue(":orderid", orderID);
    q.bindValue(":state", id_s.toInt());
    q.bindValue(":employee", id_a.toInt());
    q.bindValue(":comment", ui->eComment->toPlainText());
    if (isnew)
        q.bindValue(":operation", tr("Order created"));
    else
        q.bindValue(":operation", tr("Order edited"));
    q.exec();
    MainWindow::prevCustomer = customerID;
    saved = true;
}

//q.bindValue(":date_out", ui->eDate->dateTime().toString("yyyy-MM-dd hh:mm:ss"));

void EditOrder::setRptValue(const int recNo, const QString paramName, QVariant &paramValue, const int reportPage)
{
    Q_UNUSED(reportPage);
    Q_UNUSED(recNo);

    if (paramName == "number")
        paramValue = ui->eNumber->text();
    if (paramName == "date")
        paramValue = ui->eDate->text();
    if (paramName == "customer")
        paramValue = ui->eCustomer->text();
    if (paramName == "phone")
        paramValue = ui->ePhone->text();
    if (paramName == "product_type")
        paramValue = ui->eProductType->currentText();
    if (paramName == "product")
        paramValue = ui->eProduct->text();
    if (paramName == "serial")
        paramValue = ui->eSerial->text();
    if (paramName == "disease")
        paramValue = composeString(ui->layout_defects, ui->eDisease->text());
    if (paramName == "cond")
        paramValue = composeString(ui->layout_conds, ui->eCond->text());
    if (paramName == "complect")
        paramValue = composeString(ui->layout_compls, ui->eComplect->text());
    if (paramName == "cost")
        paramValue = ui->eCost->text();
    if (paramName == "prepay")
        paramValue = ui->ePrepay->text();
    if (paramName == "acceptor")
        paramValue = ui->eAcceptor->currentText();
}

void EditOrder::print()
{
    QString fileName = "./print_forms/order.xml";
    report = new QtRPT(this);
    if (report->loadReport(fileName) == false) {
        qDebug()<<"Report file not found: " << fileName;
    }
    connect(report,SIGNAL(setValue(const int, const QString, QVariant&, const int)), this, SLOT(setRptValue(const int, const QString, QVariant&, const int)));
    if (ui->cPreview->isChecked())
        report->printExec(true);
    else
        report->printExec(true,true);
}

void EditOrder::on_bCancel_clicked()
{
    close();
}

void EditOrder::on_bPrint_clicked()
{
    print();
}

void EditOrder::on_bSave_clicked()
{
    if(!mandatoryCheck()){
        mandatoryAlert();
        return;}
    else{
        submitOrder();
        close();
        emit orderSubmited();}
}

bool EditOrder::mandatoryCheck()
{
    if (MainWindow::productTypeM)
        if(ui->eProductType->currentIndex() == -1)
            return false;
    if(MainWindow::productM)
            if(ui->eProduct->text() == "")
                return false;
    if(MainWindow::serialM)
        if(ui->eSerial->text() == "")
            return false;
    if(MainWindow::defectM)
        if(ui->eDisease->text() == "")
            return false;
    if(MainWindow::conditionM)
        if(ui->eCond->text() == "")
            return false;
    if(MainWindow::completenessM)
        if(ui->eComplect->text() == "")
            return false;
    if(MainWindow::customerM)
        if(ui->eCustomer->text() == "")
            return false;
    if(MainWindow::phoneM)
        if(ui->ePhone->text() == "")
            return false;
    return true;
}

void EditOrder::mandatoryAlert()
{
    QMessageBox mb;
    mb.setWindowTitle(tr("Attention!"));
    mb.setText(tr("Not all required fields are filled!"));
    QPushButton *bOk = mb.addButton(tr("OK"), QMessageBox::ActionRole);
    mb.setDefaultButton(bOk);
    mb.exec();
}

void EditOrder::on_bAddType_clicked()
{
    QSqlQuery qpt;
    qpt.exec("INSERT INTO product_types (name) VALUES ('" + ui->eProductType->currentText() + "')");
    int lastid = qpt.lastInsertId().toInt(); //QtSql, as of late, returns 0 lastInsertId after model->select(),so additional variable needeed
    model_t->select();
    idx_t = ui->eProductType->model()->match(ui->eProductType->model()->index(0, 0), Qt::EditRole, lastid, 1, Qt::MatchExactly);
    ui->eProductType->setCurrentIndex(idx_t.value(0).row());
}

void EditOrder::reject()
{
    close();
}

void EditOrder::on_rbNew_clicked(bool checked)
{
    if(checked)
    {
        qc.exec("DELETE FROM customers WHERE id =" + newCustomerID);
        ui->eCustomer->clear();
        ui->ePhone->clear();
        ui->cbOldCustomer->setEnabled(false);
        qc.exec("INSERT INTO customers (id) VALUES (null)");
        newCustomerID = qc.lastInsertId().toString();
        customerID = newCustomerID;
    }

}

void EditOrder::on_rbPrev_clicked(bool checked)
{
    if(checked)
    {
        ui->eCustomer->clear();
        ui->ePhone->clear();
        ui->cbOldCustomer->setEnabled(false);
        qc.exec("DELETE FROM customers WHERE id =" + newCustomerID);
        customerID = MainWindow::prevCustomer;
        getCustomer();
    }
}

void EditOrder::on_rbOld_clicked(bool checked)
{
    if(checked)
    {
        qc.exec("DELETE FROM customers WHERE id =" + newCustomerID);
        model_c = new QSqlQueryModel();
        model_c->setQuery("SELECT id, name, phone FROM customers WHERE regular = 1");
        ui->cbOldCustomer->setModel(model_c);
        ui->cbOldCustomer->setModelColumn(1);
        ui->cbOldCustomer->model()->sort(Qt::AscendingOrder);
        ui->cbOldCustomer->setEnabled(true);
    }
}

void EditOrder::on_cbOldCustomer_currentIndexChanged(int index)
{
    if (index != -1)
    {
        recc = model_c->record(index);
        customerID = recc.value(recc.indexOf("id")).toString();
        getCustomer();
    }
}

void EditOrder::setCheckboxTemplates()
{
    settings = new QSettings(QCoreApplication::applicationDirPath()+"/repaircenter.conf",QSettings::IniFormat);
    settings->setIniCodec("UTF-8");
    int i;
    QString num;
    for (i=1; i<=20; i++)
    {
        num = QString::number(i);
        if (settings->contains("defaults/cond" + num) && (settings->value("defaults/cond" + num) != ""))
        {
            qDynamicCheckBox *chb = new qDynamicCheckBox(this);
            chb->setText(settings->value("defaults/cond" + num).toString());
            chb->setID("chBoxCond" + num);
            ui->layout_conds->addWidget(chb);
        }
        if (settings->contains("defaults/defect" + num) && settings->value("defaults/defect" + num) != "")
        {
            qDynamicCheckBox *chb = new qDynamicCheckBox(this);
            chb->setText(settings->value("defaults/defect" + num).toString());
            chb->setID("chBoxDef" + num);
            ui->layout_defects->addWidget(chb);
        }
        if (settings->contains("defaults/compl" + num) && settings->value("defaults/compl" + num) != "")
        {
            qDynamicCheckBox *chb = new qDynamicCheckBox(this);
            chb->setText(settings->value("defaults/compl" + num).toString());
            chb->setID("chBoxCompl" + num);
            ui->layout_compls->addWidget(chb);
        }
    }
    ui->layout_conds->setStretch(ui->layout_conds->count()-1,1);
    ui->layout_compls->setStretch(ui->layout_compls->count()-1,1);
    ui->layout_defects->setStretch(ui->layout_defects->count()-1,1);
}

QString EditOrder::composeString(QLayout *layout, QString str)
{
    QString strResult;
    for (int i = 0; i < layout->count(); i++)
    {
        qDynamicCheckBox *chb = qobject_cast<qDynamicCheckBox*>(layout->itemAt(i)->widget());
        if (chb->isChecked())
        {
            strResult.append(chb->text());
            qDebug()<<"chbText="<<chb->text();
            qDebug()<<"chbShortcut="<<chb->shortcut();

            strResult.append(", ");
        }
    }
    strResult.remove("&");
    strResult.append(str);
    qDebug()<<"strResult="<<strResult;
    return strResult;
}
