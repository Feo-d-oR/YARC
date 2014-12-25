#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "editorder.h"
#include "giveorder.h"

#include "createdbdialog.h"
#include "settings.h"

#include "catemployees.h"
#include "catconstants.h"
#include "catproducttypes.h"
#include "catcustomers.h"
#include "catspares.h"
#include "catsparetypes.h"
#include "catworktypes.h"

#include "jrndiagreports.h"
#include "editdiagreport.h"

#include "jrnworkreports.h"
#include "editworkreport.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
//init database
    if (dbConnect()) {
        initModelOrders();
    }
    else{
        QMessageBox mb;
        mb.setWindowTitle(tr("Ошибка!"));
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

    ui->dateend->setDate(QDate::currentDate());
}

MainWindow::~MainWindow(){
    delete ui;
}

bool MainWindow::dbConnect()
{
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        QSettings *settings = new QSettings(QCoreApplication::applicationDirPath()+"/settings.conf",QSettings::IniFormat);
        settings->setIniCodec("UTF-8");
        db.setHostName(settings->value("mysql/hostname").toString());
        db.setPort(settings->value("mysql/port").toInt());
        db.setDatabaseName(settings->value("mysql/database").toString());
        db.setUserName(settings->value("mysql/user").toString());
        db.setPassword(settings->value("mysql/password").toString());
        if (db.open())
            return true;
        else
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
//    model->setRelation(acceptorIdx, QSqlRelation("employees","ida","name"));
//    model->setRelation(giverIdx, QSqlRelation("employees","idg","name"));
    model->setRelation(model->fieldIndex("phone"), QSqlRelation("customers","id","phone"));

    model->setSort(model->fieldIndex("number"),Qt::DescendingOrder);  //setting default sorting

//setting tableview widget
    ui->tview->setModel(model);
//    ui->tview->setItemDelegate(new QSqlRelationalDelegate(ui->tview));

    //setting headers
    model->setHeaderData(model->fieldIndex("number"), Qt::Horizontal, "№");
    model->setHeaderData(model->fieldIndex("date_in"), Qt::Horizontal, "Дата");
    model->setHeaderData(typeIdx, Qt::Horizontal, "Тип");
    model->setHeaderData(model->fieldIndex("product"), Qt::Horizontal, "Изделие");
    model->setHeaderData(stateIdx, Qt::Horizontal, "Статус");
    model->setHeaderData(masterIdx, Qt::Horizontal, "Мастер");


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

//setting mapper & relations for right panel
    ui->eState->setModel(model->relationModel(stateIdx));
    ui->eState->setModelColumn(model->relationModel(stateIdx)->fieldIndex("name"));

    ui->eMaster->setModel(model->relationModel(masterIdx));
    ui->eMaster->setModelColumn(model->relationModel(masterIdx)->fieldIndex("name"));


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

void MainWindow::on_exit_triggered()
{
    close();
}

void MainWindow::on_mCreatedb_triggered()
{
    CreateDBDialog* cdb = new CreateDBDialog();
    cdb->show();
}

void MainWindow::on_mSettings_triggered()
{
    Settings* sdb = new Settings();
    sdb->show();
}

void MainWindow::on_rbAll_clicked(bool checked)
{
    if (checked)
        ui->lSearch->clear();
        ui->searchtexttype->setCurrentIndex(0);
        model->setSort(model->fieldIndex("number"),Qt::DescendingOrder);
        model->setFilter(QString());
        model->select();
}

void MainWindow::on_rbCompleted_clicked(bool checked)
{
    if (checked)
        model->setSort(model->fieldIndex("number"),Qt::DescendingOrder);
        model->setFilter("state IN (3, 4, 5, 6, 18)");
}

void MainWindow::on_rbAccepted_clicked(bool checked)
{
    if (checked)
        model->setSort(model->fieldIndex("number"),Qt::DescendingOrder);
        model->setFilter("state IN (1, 2, 12, 13, 19)");
}

void MainWindow::on_rbConsent_clicked(bool checked)
{
    if (checked)
        model->setSort(model->fieldIndex("number"),Qt::DescendingOrder);
        model->setFilter("state IN (7, 8)");
}

void MainWindow::on_rbWaitSpares_clicked(bool checked)
{
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

void MainWindow::getCustomerIds()
{
    QStringList list;
    QSqlQuery q;
    q.exec("SELECT * FROM customers WHERE name LIKE '%" + ui->lSearch->text() + "%'");
    q.first();
    list.append(q.value(0).toString());
    while (q.next())
    {
        list.append(q.value(0).toString());
    }
    namesstr = list.join("','");
    qDebug() << "list:" << list;
    qDebug() << "string:" << namesstr;
}

void MainWindow::on_lSearch_textEdited(const QString &arg1)
{
    model->setFilter(QString());
    if(ui->lSearch->text() != "")
    {
        if(ui->searchtexttype->currentText() == tr("Номер квитанции"))
            model->setFilter("number = " + arg1);
        if(ui->searchtexttype->currentText() == tr("Имя"))
        {
            getCustomerIds();
            model->setFilter("customer IN ('" + namesstr + "')");
            qDebug() << "filter:" << model->filter();
        }
    }
}


void MainWindow::on_bSubmit_clicked()
{
    model->submitAll();
}

void MainWindow::showEditOrder()
{
    EditOrder *ord = new EditOrder();
    connect(this, SIGNAL(sendMode(QString, QString)), ord, SLOT(getMode(QString, QString)));
    connect(ord,SIGNAL(orderSubmited()), this, SLOT(on_dialog_closed()));
    ord->show();
}

void MainWindow::on_mNewOrder_triggered()
{
    showEditOrder();
    emit sendMode("new", "0");
}

void MainWindow::on_bView_clicked()
{
    showEditOrder();
    emit sendMode("view", ui->dNumber->text());
}

void MainWindow::on_bEdit_clicked()
{
    showEditOrder();
    emit sendMode("edit", ui->dNumber->text());
}

void MainWindow::on_mEmployees_triggered()
{
    CatEmployees* ce = new CatEmployees();
    ce->show();
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

void MainWindow::on_dialog_closed()
{
    model->select();
}


void MainWindow::on_mConstants_triggered()
{
    CatConstants* cconst = new CatConstants();
    cconst->show();
}

void MainWindow::on_mProductTypes_triggered()
{
    CatProductTypes* cptype = new CatProductTypes();
    cptype->show();
}

void MainWindow::on_mCustomers_triggered()
{
    CatCustomers* ccust = new CatCustomers();
    ccust->show();
}

void MainWindow::on_mSpares_triggered()
{
    CatSpares* csp = new CatSpares();
    csp->show();
}

void MainWindow::on_mSpareTypes_triggered()
{
    CatSpareTypes* cst = new CatSpareTypes();
    cst->show();
}

void MainWindow::on_mWorkTypes_triggered()
{
    CatWorkTypes* cwt = new CatWorkTypes();
    cwt->show();
}

void MainWindow::on_mJrnWorkReports_triggered()
{
    JrnWorkReports* jwr = new JrnWorkReports();
    jwr->show();
}

void MainWindow::showEditWorkReport()
{
    EditWorkReport *ewr = new EditWorkReport();
    connect(this, SIGNAL(sendMode(QString, QString)), ewr, SLOT(getMode(QString, QString)));
    ewr->show();
}

void MainWindow::on_mNewWorkReport_triggered()
{
    showEditWorkReport();
    emit sendMode("new", "0");
}

void MainWindow::showGiveOrder()
{
    GiveOrder *gor = new GiveOrder();
    connect(this, SIGNAL(sendMode(QString, QString)), gor, SLOT(getMode(QString, QString)));
    gor->show();
}

void MainWindow::on_mGiveOrder_triggered()
{
    showGiveOrder();
    emit sendMode("new", ui->dNumber->text());
}

void MainWindow::on_mAbout_triggered()
{
    QMessageBox mb;
    mb.setWindowTitle(tr("О программе..."));
    mb.setTextFormat(Qt::RichText);
    mb.setText("RepairCenter ver. 0.1a");
    mb.setInformativeText("<a href = 'http://sourceforge.net/projects/repaircenter/'>RepairCenter on SourceForge</a> \n "
                          "<a href = 'http://sourceforge.net/projects/qtrpt/'>QtRPT 1.4.5</a>");
    QPushButton *bOk = mb.addButton("OK", QMessageBox::AcceptRole);
    mb.setDefaultButton(bOk);
    mb.exec();
    if (mb.clickedButton() == bOk)
        mb.close();
}
