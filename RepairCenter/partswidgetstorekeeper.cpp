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
//    ordStateIdx = model->fieldIndex("orderid");
    //setting relations
    model->setRelation(reqStateIdx, QSqlRelation("pr_states","id","name"));
    model->setRelation(masterIdx, QSqlRelation("employees","id","name"));

    model->setSort(model->fieldIndex("id"),Qt::DescendingOrder);  //setting default sorting

//    model->relationModel(model->fieldIndex("master"))->setFilter("position_type = 1 AND isactive = 1");

//setting tableview widget
    ui->tview->setModel(model);

//setting mapper & relations for right panel
    ui->eRequestState->setModel(model->relationModel(reqStateIdx));
    ui->eRequestState->setModelColumn(model->relationModel(reqStateIdx)->fieldIndex("name"));
    ui->eRequestState->model()->sort(2, Qt::AscendingOrder);

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
//    settings = new QSettings(QCoreApplication::applicationDirPath()+"/settings.conf",QSettings::IniFormat);
//    settings->setIniCodec("UTF-8");

    //setting headers
    model->setHeaderData(model->fieldIndex("id"), Qt::Horizontal, tr("#"));
    model->setHeaderData(model->fieldIndex("date"), Qt::Horizontal, tr("Date"));
    model->setHeaderData(model->fieldIndex("oederid"), Qt::Horizontal, tr("Order #"));
    model->setHeaderData(reqStateIdx, Qt::Horizontal, tr("State"));
    model->setHeaderData(masterIdx, Qt::Horizontal, tr("Master"));
    model->setHeaderData(model->fieldIndex("comment"), Qt::Horizontal, tr("Comment"));
    model->setHeaderData(model->fieldIndex("summ"), Qt::Horizontal, tr("Sum"));

    //hiding unneeded columns
    ui->tview->hideColumn(model->fieldIndex("spares"));
    ui->tview->hideColumn(model->fieldIndex("quants"));
    ui->tview->hideColumn(model->fieldIndex("ssearchbyfieldparesnew"));

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

void PartsWidgetStorekeeper::on_searchbyfield_clicked(){
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

    q.exec("SELECT state FROM orders WHERE number = " + orderID);
    rec = q.record();
    q.first();
    idx_s = ui->eOrderState->model()->match(ui->eOrderState->model()->index(0, 0), Qt::EditRole, q.value(rec.indexOf("state")), 1, Qt::MatchExactly);
    ui->eOrderState->setCurrentIndex(idx_s.value(0).row());
    orderState = ui->eOrderState->currentIndex();
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
    newOrderState = ui->eOrderState->currentIndex();
    if (newOrderState != orderState)
    {
        rec_s = model_s->record(ui->eOrderState->currentIndex());
        id_s = rec_s.value(rec_s.indexOf("id")).toString();
        q.exec("UPDATE orders SET state = " + id_s +" WHERE number = " + orderID);
        qDebug()<<"order state changed";
    }
    model->submitAll();
    calculateSumm();
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
    summ = 0;
    q.exec("SELECT summ FROM part_requests WHERE state IN (2, 5)");
    q.first();
    do
    {
        summ += q.value(0).toDouble();
        qDebug() << q.value(0).toDouble();
    }
    while (q.next());
    ui->lToPay->setText("<b>" + QString::number(summ,'f',2) + "</b>");
}
