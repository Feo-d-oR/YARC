#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "editorder.h"
#include "giveorder.h"
#include "giveorderdiag.h"
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
#include "about.h"
#include "salaries.h"
#include "catsuppliers.h"
#include "editpartsrequest.h"
#include "jrnpartsrequests.h"
#include "orderslog.h"
#include "partsreqlog.h"

QString MainWindow::sLocale = "";
float MainWindow::sPercMast = 0;
float MainWindow::sPercAcc = 0;
float MainWindow::sPercFirm = 0;
int MainWindow::defAcceptor = -1;
int MainWindow::defMaster = -1;
int MainWindow::defState = -1;
int MainWindow::role = 0;
int MainWindow::userID = 0;
bool MainWindow::isadmin = 0;
bool MainWindow::masterCanEditSpares = 0;
bool MainWindow::masterCanEditWorks = 0;
bool MainWindow::acceptorCanEditDiag = 0;
bool MainWindow::acceptorCanEditWorks = 0;
bool MainWindow::acceptorCanEditSpares = 0;
bool MainWindow::productTypeM = 0;
bool MainWindow::productM = 0;
bool MainWindow::serialM = 0;
bool MainWindow::defectM = 0;
bool MainWindow::conditionM = 0;
bool MainWindow::completenessM = 0;
bool MainWindow::customerM = 0;
bool MainWindow::phoneM = 0;
QString MainWindow::prevCustomer = "";
QString MainWindow::defWarranty = "";
QString MainWindow::currentOrderID = "";
QString MainWindow::showlimit = "0";
bool MainWindow::limitallfilters = false;
int MainWindow::tableUpdateInterval = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    QStringList *zeroArg = new QStringList;
    ui->setupUi(this);

    crypto = SimpleCrypt(Q_UINT64_C(0xd3752f1e9b140689));

    if (checkSettings()) {
        if (dbConnect())
        {
            loadWindowState();
            readGlobalSettings();
            loadUserInterface();
            connTimer();
        }
        else{
            QMessageBox mb;
            mb.setIcon(QMessageBox::Critical);
            mb.setWindowTitle(tr("RepairCenter"));
            mb.setText(tr("Cannot connect to database!"));
            mb.setInformativeText(tr("Change settings or create new one?"));
            QPushButton *bCreate = mb.addButton(tr("Create"), QMessageBox::ActionRole);
            QPushButton *bEdit = mb.addButton(tr("Change"), QMessageBox::ActionRole);
            QPushButton *bCancel = mb.addButton(tr("Cancel"), QMessageBox::RejectRole);
            mb.setDefaultButton(bEdit);
            mb.exec();

            if (mb.clickedButton() == bCreate){
                if (QProcess::startDetached(QDir::toNativeSeparators(QCoreApplication::applicationDirPath()+"/DBTool"), *zeroArg))
                    QApplication::quit();
            }
            if (mb.clickedButton() == bEdit){
                Settings* sdb = new Settings();
//                sdb->setWindowFlags(sdb->windowFlags() | Qt::WindowStaysOnTopHint);
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
        mb.setText(tr("Settings file not found or incomplete!"));
        mb.setInformativeText(tr("Change settings?"));
        QPushButton *bEdit = mb.addButton(tr("Change"), QMessageBox::ActionRole);
        QPushButton *bCancel = mb.addButton(tr("Cancel"), QMessageBox::RejectRole);
        mb.setDefaultButton(bEdit);
        mb.exec();

        if (mb.clickedButton() == bEdit){
            Settings* sdb = new Settings();
//            sdb->setWindowFlags(sdb->windowFlags() | Qt::WindowStaysOnTopHint);
            sdb->show();
        }
        if (mb.clickedButton() == bCancel)
            close();
    }
}

MainWindow::~MainWindow(){
    delete ui; }

bool MainWindow::checkSettings()
{
    settings = new QSettings(QCoreApplication::applicationDirPath()+"/repaircenter.conf",QSettings::IniFormat);
    settings->setIniCodec("UTF-8");

    if (settings->contains("mysql/password"))
        return true;
    else{
        delete settings;
        return false;}
}

void MainWindow::readGlobalSettings()
{
    settings = new QSettings(QCoreApplication::applicationDirPath()+"/repaircenter.conf",QSettings::IniFormat);
    settings->setIniCodec("UTF-8");
    QSqlQuery q;

    sLocale = settings->value("locale/language").toString();
    defAcceptor = settings->value("defaults/acceptor").toInt();
    defMaster = settings->value("defaults/master").toInt();
    defState = settings->value("defaults/state").toInt();
    defWarranty = settings->value("defaults/warranty").toString();

    showlimit = settings->value("orderstable/showlimit").toString();
    limitallfilters = settings->value("orderstable/limitallfilters").toBool();
    tableUpdateInterval = settings->value("ui/tableupdateinterval").toInt();
    connCheckInterval = settings->value("mysql/conncheckinterval").toInt();

    QString username = settings->value("user/username").toString();
    QString password = settings->value("user/password").toString();
    q.exec(QString("SELECT id, position_type FROM employees WHERE username = '"+ username +"' AND password = '"+ crypto.decryptToString(password) +"'"));
    q.first();
    userID = q.value(0).toInt();
    role = q.value(1).toInt();
    qDebug()<<"role="<<role;

    q.exec("SELECT value_n FROM system WHERE name = 'percMaster'");
    q.first();
    sPercMast = q.value(0).toFloat();
    q.exec("SELECT value_n FROM system WHERE name = 'percAcceptor'");
    q.first();
    sPercAcc = q.value(0).toFloat();
    q.exec("SELECT value_n FROM system WHERE name = 'percFirm'");
    q.first();
    sPercFirm = q.value(0).toFloat();

    q.exec("SELECT value_n FROM system WHERE name = 'masterCanEditWorks'");
    q.first();
    masterCanEditWorks = q.value(0).toBool();
    q.exec("SELECT value_n FROM system WHERE name = 'masterCanEditSpares'");
    q.first();
    masterCanEditSpares = q.value(0).toBool();
    q.exec("SELECT value_n FROM system WHERE name = 'acceptorCanEditWorks'");
    q.first();
    acceptorCanEditWorks = q.value(0).toBool();
    q.exec("SELECT value_n FROM system WHERE name = 'acceptorCanEditSpares'");
    q.first();
    acceptorCanEditSpares = q.value(0).toBool();
    q.exec("SELECT value_n FROM system WHERE name = 'acceptorCanEditDiag'");
    q.first();
    acceptorCanEditDiag = q.value(0).toBool();

    q.exec("SELECT value_n FROM system WHERE name = 'productTypeM'");
    q.first();
    productTypeM = q.value(0).toBool();
    q.exec("SELECT value_n FROM system WHERE name = 'productM'");
    q.first();
    productM = q.value(0).toBool();
    q.exec("SELECT value_n FROM system WHERE name = 'serialM'");
    q.first();
    serialM = q.value(0).toBool();
    q.exec("SELECT value_n FROM system WHERE name = 'defectM'");
    q.first();
    defectM = q.value(0).toBool();
    q.exec("SELECT value_n FROM system WHERE name = 'conditionM'");
    q.first();
    conditionM = q.value(0).toBool();
    q.exec("SELECT value_n FROM system WHERE name = 'completenessM'");
    q.first();
    completenessM = q.value(0).toBool();
    q.exec("SELECT value_n FROM system WHERE name = 'customerM'");
    q.first();
    customerM = q.value(0).toBool();
    q.exec("SELECT value_n FROM system WHERE name = 'phoneM'");
    q.first();
    phoneM = q.value(0).toBool();
    q.clear();

}

void MainWindow::loadWindowState()
{
    if(settings->value("ui/mainwindowstate") == "max")
        QMainWindow::showMaximized();
    else if(settings->value("ui/mainwindowstate") == "full")
        QMainWindow::showFullScreen();
    else if(settings->value("ui/mainwindowstate") == "last")
        restoreGeometry(settings->value("ui/geometry").toByteArray());
//        restoreState(settings->value("ui/state").toByteArray())
    else return;
}

void MainWindow::loadUserInterface()
{
    if (role == 1) //if master
    {
        mainwidget = new OrdersWidgetMaster(this);
        ui->acceptorToolBar->hide();
        ui->storekeeperToolBar->hide();
        ui->adminToolBar->hide();
        ui->mEmployees->setDisabled(1);
        ui->mNewOrder->setDisabled(1);
        ui->mGiveOrder->setDisabled(1);
        ui->mGiveOrderDiag->setDisabled(1);
        ui->mPaySalaries->setDisabled(1);
        ui->mode->setDisabled(1);
        ui->mCustomers->setDisabled(1);
        if (!masterCanEditWorks)
            ui->mWorkTypes->setDisabled(1);
        if (!masterCanEditSpares){
            ui->mSpares->setDisabled(1);
            ui->mSpareTypes->setDisabled(1);
            ui->mSuppliers->setDisabled(1);}
    }
    else if (role == 2) //if acceptor
    {
        mainwidget = new OrdersWidgetMain(this);
        ui->masterToolBar->hide();
        ui->storekeeperToolBar->hide();
        ui->adminToolBar->hide();
        ui->mEmployees->setDisabled(1);
        ui->mPaySalaries->setDisabled(1);
        ui->mode->setDisabled(1);
        if (!acceptorCanEditWorks)
            ui->mNewWorkReport->setDisabled(1);
        if(!acceptorCanEditDiag)
            ui->mNewDiagReport->setDisabled(1);
        if (!acceptorCanEditSpares){
            ui->mSpares->setDisabled(1);
            ui->mSpareTypes->setDisabled(1);
            ui->mSuppliers->setDisabled(1);}
    }
    else if (role == 3) //if storekeeper
    {
        mainwidget = new PartsWidgetStorekeeper(this);
        ui->acceptorToolBar->hide();
        ui->masterToolBar->hide();
        ui->adminToolBar->hide();
        ui->mode->setDisabled(1);
        ui->mode->setDisabled(1);
        ui->mEmployees->setDisabled(1);
        ui->mPaySalaries->setDisabled(1);
        ui->acceptorToolBar->hide();
        ui->mEmployees->setDisabled(1);
        ui->mNewOrder->setDisabled(1);
        ui->mNewWorkReport->setDisabled(1);
        ui->mNewDiagReport->setDisabled(1);
        ui->mGiveOrder->setDisabled(1);
        ui->mGiveOrderDiag->setDisabled(1);
        ui->mPaySalaries->setDisabled(1);
        ui->mCustomers->setDisabled(1);
    }
//    else if (role == 4) //if director
//    {
//    }
    else if (role == 5) //if admin
    {
        isadmin = true;
        if (settings->value("ui/adminmode") == "acceptor")
            mainwidget = new OrdersWidgetMain(this);
        else if (settings->value("ui/adminmode") == "storekeeper")
            mainwidget = new PartsWidgetStorekeeper(this);
        else if (settings->value("ui/adminmode") == "master")
            mainwidget = new OrdersWidgetMaster(this);
        else
            mainwidget = new OrdersWidgetMain(this);
    }
    else
    {
        ui->catalogs->setDisabled(1);
        ui->actions->setDisabled(1);
        ui->journals->setDisabled(1);
        ui->mode->setDisabled(1);
        ui->acceptorToolBar->setDisabled(1);
        ui->masterToolBar->setDisabled(1);
        ui->storekeeperToolBar->setDisabled(1);
        ui->adminToolBar->setDisabled(1);
    }

//    connect(this, SIGNAL(sendReconnect()), mainwidget, SLOT(on_reconnect_recieved()));
    setCentralWidget(mainwidget);
}

bool MainWindow::dbConnect()
{
    db.close();
        db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName(settings->value("mysql/hostname").toString());
        db.setPort(settings->value("mysql/port").toInt());
        db.setDatabaseName(settings->value("mysql/database").toString());
        db.setUserName(settings->value("mysql/user").toString());
        QString pass = settings->value("mysql/password").toString();
        db.setPassword(crypto.decryptToString(pass));
        if (db.open())
        {
            q = QSqlQuery(db);
            q.exec("SET SESSION sql_mode = ''"); //disabling strict mode for easier life ;)
            return true;
        }
        else
            return false;
        return false;
}


void MainWindow::on_mInit_triggered()
{
    if(dbConnect()){
        readGlobalSettings();
        loadUserInterface();
//        emit sendReconnect();
    }
    else{
        QMessageBox::critical(this, tr("RepairCenter"), tr("Unable to connect to database!"));
    }
}

void MainWindow::on_exit_triggered(){
    close();
}

void MainWindow::connTimer()
{
    if(connCheckInterval != 0){
        QTimer *timer = new QTimer(this);
        qDebug()<<"connCheckInterval"<<connCheckInterval*1000;
        connect(timer, SIGNAL(timeout()), this, SLOT(checkDBconnection()));
        timer->start(connCheckInterval*1000);} //every X seconds
}

void MainWindow::checkDBconnection()
{
    qDebug()<<"checking DB connection";
    q.exec("SELECT value_n FROM system WHERE name = 'dbversion'");
    q.first();
    dbversion = q.value(0).toInt();
    q.clear();
    if (dbversion == 0)
    {            qDebug() << "connection lost";
            QMessageBox::critical(this, tr("RepairCenter"), tr("Database connection is lost!"));
    }
    else return;
}

void MainWindow::showEditOrder(){
    EditOrder *ord = new EditOrder();
    connect(this, SIGNAL(sendMode(QString, QString)), ord, SLOT(getMode(QString, QString)));
    connect(ord,SIGNAL(orderSubmited()), mainwidget, SLOT(on_dialog_closed()));
//    ord->setWindowFlags(ord->windowFlags() | Qt::WindowStaysOnTopHint);
    ord->show();}

void MainWindow::on_mNewOrder_triggered(){
    showEditOrder();
    emit sendMode("new", "0");}

void MainWindow::on_mEmployees_triggered(){
    CatEmployees* ce = new CatEmployees();
    ce->show();}

void MainWindow::on_mSettings_triggered(){
    Settings* sdb = new Settings();
//    sdb->setWindowFlags(sdb->windowFlags() | Qt::WindowStaysOnTopHint);
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
    connect(ewr,SIGNAL(reportSubmited()), mainwidget, SLOT(on_dialog_closed()));
    ewr->show();}

void MainWindow::on_mNewWorkReport_triggered(){
    showEditWorkReport();
    emit sendMode("new", currentOrderID);}

void MainWindow::showGiveOrder(){
    GiveOrder *gor = new GiveOrder();
    connect(this, SIGNAL(sendMode(QString, QString)), gor, SLOT(getMode(QString, QString)));
    connect(gor,SIGNAL(orderSubmited()), mainwidget, SLOT(on_dialog_closed()));
//    gor->setWindowFlags(gor->windowFlags() | Qt::WindowStaysOnTopHint);
    gor->show();}

void MainWindow::on_mGiveOrder_triggered(){
    showGiveOrder();
    emit sendMode("new", currentOrderID);}

void MainWindow::on_mAbout_triggered(){
    About * ab = new About();
//    ab->setWindowFlags(ab->windowFlags() | Qt::WindowStaysOnTopHint);
    ab->show();}

void MainWindow::on_mAboutQt_triggered(){
    QMessageBox mb;
    mb.aboutQt(this, tr("About Qt"));
    mb.exec();}

void MainWindow::on_mJrnDiagReports_triggered(){
    JrnDiagReports* jdr = new JrnDiagReports();
    jdr->show();}

void MainWindow::on_mNewDiagReport_triggered(){
    showEditDiagReport();
    emit sendMode("new", currentOrderID);}

void MainWindow::showEditDiagReport(){
    EditDiagReport * edr = new EditDiagReport();
    connect(this, SIGNAL(sendMode(QString, QString)), edr, SLOT(getMode(QString, QString)));
    connect(edr,SIGNAL(reportSubmited()), mainwidget, SLOT(on_dialog_closed()));
    edr->show();}

void MainWindow::on_mGiveOrderDiag_triggered(){
    showGiveOrderDiag();
    emit sendMode("new", currentOrderID);}

void MainWindow::showGiveOrderDiag(){
    GiveOrderDiag * god = new GiveOrderDiag();
    connect(this, SIGNAL(sendMode(QString, QString)), god, SLOT(getMode(QString, QString)));
    connect(god,SIGNAL(orderSubmited()), mainwidget, SLOT(on_dialog_closed()));
//    god->setWindowFlags(god->windowFlags() | Qt::WindowStaysOnTopHint);
    god->show();}

void MainWindow::reject(){
    return; }

void MainWindow::closeEvent(QCloseEvent *event){
    settings->setValue("ui/geometry", saveGeometry());
//    settings->setValue("ui/state", saveState());
    settings->sync();
    QApplication::closeAllWindows();
    event->accept(); }

void MainWindow::on_mHelp_triggered(){
    QDesktopServices::openUrl(QUrl::fromLocalFile(QString(QCoreApplication::applicationDirPath()+"/help/"+ sLocale +"/index.html")));}

void MainWindow::on_mPrintHWDocs_triggered(){
    PrintHWDocuments * phwd = new PrintHWDocuments();
    phwd->show();}

void MainWindow::on_mPaySalaries_triggered(){
    Salaries * sal = new Salaries();
//    sal->setWindowFlags(sal->windowFlags() | Qt::WindowStaysOnTopHint);
    sal->show();}

void MainWindow::on_mSuppliers_triggered(){
    CatSuppliers* csu = new CatSuppliers();
    csu->show();}

void MainWindow::on_mNewPartsRequest_triggered(){
    showPartsRequest();
    emit sendMode("new", currentOrderID);}

void MainWindow::showPartsRequest(){
    EditPartsRequest * epr = new EditPartsRequest();
    connect(this, SIGNAL(sendMode(QString, QString)), epr, SLOT(getMode(QString, QString)));
    connect(epr,SIGNAL(requestSubmited()), mainwidget, SLOT(on_dialog_closed()));
    epr->show();}

void MainWindow::on_mJrnPartsRequests_triggered(){
    JrnPartsRequests* jpr = new JrnPartsRequests();
    jpr->show();}

void MainWindow::on_mOrdersLog_triggered(){
    OrdersLog* ordl = new OrdersLog();
    ordl->show();}


void MainWindow::on_mPartReqLog_triggered(){
    PartsReqLog* partl = new PartsReqLog();
    partl->show();}

void MainWindow::on_mFullscreen_triggered(bool checked){
    if (checked)
        QMainWindow::showFullScreen();
    else
        QMainWindow::showNormal();}

void MainWindow::on_mOrdersMode_triggered(){
    mainwidget = new OrdersWidgetMain(this);
    setCentralWidget(mainwidget);}

void MainWindow::on_mStorekeeperMode_triggered(){
    mainwidget = new PartsWidgetStorekeeper(this);
    setCentralWidget(mainwidget);}

void MainWindow::on_mMasterMode_triggered(){
    mainwidget = new OrdersWidgetMaster(this);
    setCentralWidget(mainwidget);}

