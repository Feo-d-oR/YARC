#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "editorder.h"
#include "giveorder.h"
#include "giveorderdiag.h"
#include "createdbdialog.h"
#include "settings.h"
#include "catemployees.h"
#include "catproducttypes.h"
#include "catcustomers.h"
#include "catspares.h"
#include "catsparetypes.h"
#include "catworktypes.h"
#include "jrndiagreports.h"
#include "editdiagreport.h"
#include "jrnworkreports.h"
#include "editworkreport.h"
#include "printhwdocuments.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
//init database
    if (checkSettings()) {
        if (dbConnect())
            initModelOrders();
        else{
            QMessageBox mb;
            mb.setIcon(QMessageBox::Critical);
            mb.setWindowTitle(tr("RepairCenter"));
            mb.setText(tr("База данных не найдена!"));
            mb.setInformativeText(tr("Изменить настройки или создать новую?"));
            QPushButton *bCreate = mb.addButton(tr("Создать"), QMessageBox::ActionRole);
            QPushButton *bEdit = mb.addButton(tr("Изменить"), QMessageBox::ActionRole);
            QPushButton *bCancel = mb.addButton(tr("Отмена"), QMessageBox::RejectRole);
            mb.setDefaultButton(bEdit);
            mb.exec();

            if (mb.clickedButton() == bCreate){
                CreateDBDialog* cdb = new CreateDBDialog();
                cdb->show();
            }
            if (mb.clickedButton() == bEdit){
                Settings* sdb = new Settings();
                sdb->show();
            }
            if (mb.clickedButton() == bCancel)
                close();
        }
    }
    else{
        QMessageBox mb;
        mb.setIcon(QMessageBox::Critical);
        mb.setWindowTitle(tr("RepairCenter"));
        mb.setText(tr("Файл настроек не найден!"));
        mb.setInformativeText(tr("Создать файл настроек?"));
        QPushButton *bEdit = mb.addButton(tr("Создать"), QMessageBox::ActionRole);
        QPushButton *bCancel = mb.addButton(tr("Отмена"), QMessageBox::RejectRole);
        mb.setDefaultButton(bEdit);
        mb.exec();

        if (mb.clickedButton() == bEdit){
            Settings* sdb = new Settings();
            sdb->show();
        }
        if (mb.clickedButton() == bCancel)
            close();
    }

    ui->dateend->setDate(QDate::currentDate());
}

MainWindow::~MainWindow(){
    delete ui; }

bool MainWindow::checkSettings()
{
    settings = new QSettings(QCoreApplication::applicationDirPath()+"/settings.conf",QSettings::IniFormat);
    settings->setIniCodec("UTF-8");
    if (settings->contains("mysql/hostname"))
        return true;
    else
        return false;

}

bool MainWindow::dbConnect()
{
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName(settings->value("mysql/hostname").toString());
        db.setPort(settings->value("mysql/port").toInt());
        db.setDatabaseName(settings->value("mysql/database").toString());
        db.setUserName(settings->value("mysql/user").toString());
        db.setPassword(settings->value("mysql/password").toString());
        if (db.open())
            return true;
        else
            return false;
        return false;
}

void MainWindow::initModelOrders()
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
    model->setRelation(typeIdx, QSqlRelation("product_types","id","name"));
    model->setRelation(customerIdx, QSqlRelation("customers","id","name"));
    model->setRelation(model->fieldIndex("phone"), QSqlRelation("customers","id","phone"));

    model->setSort(model->fieldIndex("number"),Qt::DescendingOrder);  //setting default sorting

    model->relationModel(model->fieldIndex("master"))->setFilter("position_type = 1");

//setting tableview widget
    ui->tview->setModel(model);

    //setting headers
    model->setHeaderData(model->fieldIndex("number"), Qt::Horizontal, tr("№"));
    model->setHeaderData(model->fieldIndex("date_in"), Qt::Horizontal, tr("Дата"));
    model->setHeaderData(typeIdx, Qt::Horizontal, tr("Тип"));
    model->setHeaderData(model->fieldIndex("product"), Qt::Horizontal, tr("Изделие"));
    model->setHeaderData(stateIdx, Qt::Horizontal, tr("Статус"));
    model->setHeaderData(masterIdx, Qt::Horizontal, tr("Мастер"));

    //hiding unneeded columns
    ui->tview->hideColumn(model->fieldIndex("date_out"));
    ui->tview->hideColumn(model->fieldIndex("serial"));
    ui->tview->hideColumn(acceptorIdx);
    ui->tview->hideColumn(giverIdx);
    ui->tview->hideColumn(customerIdx);
    ui->tview->hideColumn(model->fieldIndex("disease"));
    ui->tview->hideColumn(model->fieldIndex("warranty"));
    ui->tview->hideColumn(model->fieldIndex("comment"));
    ui->tview->hideColumn(model->fieldIndex("phone"));
    ui->tview->hideColumn(model->fieldIndex("cond"));
    ui->tview->hideColumn(model->fieldIndex("complect"));
    ui->tview->hideColumn(model->fieldIndex("cost"));

    //setting column properties
    ui->tview->setColumnWidth(model->fieldIndex("number"),50);
    ui->tview->setColumnWidth(model->fieldIndex("date_in"),100);
    ui->tview->setColumnWidth(customerIdx,100);
    ui->tview->setColumnWidth(typeIdx,120);
    ui->tview->setColumnWidth(model->fieldIndex("product"),160);
    ui->tview->setColumnWidth(stateIdx,210);
    ui->tview->setColumnWidth(masterIdx,100);

    ui->tview->verticalHeader()->setDefaultSectionSize(24);
    ui->tview->verticalHeader()->hide();
    ui->tview->horizontalHeader()->show();
    ui->tview->setEditTriggers(QAbstractItemView::NoEditTriggers);

//setting mapper & relations for right panel
    ui->eState->setModel(model->relationModel(stateIdx));
    ui->eState->setModelColumn(model->relationModel(stateIdx)->fieldIndex("name"));
    ui->eState->model()->sort(2, Qt::AscendingOrder);

    ui->eMaster->setModel(model->relationModel(masterIdx));
    ui->eMaster->setModelColumn(model->relationModel(masterIdx)->fieldIndex("name"));
    ui->eMaster->model()->sort(1, Qt::AscendingOrder);

    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->setItemDelegate(new QSqlRelationalDelegate(this));
    mapper->addMapping(ui->dNumber, model->fieldIndex("number"));
    mapper->addMapping(ui->dDateIn, model->fieldIndex("date_in"));
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

    model->select();
//    ui->tview->setCurrentIndex(model->index(0, 0));
}

void MainWindow::on_rbAll_clicked(bool checked){
    if (checked)
        ui->lSearch->clear();
        ui->searchtexttype->setCurrentIndex(0);
        model->setSort(model->fieldIndex("number"),Qt::DescendingOrder);
        model->setFilter(QString());
        model->select();
}

void MainWindow::on_rbCompleted_clicked(bool checked){
    if (checked)
        model->setSort(model->fieldIndex("number"),Qt::DescendingOrder);
        model->setFilter("state IN (3, 4, 5, 6, 18)");
}

void MainWindow::on_rbAccepted_clicked(bool checked){
    if (checked)
        model->setSort(model->fieldIndex("number"),Qt::DescendingOrder);
        model->setFilter("state IN (1, 2, 12, 13, 19)");
}

void MainWindow::on_rbConsent_clicked(bool checked){
    if (checked)
        model->setSort(model->fieldIndex("number"),Qt::DescendingOrder);
        model->setFilter("state IN (7, 8)");
}

void MainWindow::on_rbWaitSpares_clicked(bool checked){
    if (checked)
        model->setSort(model->fieldIndex("number"),Qt::DescendingOrder);
        model->setFilter("state IN (14, 15, 16, 17)");
}

void MainWindow::on_searchbydate_clicked()
{
    model->setSort(model->fieldIndex("number"),Qt::AscendingOrder);
    model->setFilter("CAST(date_in as DATE) BETWEEN '" + ui->datestart->date().toString("yyyy-MM-dd") + "' AND '" + ui->dateend->date().toString("yyyy-MM-dd") + "'");
    model->select();
}

//void MainWindow::getCustomerIds()
//{
//    QStringList list;
//    QSqlQuery q;
//    q.exec("SELECT * FROM customers WHERE name LIKE '%" + ui->lSearch->text() + "%'");
//    q.first();
//    list.append(q.value(0).toString());
//    while (q.next())
//    { list.append(q.value(0).toString()); }
//    namesstr = list.join("','");
//    qDebug() << "list:" << list;
//    qDebug() << "string:" << namesstr;
//}

void MainWindow::on_lSearch_textEdited(const QString &arg1)
{
    model->setFilter(QString());
    if(ui->lSearch->text() != ""){
        if(ui->searchtexttype->currentText() == tr("Номер квитанции"))
            model->setFilter("number = " + arg1);
        if(ui->searchtexttype->currentText() == tr("Имя"))        {
//            getCustomerIds();
//            model->setFilter("customer IN ('" + namesstr + "')");
            model->setFilter("relTblAl_5.name LIKE '%" + arg1 + "%'");
            qDebug() << "filter:" << model->filter();
        }
    }
}

void MainWindow::on_mInit_triggered()
{
    if (dbConnect()) {
        initModelOrders();
    }
    else{
        QMessageBox::critical(this, tr("RepairCenter"), tr("Не удалось подключиться к базе данных."));
    }
}

void MainWindow::on_bDelete_clicked()
{
    QMessageBox mb;
    mb.setWindowTitle(tr("Внимание!"));
    mb.setText(tr("Действительно удалить запись?"));
    QPushButton *bYes = mb.addButton(tr("Да"), QMessageBox::ActionRole);
    QPushButton *bNo = mb.addButton(tr("Нет"), QMessageBox::RejectRole);
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

void MainWindow::on_tview_clicked(const QModelIndex &index){
    int row = index.row();
    const QAbstractItemModel * mdl = index.model();
    currentID = mdl->data(mdl->index(row, 0), Qt::DisplayRole).toString();
    qDebug() << "orderID: " << currentID;
}

void MainWindow::on_dialog_closed(){
    model->select();}

void MainWindow::on_exit_triggered(){
    close();
}

void MainWindow::on_bSubmit_clicked(){
    model->submitAll();}

void MainWindow::showEditOrder(){
    EditOrder *ord = new EditOrder();
    connect(this, SIGNAL(sendMode(QString, QString)), ord, SLOT(getMode(QString, QString)));
    connect(ord,SIGNAL(orderSubmited()), this, SLOT(on_dialog_closed()));
    ord->show();}

void MainWindow::on_mNewOrder_triggered(){
    showEditOrder();
    emit sendMode("new", "0");}

void MainWindow::on_bView_clicked(){
    showEditOrder();
    emit sendMode("view", currentID);}

void MainWindow::on_bEdit_clicked(){
    showEditOrder();
    emit sendMode("edit", currentID);}

void MainWindow::on_mEmployees_triggered(){
    CatEmployees* ce = new CatEmployees();
    ce->show();}

void MainWindow::on_mCreatedb_triggered(){
    CreateDBDialog* cdb = new CreateDBDialog();
    cdb->show();}

void MainWindow::on_mSettings_triggered(){
    Settings* sdb = new Settings();
    sdb->show();}

void MainWindow::on_mProductTypes_triggered(){
    CatProductTypes* cptype = new CatProductTypes();
    cptype->show();}

void MainWindow::on_mCustomers_triggered(){
    CatCustomers* ccust = new CatCustomers();
    ccust->show();}

void MainWindow::on_mSpares_triggered(){
    CatSpares* csp = new CatSpares();
    csp->show();}

void MainWindow::on_mSpareTypes_triggered(){
    CatSpareTypes* cst = new CatSpareTypes();
    cst->show();}

void MainWindow::on_mWorkTypes_triggered(){
    CatWorkTypes* cwt = new CatWorkTypes();
    cwt->show();}

void MainWindow::on_mJrnWorkReports_triggered(){
    JrnWorkReports* jwr = new JrnWorkReports();
    jwr->show();}

void MainWindow::showEditWorkReport(){
    EditWorkReport *ewr = new EditWorkReport();
    connect(this, SIGNAL(sendMode(QString, QString)), ewr, SLOT(getMode(QString, QString)));
    ewr->show();}

void MainWindow::on_mNewWorkReport_triggered(){
    showEditWorkReport();
    emit sendMode("new", currentID);}

void MainWindow::showGiveOrder(){
    GiveOrder *gor = new GiveOrder();
    connect(this, SIGNAL(sendMode(QString, QString)), gor, SLOT(getMode(QString, QString)));
    connect(gor,SIGNAL(orderSubmited()), this, SLOT(on_dialog_closed()));
    gor->show();}

void MainWindow::on_mGiveOrder_triggered(){
    showGiveOrder();
    emit sendMode("new", currentID);}

void MainWindow::on_mAbout_triggered()
{
    QMessageBox mb;
    mb.setWindowTitle(tr("О программе..."));
    mb.setTextFormat(Qt::RichText);
    mb.setText("RepairCenter ver. 0.2b");
    mb.setInformativeText("<a href = 'http://sourceforge.net/projects/repaircenter/'>RepairCenter on SourceForge</a> \n "
                          "<a href = 'http://sourceforge.net/projects/qtrpt/'>QtRPT 1.4.5</a>");
    QPushButton *bOk = mb.addButton("OK", QMessageBox::AcceptRole);
    mb.setDefaultButton(bOk);
    mb.exec();
    if (mb.clickedButton() == bOk)
        mb.close();
}

void MainWindow::on_mJrnDiagReports_triggered(){
    JrnDiagReports* jdr = new JrnDiagReports();
    jdr->show();}

void MainWindow::on_mNewDiagReport_triggered(){
    showEditDiagReport();
    emit sendMode("new", currentID);}

void MainWindow::showEditDiagReport(){
    EditDiagReport * edr = new EditDiagReport();
    connect(this, SIGNAL(sendMode(QString, QString)), edr, SLOT(getMode(QString, QString)));
    edr->show();}

void MainWindow::on_mGiveOrderDiag_triggered(){
    showGiveOrderDiag();
    emit sendMode("new", currentID);}

void MainWindow::showGiveOrderDiag(){
    GiveOrderDiag * god = new GiveOrderDiag();
    connect(this, SIGNAL(sendMode(QString, QString)), god, SLOT(getMode(QString, QString)));
    connect(god,SIGNAL(orderSubmited()), this, SLOT(on_dialog_closed()));
    god->show();}

void MainWindow::reject(){
    return; }

void MainWindow::closeEvent(QCloseEvent *event){
    QApplication::closeAllWindows();
    event->accept(); }

void MainWindow::on_mHelp_triggered(){
    QDesktopServices::openUrl(QUrl("file://"+QCoreApplication::applicationDirPath()+"/help/RU_ru/index.html"));
}

void MainWindow::on_mPrintHWDocs_triggered(){
    PrintHWDocuments * phwd = new PrintHWDocuments();
    phwd->show();}
