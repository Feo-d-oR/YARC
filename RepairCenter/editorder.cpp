#include "editorder.h"
#include "ui_editorder.h"

EditOrder::EditOrder(QWidget *parent):
    QDialog(parent),
    ui(new Ui::EditOrder)
{
    EditOrder::activateWindow();

    isnew = true;
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
        mb.setWindowTitle(tr("Заказ"));
        mb.setText(tr("Сохранить изменения?"));
        QPushButton *bSave = mb.addButton(tr("Сохранить"), QMessageBox::ActionRole);
        QPushButton *bDiscard = mb.addButton(tr("Удалить"), QMessageBox::ActionRole);
        QPushButton *bCancel = mb.addButton(tr("Отмена"), QMessageBox::ActionRole);
        mb.setDefaultButton(bCancel);
        mb.exec();

        if (mb.clickedButton() == bSave){
            submitOrder();
            saved = true;
            event->accept();
        }
        if (mb.clickedButton() == bDiscard){
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
    if (mode == "new" && isnew == true)
    {
        isnew = false; //this prevents multiple records creation
        QWidget::setWindowTitle(tr("Новый заказ"));
        allocateNumber();
        ui->eDate->setDate(QDate::currentDate());
        setModels();
    }
    else if (mode == "view")
    {
        isnew = false;
        saved = true;
        orderID = num;
        QWidget::setWindowTitle(tr("Просмотр заказа"));
        ui->bSave->setDisabled(true);
        setModels();
        fillFields();
    }
    else if (mode == "edit")
    {
        isnew = false;
        saved = true;
        orderID = num;
        QWidget::setWindowTitle(tr("Редактирование заказа"));
        setModels();
        fillFields();
    }
    else if (mode == "fill")
    {

    }
}

void EditOrder::allocateNumber()
{
    q.exec("INSERT INTO orders (number) VALUES (null)");  //inserting empty string
    orderID = q.lastInsertId().toString();  //gets auto-incremet value

    qc.exec("INSERT INTO customers (id) VALUES (null)");
    customerID = qc.lastInsertId().toString();

    ui->eNumber->setText(orderID);
    ui->eNumber->setReadOnly(true);
    saved = false;
}

void EditOrder::setModels()
{
    model_s = new QSqlQueryModel();
    model_s->setQuery("SELECT id, name FROM states");
    ui->eState->setModel(model_s);
    ui->eState->setModelColumn(1);

    model_e = new QSqlQueryModel();
    model_e->setQuery("SELECT id, name FROM employees");
    ui->eAcceptor->setModel(model_e);
    ui->eAcceptor->setModelColumn(1);
    ui->eMaster->setModel(model_e);
    ui->eMaster->setModelColumn(1);

//    model_t = new QSqlQueryModel();
//    model_t->setQuery("SELECT id, name FROM product_types");
    model_t = new QSqlTableModel();
    model_t->setTable("product_types");
    model_t->setEditStrategy(QSqlTableModel::OnFieldChange);

    ui->eProductType->setModel(model_t);
    ui->eProductType->setModelColumn(model_t->fieldIndex("name"));
    model_t->select();
//    ui->eProductType->setDuplicatesEnabled(false);
}

void EditOrder::removeAllocated()
{
    q.exec("DELETE FROM orders WHERE number = " + orderID);
    q.exec("DELETE FROM customers WHERE id =" + customerID);
    saved = true;
}

void EditOrder::fillFields()
{
    q.exec("SELECT * FROM orders WHERE number = " + orderID);
    rec = q.record();
    q.first();

    ui->eNumber->setText(orderID);
    ui->eDate->setDate(q.value(rec.indexOf("date_in")).toDate());
    ui->eProduct->setText(q.value(rec.indexOf("product")).toString());
    ui->eSerial->setText(q.value(rec.indexOf("serial")).toString());
    ui->eSerial->setText(q.value(rec.indexOf("serial")).toString());
    ui->eDisease->setText(q.value(rec.indexOf("disease")).toString());
    ui->eCond->setText(q.value(rec.indexOf("cond")).toString());
    ui->eComplect->setText(q.value(rec.indexOf("complect")).toString());
    ui->eCost->setText(q.value(rec.indexOf("cost")).toString());
    ui->eComment->setPlainText(q.value(rec.indexOf("comment")).toString());

    customerID = q.value(rec.indexOf("customer")).toString();
    qc.exec("SELECT name, phone FROM customers WHERE id = " + customerID);
    recc = qc.record();
    qc.first();
    ui->eCustomer->setText(qc.value(recc.indexOf("name")).toString());
    ui->ePhone->setText(qc.value(recc.indexOf("phone")).toString());

    QModelIndexList idx_s = ui->eState->model()->match(ui->eState->model()->index(0, 0), Qt::EditRole, q.value(rec.indexOf("state")), 1, Qt::MatchExactly);
    ui->eState->setCurrentIndex(idx_s.value(0).row());

    QModelIndexList idx_t = ui->eProductType->model()->match(ui->eProductType->model()->index(0, 0), Qt::EditRole, q.value(rec.indexOf("product_type")), 1, Qt::MatchExactly);
    ui->eProductType->setCurrentIndex(idx_t.value(0).row());

    QModelIndexList idx_a = ui->eAcceptor->model()->match(ui->eAcceptor->model()->index(0, 0), Qt::EditRole, q.value(rec.indexOf("acceptor")), 1, Qt::MatchExactly);
    ui->eAcceptor->setCurrentIndex(idx_a.value(0).row());

    QModelIndexList idx_m = ui->eMaster->model()->match(ui->eState->model()->index(0, 0), Qt::EditRole, q.value(rec.indexOf("master")), 1, Qt::MatchExactly);
    ui->eMaster->setCurrentIndex(idx_m.value(0).row());

}

void EditOrder::submitOrder()
{
    QSqlRecord rec_s = model_s->record(ui->eState->currentIndex());
    QString id_s = rec_s.value(rec_s.indexOf("id")).toString();

    QSqlRecord rec_t = model_t->record(ui->eProductType->currentIndex());
    QString id_t = rec_t.value(rec_t.indexOf("id")).toString();

    QSqlRecord rec_a = model_e->record(ui->eAcceptor->currentIndex());
    QString id_a= rec_a.value(rec_a.indexOf("id")).toString();

    QSqlRecord rec_m = model_e->record(ui->eMaster->currentIndex());
    QString id_m = rec_m.value(rec_m.indexOf("id")).toString();

    qc.prepare("UPDATE customers SET name = :name, phone = :phone WHERE id = " + customerID);
    qc.bindValue(":name", ui->eCustomer->text());
    qc.bindValue(":phone", ui->ePhone->text());
    qc.exec();

    q.prepare("UPDATE orders SET state = :state, customer = :customer, phone = :phone, product_type = :product_type, product = :product, "
              " serial = :serial, disease = :disease, cond = :cond, complect = :complect, cost = :cost, acceptor = :acceptor, master = :master, comment = :comment "
              "WHERE number = " + orderID);
    q.bindValue(":state", id_s);
    q.bindValue(":customer", customerID);
    q.bindValue(":phone", customerID);
    q.bindValue(":product_type", id_t);
    q.bindValue(":product", ui->eProduct->text());
    q.bindValue(":serial", ui->eSerial->text());
    q.bindValue(":disease", ui->eDisease->text());
    q.bindValue(":cond", ui->eCond->text());
    q.bindValue(":complect", ui->eComplect->text());
    q.bindValue(":cost", ui->eCost->text());
    q.bindValue(":acceptor", id_a);
    q.bindValue(":master", id_m);
    q.bindValue(":comment", ui->eComment->toPlainText());
    q.exec();
    saved = true;
}

void EditOrder::setRptValue(int &recNo, QString &paramName, QVariant &paramValue, int reportPage)
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
        paramValue = ui->eDisease->text();
    if (paramName == "cond")
        paramValue = ui->eCond->text();
    if (paramName == "complect")
        paramValue = ui->eComplect->text();
    if (paramName == "cost")
        paramValue = ui->eCost->text();
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
    connect(report,SIGNAL(setValue(int&,QString&,QVariant&,int)), this, SLOT(setRptValue(int&,QString&,QVariant&,int)));
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
    submitOrder();    
    close();
    emit orderSubmited();
}

void EditOrder::on_bAddType_clicked()
{
    qpt.exec("INSERT INTO product_types (name) VALUES ('" + ui->eProductType->currentText() + "')");
    model_t->select();
    QModelIndexList idx_t = ui->eProductType->model()->match(ui->eProductType->model()->index(0, 0), Qt::EditRole, qpt.lastInsertId().toInt(), 1, Qt::MatchExactly);
    ui->eProductType->setCurrentIndex(idx_t.value(0).row());

}

void EditOrder::reject()
{
    close();
}
