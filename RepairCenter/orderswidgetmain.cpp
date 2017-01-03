#include "orderswidgetmain.h"
#include "ui_orderswidgetmain.h"
#include "mainwindow.h"
#include "editorder.h"

OrdersWidgetMain::OrdersWidgetMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrdersWidgetMain)
{
    ui->setupUi(this);
    ui->bDelete->setDisabled(true);
    initModelOrders();
    readUiSettings();
    ui->datestart->setDate(QDate::currentDate());
    ui->dateend->setDate(QDate::currentDate());
}

OrdersWidgetMain::~OrdersWidgetMain()
{
    delete ui;
}

void OrdersWidgetMain::initModelOrders()
{
//setting table model
    model = new QSqlRelationalTableModel(ui->tview);
    model->setJoinMode(QSqlRelationalTableModel::LeftJoin); //some fields will be NULL, so we need it
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("orders");
    //remember column indexes
    stateIdx = model->fieldIndex("state");
    masterIdx = model->fieldIndex("master");
    typeIdx = model->fieldIndex("product_type");
    customerIdx = model->fieldIndex("customer");
    acceptorIdx = model->fieldIndex("acceptor");
    giverIdx = model->fieldIndex("giver");
    //setting relations
    model->setRelation(stateIdx, QSqlRelation("states","id","name"));
    model->setRelation(masterIdx, QSqlRelation("employees","id","name"));
    model->setRelation(acceptorIdx, QSqlRelation("employees","id","name"));
    model->setRelation(typeIdx, QSqlRelation("product_types","id","name"));
    model->setRelation(customerIdx, QSqlRelation("customers","id","name"));
    model->setRelation(model->fieldIndex("phone"), QSqlRelation("customers","id","phone"));

    model->setSort(model->fieldIndex("number"),Qt::DescendingOrder);  //setting default sorting

    model->relationModel(model->fieldIndex("master"))->setFilter("position_type = 1 AND isactive = 1");

//setting tableview widget
    ui->tview->setModel(model);

//setting mapper & relations for right panel
    ui->eState->setModel(model->relationModel(stateIdx));
    ui->eState->setModelColumn(model->relationModel(stateIdx)->fieldIndex("name"));
    ui->eState->model()->sort(1, Qt::AscendingOrder);

    ui->eMaster->setModel(model->relationModel(masterIdx));
    ui->eMaster->setModelColumn(model->relationModel(masterIdx)->fieldIndex("name"));
    ui->eMaster->model()->sort(1, Qt::AscendingOrder);

    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->setItemDelegate(new QSqlRelationalDelegate(this));
    mapper->addMapping(ui->dNumber, model->fieldIndex("number"));
    mapper->addMapping(ui->dDateIn, model->fieldIndex("date_in"));
    mapper->addMapping(ui->eCalled, model->fieldIndex("called"));
    mapper->addMapping(ui->datenotify, model->fieldIndex("date_called"));
    mapper->addMapping(ui->eState, stateIdx);
    mapper->addMapping(ui->eMaster, masterIdx);
    mapper->addMapping(ui->dCustomer,customerIdx);
    mapper->addMapping(ui->dPhone, model->fieldIndex("phone"));
    mapper->addMapping(ui->dProductType, typeIdx);
    mapper->addMapping(ui->dProduct, model->fieldIndex("product"));
    mapper->addMapping(ui->dDisease, model->fieldIndex("disease"));
    mapper->addMapping(ui->dDateOut, model->fieldIndex("date_out"));
    mapper->addMapping(ui->dComment, model->fieldIndex("comment"));

    connect(ui->tview->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            mapper, SLOT(setCurrentModelIndex(QModelIndex)));
    model->setFilter("number >= " + MainWindow::showlimit);
    model->select();
}

void OrdersWidgetMain::readUiSettings()
{
    settings = new QSettings(QCoreApplication::applicationDirPath()+"/repaircenter.conf",QSettings::IniFormat);
    settings->setIniCodec("UTF-8");

    //setting headers
    model->setHeaderData(model->fieldIndex("number"), Qt::Horizontal, tr("#"));
    model->setHeaderData(model->fieldIndex("date_in"), Qt::Horizontal, tr("Date"));
    model->setHeaderData(typeIdx, Qt::Horizontal, tr("Type"));
    model->setHeaderData(model->fieldIndex("product"), Qt::Horizontal, tr("Product"));
    model->setHeaderData(model->fieldIndex("called"), Qt::Horizontal, tr("Notified?"));
    model->setHeaderData(stateIdx, Qt::Horizontal, tr("State"));
    model->setHeaderData(masterIdx, Qt::Horizontal, tr("Master"));
    model->setHeaderData(acceptorIdx, Qt::Horizontal, tr("Acceptor"));
    model->setHeaderData(customerIdx, Qt::Horizontal, tr("Customer"));
    model->setHeaderData(model->fieldIndex("disease"), Qt::Horizontal, tr("Defect"));

    if (settings->value("orderstable/datee").toBool() == true){
        ui->tview->setColumnWidth(model->fieldIndex("date_in"), settings->value("orderstable/datew").toInt());}
                else ui->tview->hideColumn(model->fieldIndex("date_in"));
    if (settings->value("orderstable/statee").toBool() == true){
        ui->tview->setColumnWidth(stateIdx, settings->value("orderstable/statew").toInt());}
                else ui->tview->hideColumn(stateIdx);
    if (settings->value("orderstable/customere").toBool() == true){
        ui->tview->setColumnWidth(customerIdx, settings->value("orderstable/customerw").toInt());}
                else ui->tview->hideColumn(customerIdx);
    if (settings->value("orderstable/typee").toBool() == true){
        ui->tview->setColumnWidth(typeIdx, settings->value("orderstable/typew").toInt());}
                else ui->tview->hideColumn(typeIdx);
    if (settings->value("orderstable/producte").toBool() == true){
        ui->tview->setColumnWidth(model->fieldIndex("product"), settings->value("orderstable/productw").toInt());}
                else ui->tview->hideColumn(model->fieldIndex("product"));
    if (settings->value("orderstable/defecte").toBool() == true){
        ui->tview->setColumnWidth(model->fieldIndex("disease"), settings->value("orderstable/defectw").toInt());}
                else ui->tview->hideColumn(model->fieldIndex("disease"));
    if (settings->value("orderstable/acceptore").toBool() == true){
        ui->tview->setColumnWidth(acceptorIdx, settings->value("orderstable/acceptorw").toInt());}
                else ui->tview->hideColumn(acceptorIdx);
    if (settings->value("orderstable/mastere").toBool() == true){
        ui->tview->setColumnWidth(masterIdx, settings->value("orderstable/masterw").toInt());}
                else ui->tview->hideColumn(masterIdx);
    if (settings->value("orderstable/notifiede").toBool() == true){
        ui->tview->setColumnWidth(model->fieldIndex("called"), settings->value("orderstable/notifiedw").toInt());}
                else ui->tview->hideColumn(model->fieldIndex("called"));

    //hiding unneeded columns
    ui->tview->hideColumn(model->fieldIndex("date_out"));
    ui->tview->hideColumn(model->fieldIndex("serial"));
    ui->tview->hideColumn(giverIdx);
    ui->tview->hideColumn(model->fieldIndex("warranty"));
    ui->tview->hideColumn(model->fieldIndex("comment"));
    ui->tview->hideColumn(model->fieldIndex("phone"));
    ui->tview->hideColumn(model->fieldIndex("cond"));
    ui->tview->hideColumn(model->fieldIndex("complect"));
    ui->tview->hideColumn(model->fieldIndex("cost"));
    ui->tview->hideColumn(model->fieldIndex("date_called"));
    ui->tview->hideColumn(model->fieldIndex("prepay"));

    ui->tview->setColumnWidth(model->fieldIndex("number"), 50);

    ui->tview->verticalHeader()->setDefaultSectionSize(24);
    ui->tview->verticalHeader()->hide();
    ui->tview->horizontalHeader()->show();
    ui->tview->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->datenotify->setDate(QDate::currentDate());

    if(MainWindow::isadmin)
        ui->bDelete->setDisabled(false);
}


void OrdersWidgetMain::on_rbAll_clicked(bool checked){
    if (checked){
        ui->lSearch->clear();
        ui->searchtexttype->setCurrentIndex(0);
        model->setSort(model->fieldIndex("number"),Qt::DescendingOrder);
        model->setFilter("number >= " + MainWindow::showlimit);
        model->select();
    }
}

void OrdersWidgetMain::on_rbCompleted_clicked(bool checked){
    if (checked){
        model->setSort(model->fieldIndex("number"),Qt::DescendingOrder);
        model->setFilter("state IN (3, 4, 5, 6, 18) AND number >= " + MainWindow::showlimit);
    }
}

void OrdersWidgetMain::on_rbAccepted_clicked(bool checked){
    if (checked){
        model->setSort(model->fieldIndex("number"),Qt::DescendingOrder);
        if (MainWindow::limitallfilters)
            model->setFilter("state IN (1, 2, 12, 13, 19, 20, 21) AND number >= " + MainWindow::showlimit);
        else
            model->setFilter("state IN (1, 2, 12, 13, 19, 20, 21)");
    }
}

void OrdersWidgetMain::on_rbConsent_clicked(bool checked){
    if (checked){
        model->setSort(model->fieldIndex("number"),Qt::DescendingOrder);
        if (MainWindow::limitallfilters)
            model->setFilter("state IN (7, 8) AND number >= " + MainWindow::showlimit);
        else
            model->setFilter("state IN (7, 8)");
    }
}

void OrdersWidgetMain::on_rbWaitSpares_clicked(bool checked){
    if (checked){
        model->setSort(model->fieldIndex("number"),Qt::DescendingOrder);
        if (MainWindow::limitallfilters)
            model->setFilter("state IN (14, 15, 16, 17) AND number >= " + MainWindow::showlimit);
        else
            model->setFilter("state IN (14, 15, 16, 17)");
    }
}

void OrdersWidgetMain::on_rbCall_clicked(bool checked){
    if (checked){
        model->setSort(model->fieldIndex("number"),Qt::AscendingOrder);
        if (MainWindow::limitallfilters)
            model->setFilter("state IN (4,5,6,7,20) AND called = 0 AND number >= " + MainWindow::showlimit);
        else
            model->setFilter("state IN (4,5,6,7,20) AND called = 0");
    }
}

void OrdersWidgetMain::on_searchbydate_clicked()
{
    model->setSort(model->fieldIndex("number"),Qt::AscendingOrder);
    model->setFilter("CAST(date_in as DATE) BETWEEN '" + ui->datestart->date().toString("yyyy-MM-dd") + "' AND '" + ui->dateend->date().toString("yyyy-MM-dd") + "'");
    model->select();
}


void OrdersWidgetMain::on_lSearch_returnPressed(){
    searchByField();}

void OrdersWidgetMain::searchByField()
{
    model->setFilter(QString());
    if(ui->lSearch->text() != ""){
        if(ui->searchtexttype->currentText() == tr("Order #"))
            model->setFilter("number = " + ui->lSearch->text());
        if(ui->searchtexttype->currentText() == tr("Name"))        {
            model->setFilter("relTblAl_5.name LIKE '%" + ui->lSearch->text() + "%'");
        }
    }
}

void OrdersWidgetMain::on_tview_clicked(const QModelIndex &index){
    int row = index.row();
    const QAbstractItemModel * mdl = index.model();
    currentID = mdl->data(mdl->index(row, 0), Qt::DisplayRole).toString();
    MainWindow::currentOrderID = currentID;
    qDebug() << "orderID: " << currentID;
}

void OrdersWidgetMain::on_dialog_closed(){
    model->select();}

void OrdersWidgetMain::on_reconnect_recieved(){
    initModelOrders();
    readUiSettings();
}

void OrdersWidgetMain::on_bSubmit_clicked()
{
    q.clear();
    q.exec("SELECT id FROM employees WHERE name = '" + ui->eMaster->currentText() + "'");
    q.first();
    QString employee = q.value(0).toString();
    q.clear();
    q.exec("SELECT id FROM states WHERE name = '" + ui->eState->currentText() + "'");
    q.first();
    QString state = q.value(0).toString();
    q.clear();
    q.prepare("INSERT INTO orders_log SET date = :date, orderid = :orderid, operation = :operation, state = :state, employee = :employee, comment = :comment");
    q.bindValue(":date", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    q.bindValue(":orderid", ui->dNumber->text());
    q.bindValue(":operation", tr("Order status changed"));
    q.bindValue(":employee", employee);
    q.bindValue(":state", state);
    q.bindValue(":comment", ui->dComment->toPlainText());
    q.exec();
    q.clear();
    model->submitAll();
}

void OrdersWidgetMain::showEditOrder(){
    EditOrder *ord = new EditOrder();
    connect(this, SIGNAL(sendMode(QString, QString)), ord, SLOT(getMode(QString, QString)));
    connect(ord,SIGNAL(orderSubmited()), this, SLOT(on_dialog_closed()));
    ord->show();}

void OrdersWidgetMain::on_bView_clicked(){
    showEditOrder();
    emit sendMode("view", currentID);}

void OrdersWidgetMain::on_bEdit_clicked(){
    showEditOrder();
    emit sendMode("edit", currentID);}

void OrdersWidgetMain::on_bDelete_clicked()
{
    QMessageBox mb;
    mb.setWindowTitle(tr("Caution!"));
    mb.setText(tr("Are you sure to delete order?"));
    QPushButton *bYes = mb.addButton(tr("Yes"), QMessageBox::ActionRole);
    QPushButton *bNo = mb.addButton(tr("No"), QMessageBox::RejectRole);
    mb.setDefaultButton(bNo);
    mb.exec();

    if (mb.clickedButton() == bYes){
        QItemSelectionModel *sm = ui->tview->selectionModel();
        if (sm->hasSelection()){
            model->removeRow(sm->selectedRows().first().row());
            model->submitAll();
            model->select();
        }
    if (mb.clickedButton() == bNo)
        mb.close();
    }
}

void OrdersWidgetMain::on_eCalled_stateChanged(int state)
{
    if (state == 0){
        ui->datenotify->setDate(QDate::currentDate());
        ui->datenotify->setEnabled(false);}
    if (state == 2){
        ui->datenotify->setEnabled(true);}
}
