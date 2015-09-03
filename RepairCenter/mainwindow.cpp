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
#include "orderswidgetmain.h"

QString MainWindow::sLocale = "";
float MainWindow::sPercMast = 0;
float MainWindow::sPercAcc = 0;
float MainWindow::sPercFirm = 0;
int MainWindow::defAcceptor = -1;
int MainWindow::defMaster = -1;
int MainWindow::defState = -1;
QString MainWindow::prevCustomer = "";
QString MainWindow::currentID = "";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
//init database
    if (checkSettings()) {
        if (dbConnect())
        {
            readGlobalSettings();
            loadMainWidget();
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
    q.exec("SELECT value_n FROM system WHERE name = 'percMaster'");
    q.first();
    sPercMast = q.value(0).toFloat();
    q.exec("SELECT value_n FROM system WHERE name = 'percAcceptor'");
    q.first();
    sPercAcc = q.value(0).toFloat();
    q.exec("SELECT value_n FROM system WHERE name = 'percFirm'");
    q.first();
    sPercFirm = q.value(0).toFloat();

    settings = new QSettings(QCoreApplication::applicationDirPath()+"/settings.conf",QSettings::IniFormat);
    settings->setIniCodec("UTF-8");
    sLocale = settings->value("locale/language").toString();

    defAcceptor = settings->value("defaults/acceptor").toInt();
    defMaster = settings->value("defaults/master").toInt();
    defState = settings->value("defaults/state").toInt();
}

void MainWindow::loadMainWidget()
{
    OrdersWidgetMain * orders = new OrdersWidgetMain(this);
    setCentralWidget(orders);
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

void MainWindow::on_mInit_triggered()
{
    if (dbConnect()) {
        readGlobalSettings();
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
    connect(ord,SIGNAL(orderSubmited()), this, SLOT(on_dialog_closed()));
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
    emit sendMode("new", currentID);}

void MainWindow::showGiveOrder(){
    GiveOrder *gor = new GiveOrder();
    connect(this, SIGNAL(sendMode(QString, QString)), gor, SLOT(getMode(QString, QString)));
    connect(gor,SIGNAL(orderSubmited()), this, SLOT(on_dialog_closed()));
    gor->show();}

void MainWindow::on_mGiveOrder_triggered(){
    showGiveOrder();
    emit sendMode("new", currentID);}

void MainWindow::on_mAbout_triggered(){
    About * ab = new About();
    ab->show();}

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
//    QString hpath;
//    hpath = QDir::toNativeSeparators("file://"+QCoreApplication::applicationDirPath()+"/help/"+ sLocale +"/index.html");
    QDesktopServices::openUrl(QUrl::fromLocalFile(QString(QCoreApplication::applicationDirPath()+"/help/"+ sLocale +"/index.html")));
//    QDesktopServices::openUrl(hpath);
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
