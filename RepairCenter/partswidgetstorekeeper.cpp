#include "partswidgetstorekeeper.h"
#include "ui_partswidgetstorekeeper.h"
#include "mainwindow.h"
#include "editpartsrequest.h"

PartsWidgetStorekeeper::PartsWidgetStorekeeper(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PartsWidgetStorekeeper)
{
    ui->setupUi(this);
    initModelRequests();
    initModels();
    readUiSettings();
    calculateSumm();
    updateTimer();
}

PartsWidgetStorekeeper::~PartsWidgetStorekeeper()
{
    delete ui;
}

void PartsWidgetStorekeeper::initModelRequests()
{
//setting table model
    model = new QSqlRelationalTableModel(ui->tview);
    model->setJoinMode(QSqlRelationalTableModel::LeftJoin); //some fields will be NULL, so we need it
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("part_requests");
    //remember column indexes
    reqStateIdx = model->fieldIndex("state");
    masterIdx = model->fieldIndex("master");
    //setting relations
    model->setRelation(reqStateIdx, QSqlRelation("pr_states","id","name"));
    model->setRelation(masterIdx, QSqlRelation("employees","id","name"));

    model->setSort(model->fieldIndex("id"),Qt::DescendingOrder);  //setting default sorting

//setting tableview widget
    ui->tview->setModel(model);

//setting mapper & relations for right panel
    ui->eRequestState->setModel(model->relationModel(reqStateIdx));
    ui->eRequestState->setModelColumn(model->relationModel(reqStateIdx)->fieldIndex("name"));
    ui->eRequestState->model()->sort(1, Qt::AscendingOrder);

    ui->eMaster->setModel(model->relationModel(masterIdx));
    ui->eMaster->setModelColumn(model->relationModel(masterIdx)->fieldIndex("name"));
    ui->eMaster->model()->sort(1, Qt::AscendingOrder);

    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->setItemDelegate(new QSqlRelationalDelegate(this));
    mapper->addMapping(ui->eId, model->fieldIndex("id"));
    mapper->addMapping(ui->eDate, model->fieldIndex("date"));
    mapper->addMapping(ui->eRequestState, reqStateIdx);
    mapper->addMapping(ui->eOrderId, model->fieldIndex("orderid"));
    mapper->addMapping(ui->eMaster, masterIdx);
    mapper->addMapping(ui->eComment, model->fieldIndex("comment"));
    mapper->addMapping(ui->eSumm, model->fieldIndex("summ"));

    connect(ui->tview->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            mapper, SLOT(setCurrentModelIndex(QModelIndex)));
    model->setFilter("orderid >= " + MainWindow::showlimit);
    model->select();
}

void PartsWidgetStorekeeper::initModels()
{
    model_m = new QSqlQueryModel();
    model_m->setQuery("SELECT id, name FROM employees WHERE position_type = '1' AND isactive = '1'");
    ui->cbSearchMaster->setModel(model_m);
    ui->cbSearchMaster->setModelColumn(1);
    ui->cbSearchMaster->model()->sort(1, Qt::AscendingOrder);

    model_s = new QSqlQueryModel();
    model_s->setQuery("SELECT id, name FROM states");
    ui->eOrderState->setModel(model_s);
    ui->eOrderState->setModelColumn(1);
    ui->eOrderState->model()->sort(1, Qt::AscendingOrder);
}

void PartsWidgetStorekeeper::readUiSettings()
{
    settings = new QSettings(QCoreApplication::applicationDirPath()+"/repaircenter.conf",QSettings::IniFormat);
    settings->setIniCodec("UTF-8");

    //setting headers
    model->setHeaderData(model->fieldIndex("id"), Qt::Horizontal, tr("#"));
    model->setHeaderData(model->fieldIndex("date"), Qt::Horizontal, tr("Date"));
    model->setHeaderData(model->fieldIndex("orderid"), Qt::Horizontal, tr("Order #"));
    model->setHeaderData(reqStateIdx, Qt::Horizontal, tr("State"));
    model->setHeaderData(masterIdx, Qt::Horizontal, tr("Master"));
    model->setHeaderData(model->fieldIndex("comment"), Qt::Horizontal, tr("Comment"));
    model->setHeaderData(model->fieldIndex("summ"), Qt::Horizontal, tr("Sum"));

    if (settings->value("orderstable/datee").toBool() == true){
        ui->tview->setColumnWidth(model->fieldIndex("date"), settings->value("orderstable/datew").toInt());}
                else ui->tview->hideColumn(model->fieldIndex("date"));
    if (settings->value("orderstable/statee").toBool() == true){
        ui->tview->setColumnWidth(reqStateIdx, settings->value("orderstable/statew").toInt());}
                else ui->tview->hideColumn(reqStateIdx);
    if (settings->value("orderstable/ide").toBool() == true){
        ui->tview->setColumnWidth(model->fieldIndex("orderid"), settings->value("orderstable/idw").toInt());}
                else ui->tview->hideColumn(model->fieldIndex("orderid"));
    if (settings->value("orderstable/commente").toBool() == true){
        ui->tview->setColumnWidth(model->fieldIndex("comment"), settings->value("orderstable/commentw").toInt());}
                else ui->tview->hideColumn(model->fieldIndex("comment"));
    if (settings->value("orderstable/mastere").toBool() == true){
        ui->tview->setColumnWidth(masterIdx, settings->value("orderstable/masterw").toInt());}
                else ui->tview->hideColumn(masterIdx);
    if (settings->value("orderstable/sume").toBool() == true){
        ui->tview->setColumnWidth(model->fieldIndex("summ"), settings->value("orderstable/sumw").toInt());}
                else ui->tview->hideColumn(model->fieldIndex("summ"));


    //hiding unneeded columns
    ui->tview->hideColumn(model->fieldIndex("spares"));
    ui->tview->hideColumn(model->fieldIndex("quants"));
    ui->tview->hideColumn(model->fieldIndex("sparesnew"));

    ui->tview->setColumnWidth(model->fieldIndex("id"), 50);

    ui->tview->verticalHeader()->setDefaultSectionSize(24);
    ui->tview->verticalHeader()->hide();
    ui->tview->horizontalHeader()->show();
    ui->tview->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


void PartsWidgetStorekeeper::on_rbAll_clicked(bool checked){
    if (checked){
        ui->lSearch->clear();
        ui->cbSearchMaster->setCurrentIndex(-1);
        model->setSort(model->fieldIndex("id"),Qt::DescendingOrder);
        model->setFilter("orderid >= " + MainWindow::showlimit);
        model->select();
    }
}

void PartsWidgetStorekeeper::on_rbNew_clicked(bool checked){
    if (checked){
        model->setSort(model->fieldIndex("id"),Qt::DescendingOrder);
        if (MainWindow::limitallfilters)
            model->setFilter("state IN (1, 9) AND orderid >= " + MainWindow::showlimit);
        else
            model->setFilter("state IN (1, 9)");
    }
}

void PartsWidgetStorekeeper::on_rbActive_clicked(bool checked){
    if (checked){
        model->setSort(model->fieldIndex("id"),Qt::DescendingOrder);
        if (MainWindow::limitallfilters)
            model->setFilter("state IN (2, 4, 5, 6, 7) AND orderid >= " + MainWindow::showlimit);
        else
            model->setFilter("state IN (2, 4, 5, 6, 7)");
    }
}

void PartsWidgetStorekeeper::on_rbInfo_clicked(bool checked){
    if (checked){
        model->setSort(model->fieldIndex("id"),Qt::DescendingOrder);
        if (MainWindow::limitallfilters)
            model->setFilter("state IN (9, 10) AND orderid >= " + MainWindow::showlimit);
        else
            model->setFilter("state IN (9, 10)");
    }
}

void PartsWidgetStorekeeper::on_rbRecieve_clicked(bool checked){
    if (checked){
        model->setSort(model->fieldIndex("id"),Qt::DescendingOrder);
        if (MainWindow::limitallfilters)
            model->setFilter("state IN (6) AND orderid >= " + MainWindow::showlimit);
        else
            model->setFilter("state IN (6)");
    }
}

void PartsWidgetStorekeeper::on_rbGive_clicked(bool checked){
    if (checked){
        model->setSort(model->fieldIndex("id"),Qt::DescendingOrder);
        if (MainWindow::limitallfilters)
            model->setFilter("state IN (2, 7) AND orderid >= " + MainWindow::showlimit);
        else
            model->setFilter("state IN (2, 7)");
    }
}

void PartsWidgetStorekeeper::on_lSearch_returnPressed(){
    searchByField();}

void PartsWidgetStorekeeper::searchByField()
{
    model->setFilter(QString());
    if(ui->lSearch->text() != ""){
        if(ui->cbSearchType->currentText() == tr("Order #"))
            model->setFilter("orerid = " + ui->lSearch->text());
        if(ui->cbSearchType->currentText() == tr("Request #"))
            model->setFilter("id = " + ui->lSearch->text());
    }
}

void PartsWidgetStorekeeper::on_tview_clicked(const QModelIndex &index){
    int row = index.row();
    const QAbstractItemModel * mdl = index.model();
    orderID = mdl->data(mdl->index(row, 3), Qt::DisplayRole).toString();
    currentID = mdl->data(mdl->index(row, 0), Qt::DisplayRole).toString();
    MainWindow::currentOrderID = orderID;
    qDebug() << "orderID: " << orderID;

    q.exec("SELECT state, comment FROM orders WHERE number = " + orderID);
    rec = q.record();
    q.first();
    idx_s = ui->eOrderState->model()->match(ui->eOrderState->model()->index(0, 0), Qt::EditRole, q.value(rec.indexOf("state")), 1, Qt::MatchExactly);
    ui->eOrderState->setCurrentIndex(idx_s.value(0).row());
    ui->eOrderComment->setPlainText(q.value(rec.indexOf("comment")).toString());
//    orderState = ui->eOrderState->currentIndex();
}

void PartsWidgetStorekeeper::on_dialog_closed(){
    model->select();
    calculateSumm();
}

void PartsWidgetStorekeeper::on_reconnect_recieved(){
    qDebug()<<"reconnect";
    initModelRequests();
    initModels();
    readUiSettings();
    calculateSumm();
}

void PartsWidgetStorekeeper::on_bSubmit_clicked(){

    model->submitAll();
    calculateSumm();
}

void PartsWidgetStorekeeper::on_bSubmitOrder_clicked()
{
//    newOrderState = ui->eOrderState->currentIndex();
//    if (newOrderState != orderState)
//    {

    rec_s = model_s->record(ui->eOrderState->currentIndex());
    id_s = rec_s.value(rec_s.indexOf("id")).toString();
    q.clear();
    q.prepare("UPDATE orders SET state = :state, comment = :comment WHERE number = " + orderID);
    q.bindValue(":state", id_s);
    q.bindValue(":comment", ui->eOrderComment->toPlainText());
    q.exec();
    q.clear();
    q.prepare("INSERT INTO orders_log SET date = :date, orderid = :orderid, operation = :operation, state = :state, employee = :employee, comment = :comment");
    q.bindValue(":date", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    q.bindValue(":orderid", orderID);
    q.bindValue(":operation", tr("Status changed by storekeeper"));
    q.bindValue(":state", id_s.toInt());
    q.bindValue(":employee", MainWindow::userID);
    q.bindValue(":comment", ui->eOrderComment->toPlainText());
    q.exec();
    q.clear();

    qDebug()<<"order state changed";
//}

}


void PartsWidgetStorekeeper::on_cbSearchMaster_activated(int index)
{
    if (index != -1)
    {
//        model->setFilter(QString());
        QSqlRecord rec_m = model_m->record(index);
        QString id_m = rec_m.value(rec_m.indexOf("id")).toString();
        model->setFilter("master = '" + id_m + "'");
    }
}

void PartsWidgetStorekeeper::showEditPartsRequest(){
    EditPartsRequest *epr = new EditPartsRequest();
    connect(this, SIGNAL(sendMode(QString, QString)), epr, SLOT(getMode(QString, QString)));
    connect(epr,SIGNAL(requestSubmited()), this, SLOT(on_dialog_closed()));
    epr->show();}

void PartsWidgetStorekeeper::on_bView_clicked(){
    showEditPartsRequest();
    emit sendMode("view", currentID);}

void PartsWidgetStorekeeper::on_bEdit_clicked(){
    showEditPartsRequest();
    emit sendMode("edit", currentID);}

void PartsWidgetStorekeeper::on_bDelete_clicked()
{
    QMessageBox mb;
    mb.setWindowTitle(tr("Caution!"));
    mb.setText(tr("Are you sure to delete parts request?"));
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

void PartsWidgetStorekeeper::calculateSumm()
{
//    summ = 0;
//    q.exec("SELECT summ FROM part_requests WHERE state IN (2, 5)");
//    q.first();
//    do
//    {
//        summ += q.value(0).toDouble();
//        qDebug() << q.value(0).toDouble();
//    }
//    while (q.next());
//    ui->lToPay->setText("<b>" + QString::number(summ,'f',2) + "</b>");
}

void PartsWidgetStorekeeper::updateTimer()
{
    if (MainWindow::tableUpdateInterval != 0){
        QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(updateTable()));
        timer->start(MainWindow::tableUpdateInterval*1000); } //every X seconds
}

void PartsWidgetStorekeeper::updateTable()
{
    model->select();
}
