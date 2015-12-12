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

QString MainWindow::sLocale = "";
float MainWindow::sPercMast = 0;
float MainWindow::sPercAcc = 0;
float MainWindow::sPercFirm = 0;
int MainWindow::defAcceptor = -1;
int MainWindow::defMaster = -1;
int MainWindow::defState = -1;
int MainWindow::role = 0;
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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);

    crypto = SimpleCrypt(Q_UINT64_C(0xd3752f1e9b140689));

    if (checkSettings()) {
        if (dbConnect())
        {
            readGlobalSettings();
            loadUserInterface();
        }
        else{
            QMessageBox mb;
            mb.setIcon(QMessageBox::Critical);
            mb.setWindowTitle(tr("RepairCenter"));
            mb.setText(tr("Database not found!"));
            mb.setInformativeText(tr("Change settings or create new one?"));
            QPushButton *bCreate = mb.addButton(tr("Create"), QMessageBox::ActionRole);
            QPushButton *bEdit = mb.addButton(tr("Change"), QMessageBox::ActionRole);
            QPushButton *bCancel = mb.addButton(tr("Cancel"), QMessageBox::RejectRole);
            mb.setDefaultButton(bEdit);
            mb.exec();

            if (mb.clickedButton() == bCreate){
                if (QProcess::startDetached(QDir::toNativeSeparators(QCoreApplication::applicationDirPath()+"/DBTool")))
                    QApplication::quit();
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
        mb.setText(tr("Settings file not found!"));
        mb.setInformativeText(tr("Create settings file?"));
        QPushButton *bEdit = mb.addButton(tr("Create"), QMessageBox::ActionRole);
        QPushButton *bCancel = mb.addButton(tr("Cancel"), QMessageBox::RejectRole);
        mb.setDefaultButton(bEdit);
        mb.exec();

        if (mb.clickedButton() == bEdit){
            Settings* sdb = new Settings();
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
    settings = new QSettings(QCoreApplication::applicationDirPath()+"/settings.conf",QSettings::IniFormat);
    settings->setIniCodec("UTF-8");
    if (settings->contains("mysql/hostname"))
        return true;
    else
        return false;
}

void MainWindow::readGlobalSettings()
{
    QSqlQuery q;
    settings = new QSettings(QCoreApplication::applicationDirPath()+"/settings.conf",QSettings::IniFormat);
    settings->setIniCodec("UTF-8");

    sLocale = settings->value("locale/language").toString();
    defAcceptor = settings->value("defaults/acceptor").toInt();
    defMaster = settings->value("defaults/master").toInt();
    defState = settings->value("defaults/state").toInt();
    defWarranty = settings->value("defaults/warranty").toString();

    showlimit = settings->value("orderstable/showlimit").toString();
    limitallfilters = settings->value("orderstable/limitallfilters").toBool();

    QString username = settings->value("user/username").toString();
    QString password = settings->value("user/password").toString();
    q.exec(QString("SELECT position_type FROM employees WHERE username = '"+ username +"' AND password = '"+ crypto.decryptToString(password) +"'"));
    q.first();
    role = q.value(0).toInt();
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

}

void MainWindow::loadUserInterface()
{
    if (role == 1) //if master
    {
        mainwidget = new OrdersWidgetMaster(this);
        ui->acceptorToolBar->hide();
        ui->storekeeperToolBar->hide();
        ui->mEmployees->setDisabled(1);
        ui->mNewOrder->setDisabled(1);
        ui->mGiveOrder->setDisabled(1);
        ui->mGiveOrderDiag->setDisabled(1);
        ui->mPaySalaries->setDisabled(1);
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
        ui->mEmployees->setDisabled(1);
        ui->mPaySalaries->setDisabled(1);
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
        ui->masterToolBar->hide();
        ui->mEmployees->setDisabled(1);
        ui->mPaySalaries->setDisabled(1);
        ui->acceptorToolBar->hide();
        ui->mEmployees->setDisabled(1);
        ui->mNewOrder->setDisabled(1);
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
        mainwidget = new OrdersWidgetMain(this);
        isadmin = true;
    }
    else
    {
        ui->catalogs->setDisabled(1);
        ui->actions->setDisabled(1);
        ui->journals->setDisabled(1);
        ui->acceptorToolBar->setDisabled(1);
        ui->masterToolBar->setDisabled(1);
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
            return true;
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

void MainWindow::showEditOrder(){
    EditOrder *ord = new EditOrder();
    connect(this, SIGNAL(sendMode(QString, QString)), ord, SLOT(getMode(QString, QString)));
    connect(ord,SIGNAL(orderSubmited()), mainwidget, SLOT(on_dialog_closed()));
    ord->show();}

void MainWindow::on_mNewOrder_triggered(){
    showEditOrder();
    emit sendMode("new", "0");}

void MainWindow::on_mEmployees_triggered(){
    CatEmployees* ce = new CatEmployees();
    ce->show();}

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
    emit sendMode("new", currentOrderID);}

void MainWindow::showGiveOrder(){
    GiveOrder *gor = new GiveOrder();
    connect(this, SIGNAL(sendMode(QString, QString)), gor, SLOT(getMode(QString, QString)));
    connect(gor,SIGNAL(orderSubmited()), mainwidget, SLOT(on_dialog_closed()));
    gor->show();}

void MainWindow::on_mGiveOrder_triggered(){
    showGiveOrder();
    emit sendMode("new", currentOrderID);}

void MainWindow::on_mAbout_triggered(){
    About * ab = new About();
    ab->show();}

void MainWindow::on_mJrnDiagReports_triggered(){
    JrnDiagReports* jdr = new JrnDiagReports();
    jdr->show();}

void MainWindow::on_mNewDiagReport_triggered(){
    showEditDiagReport();
    emit sendMode("new", currentOrderID);}

void MainWindow::showEditDiagReport(){
    EditDiagReport * edr = new EditDiagReport();
    connect(this, SIGNAL(sendMode(QString, QString)), edr, SLOT(getMode(QString, QString)));
    edr->show();}

void MainWindow::on_mGiveOrderDiag_triggered(){
    showGiveOrderDiag();
    emit sendMode("new", currentOrderID);}

void MainWindow::showGiveOrderDiag(){
    GiveOrderDiag * god = new GiveOrderDiag();
    connect(this, SIGNAL(sendMode(QString, QString)), god, SLOT(getMode(QString, QString)));
    connect(god,SIGNAL(orderSubmited()), mainwidget, SLOT(on_dialog_closed()));
    god->show();}

void MainWindow::reject(){
    return; }

void MainWindow::closeEvent(QCloseEvent *event){
    QApplication::closeAllWindows();
    event->accept(); }

void MainWindow::on_mHelp_triggered(){
    QDesktopServices::openUrl(QUrl::fromLocalFile(QString(QCoreApplication::applicationDirPath()+"/help/"+ sLocale +"/index.html")));
}

void MainWindow::on_mPrintHWDocs_triggered(){
    PrintHWDocuments * phwd = new PrintHWDocuments();
    phwd->show();}

void MainWindow::on_mAboutQt_triggered(){
    QMessageBox mb;
    mb.aboutQt(this, tr("About Qt"));
    mb.exec();}

void MainWindow::on_mPaySalaries_triggered(){
    Salaries * sal = new Salaries();
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
