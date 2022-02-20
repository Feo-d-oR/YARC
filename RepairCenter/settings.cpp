#include "settings.h"
#include "ui_settings.h"
#include "mainwindow.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    crypto = SimpleCrypt(Q_UINT64_C(0xd3752f1e9b140689));
    ui->setupUi(this);
    readSettings();
    readDBSettings();
}

void Settings::readSettings()
{
    settings = new QSettings(QCoreApplication::applicationDirPath()+"/repaircenter.conf",QSettings::IniFormat);
    settings->setIniCodec("UTF-8");
    ui->server->setText(settings->value("mysql/hostname").toString());
    ui->port->setText(settings->value("mysql/port").toString());
    ui->dbname->setText(settings->value("mysql/database").toString());
    ui->username->setText(settings->value("mysql/user").toString());
    ui->password->setText(crypto.decryptToString(settings->value("mysql/password").toString()));
    ui->eConnCheckInterval->setText(settings->value("mysql/conncheckinterval").toString());

    if(settings->contains("user/username"))
    {
        ui->eUsername->setText(settings->value("user/username").toString());
        ui->ePassword->setText(crypto.decryptToString(settings->value("user/password").toString()));
    }

    if(settings->contains("orderstable/datee"))
    {
    ui->cbDate->setChecked(settings->value("orderstable/datee").toBool());
    ui->cbState->setChecked(settings->value("orderstable/statee").toBool());
    ui->cbCustomer->setChecked(settings->value("orderstable/customere").toBool());
    ui->cbType->setChecked(settings->value("orderstable/typee").toBool());
    ui->cbProduct->setChecked(settings->value("orderstable/producte").toBool());
    ui->cbDefect->setChecked(settings->value("orderstable/defecte").toBool());
    ui->cbAcceptor->setChecked(settings->value("orderstable/acceptore").toBool());
    ui->cbMaster->setChecked(settings->value("orderstable/mastere").toBool());
    ui->cbNotified->setChecked(settings->value("orderstable/notifiede").toBool());
    ui->cbID->setChecked(settings->value("orderstable/ide").toBool());
    ui->cbSum->setChecked(settings->value("orderstable/sume").toBool());
    ui->cbComment->setChecked(settings->value("orderstable/commente").toBool());

    ui->wDate->setText(settings->value("orderstable/datew").toString());
    ui->wState->setText(settings->value("orderstable/statew").toString());
    ui->wCustomer->setText(settings->value("orderstable/customerw").toString());
    ui->wType->setText(settings->value("orderstable/typew").toString());
    ui->wProduct->setText(settings->value("orderstable/productw").toString());
    ui->wDefect->setText(settings->value("orderstable/defectw").toString());
    ui->wAcceptor->setText(settings->value("orderstable/acceptorw").toString());
    ui->wMaster->setText(settings->value("orderstable/masterw").toString());
    ui->wNotified->setText(settings->value("orderstable/notifiedw").toString());
    ui->wID->setText(settings->value("orderstable/idw").toString());
    ui->wSum->setText(settings->value("orderstable/sumw").toString());
    ui->wComment->setText(settings->value("orderstable/commentw").toString());

    if(settings->contains("orderstable/showlimit"))
    {
        ui->eLimitOrders->setText(settings->value("orderstable/showlimit").toString());
        ui->cbAffectFilters->setChecked(settings->value("orderstable/limitallfilters").toBool());
    }
    }

    if(settings->contains("defaults/cond1"))
    {
        ui->eCond1->setText(settings->value("defaults/cond1").toString());
        ui->eCond2->setText(settings->value("defaults/cond2").toString());
        ui->eCond3->setText(settings->value("defaults/cond3").toString());
        ui->eCond4->setText(settings->value("defaults/cond4").toString());
        ui->eCond5->setText(settings->value("defaults/cond5").toString());

        ui->eDefect1->setText(settings->value("defaults/defect1").toString());
        ui->eDefect2->setText(settings->value("defaults/defect2").toString());
        ui->eDefect3->setText(settings->value("defaults/defect3").toString());
        ui->eDefect4->setText(settings->value("defaults/defect4").toString());
        ui->eDefect5->setText(settings->value("defaults/defect5").toString());

        ui->eCompl1->setText(settings->value("defaults/compl1").toString());
        ui->eCompl2->setText(settings->value("defaults/compl2").toString());
        ui->eCompl3->setText(settings->value("defaults/compl3").toString());
        ui->eCompl4->setText(settings->value("defaults/compl4").toString());
        ui->eCompl5->setText(settings->value("defaults/compl5").toString());
    }

    if(settings->value("ui/mainwindowstate") == "max")
        ui->rbMaximize->setChecked(true);
    else if(settings->value("ui/mainwindowstate") == "last")
        ui->rbLastState->setChecked(true);
    else if(settings->value("ui/mainwindowstate") == "full")
        ui->rbFullscreen->setChecked(true);
    else
        ui->rbMaximize->setChecked(true);

    ui->eTableUpdateInterval->setText(settings->value("ui/tableupdateinterval").toString());

    QString adminmode = settings->value("ui/adminmode").toString();

    if (adminmode == "acceptor")
        ui->cbDefaultAdminUI->setCurrentIndex(0);
    else if (adminmode == "storekeeper")
        ui->cbDefaultAdminUI->setCurrentIndex(1);
    else if (adminmode == "master")
        ui->cbDefaultAdminUI->setCurrentIndex(2);
    else
        ui->cbDefaultAdminUI->setCurrentIndex(0);

    ui->eWarranty->setText(settings->value("defaults/warranty").toString());

    QString lang = settings->value("locale/language").toString();
    if (lang == "") //default system language
        ui->language->setCurrentIndex(0);
    else if (lang == "en_US")//english
        ui->language->setCurrentIndex(1);
    else if (lang == "ru_RU")//russian
        ui->language->setCurrentIndex(2);
    else if (lang == "it_IT")//italian
        ui->language->setCurrentIndex(3);
//    else if (lang == "nl_NL")//dutch
//        ui->language->setCurrentIndex(3);

    langIdx = ui->language->currentIndex();

    if(!MainWindow::isadmin)
    {
        ui->money->setDisabled(true);
        ui->permissions->setDisabled(true);
    }
}

void Settings::readDBSettings()
{
    q.exec("SELECT value_n FROM system WHERE name = 'percMaster'");
    if (q.first())
        dbconnected = true;
    ui->prmast->setText(st.setNum(q.value(0).toFloat() *100));
    q.exec("SELECT value_n FROM system WHERE name = 'percAcceptor'");
    q.first();
    ui->pracc->setText(st.setNum(q.value(0).toFloat() *100));

    q.exec("SELECT value_n FROM system WHERE name = 'masterCanEditWorks'");
    q.first();
    ui->cbMEdWorks->setChecked(q.value(0).toBool());
    q.exec("SELECT value_n FROM system WHERE name = 'masterCanEditSpares'");
    q.first();
    ui->cbMEdSpares->setChecked(q.value(0).toBool());
    q.exec("SELECT value_n FROM system WHERE name = 'acceptorCanEditWorks'");
    q.first();
    ui->cbAEdWorks->setChecked(q.value(0).toBool());
    q.exec("SELECT value_n FROM system WHERE name = 'acceptorCanEditSpares'");
    q.first();
    ui->cbAEdSpares->setChecked(q.value(0).toBool());
    q.exec("SELECT value_n FROM system WHERE name = 'acceptorCanEditDiag'");
    q.first();
    ui->cbAEdDiag->setChecked(q.value(0).toBool());

    q.exec("SELECT value_n FROM system WHERE name = 'productTypeM'");
    q.first();
    ui->cbProductTypeM->setChecked(q.value(0).toBool());
    q.exec("SELECT value_n FROM system WHERE name = 'productM'");
    q.first();
    ui->cbProductM->setChecked(q.value(0).toBool());
    q.exec("SELECT value_n FROM system WHERE name = 'serialM'");
    q.first();
    ui->cbSerialM->setChecked(q.value(0).toBool());
    q.exec("SELECT value_n FROM system WHERE name = 'defectM'");
    q.first();
    ui->cbDefectM->setChecked(q.value(0).toBool());
    q.exec("SELECT value_n FROM system WHERE name = 'conditionM'");
    q.first();
    ui->cbConditionM->setChecked(q.value(0).toBool());
    q.exec("SELECT value_n FROM system WHERE name = 'completenessM'");
    q.first();
    ui->cbCompletenessM->setChecked(q.value(0).toBool());
    q.exec("SELECT value_n FROM system WHERE name = 'customerM'");
    q.first();
    ui->cbCustomerM->setChecked(q.value(0).toBool());
    q.exec("SELECT value_n FROM system WHERE name = 'phoneM'");
    q.first();
    ui->cbPhoneM->setChecked(q.value(0).toBool());


    model_a = new QSqlQueryModel();
    model_a->setQuery("SELECT id, name FROM employees WHERE position_type = 2 AND isactive = 1");
    ui->eDefAcceptor->setModel(model_a);
    ui->eDefAcceptor->model()->sort(1, Qt::AscendingOrder);
    ui->eDefAcceptor->setModelColumn(1);

    model_m = new QSqlQueryModel();
    model_m->setQuery("SELECT id, name FROM employees WHERE position_type = 1 AND isactive = 1");
    ui->eDefMaster->setModel(model_m);
    ui->eDefMaster->model()->sort(1, Qt::AscendingOrder);
    ui->eDefMaster->setModelColumn(1);

    model_s = new QSqlQueryModel();
    model_s->setQuery("SELECT id, name FROM states WHERE id IN (1, 2, 14, 16, 19)");
    ui->eDefState->setModel(model_s);
    ui->eDefState->model()->sort(1, Qt::AscendingOrder);
    ui->eDefState->setModelColumn(1);

    QModelIndexList idx_a = ui->eDefAcceptor->model()->match(ui->eDefAcceptor->model()->index(0, 0), Qt::EditRole, settings->value("defaults/acceptor").toInt(), 1, Qt::MatchExactly);
    ui->eDefAcceptor->setCurrentIndex(idx_a.value(0).row());

    QModelIndexList idx_m = ui->eDefMaster->model()->match(ui->eDefMaster->model()->index(0, 0), Qt::EditRole, settings->value("defaults/master").toInt(), 1, Qt::MatchExactly);
    ui->eDefMaster->setCurrentIndex(idx_m.value(0).row());

    QModelIndexList idx_s = ui->eDefState->model()->match(ui->eDefState->model()->index(0, 0), Qt::EditRole, settings->value("defaults/state").toInt(), 1, Qt::MatchExactly);
    ui->eDefState->setCurrentIndex(idx_s.value(0).row());
}

Settings::~Settings(){
    delete ui;}

void Settings::on_cancel_clicked(){
    close();}

void Settings::on_save_clicked()
{
    settings->setValue("orderstable/datee", ui->cbDate->isChecked());
    settings->setValue("orderstable/statee", ui->cbState->isChecked());
    settings->setValue("orderstable/customere", ui->cbCustomer->isChecked());
    settings->setValue("orderstable/typee", ui->cbType->isChecked());
    settings->setValue("orderstable/producte", ui->cbProduct->isChecked());
    settings->setValue("orderstable/defecte", ui->cbDefect->isChecked());
    settings->setValue("orderstable/acceptore", ui->cbAcceptor->isChecked());
    settings->setValue("orderstable/mastere", ui->cbMaster->isChecked());
    settings->setValue("orderstable/notifiede", ui->cbNotified->isChecked());
    settings->setValue("orderstable/ide", ui->cbID->isChecked());
    settings->setValue("orderstable/sume", ui->cbSum->isChecked());
    settings->setValue("orderstable/commente", ui->cbComment->isChecked());

    settings->setValue("orderstable/datew", ui->wDate->text());
    settings->setValue("orderstable/statew", ui->wState->text());
    settings->setValue("orderstable/customerw", ui->wCustomer->text());
    settings->setValue("orderstable/typew", ui->wType->text());
    settings->setValue("orderstable/productw", ui->wProduct->text());
    settings->setValue("orderstable/defectw", ui->wDefect->text());
    settings->setValue("orderstable/acceptorw", ui->wAcceptor->text());
    settings->setValue("orderstable/masterw", ui->wMaster->text());
    settings->setValue("orderstable/notifiedw", ui->wNotified->text());
    settings->setValue("orderstable/idw", ui->wSum->text());
    settings->setValue("orderstable/sumw", ui->wSum->text());
    settings->setValue("orderstable/commentw", ui->wComment->text());

    settings->setValue("orderstable/showlimit", ui->eLimitOrders->text());
    settings->setValue("orderstable/limitallfilters", ui->cbAffectFilters->isChecked());

    settings->setValue("defaults/warranty", ui->eWarranty->text());

    settings->setValue("defaults/cond1", ui->eCond1->text());
    settings->setValue("defaults/cond2", ui->eCond2->text());
    settings->setValue("defaults/cond3", ui->eCond3->text());
    settings->setValue("defaults/cond4", ui->eCond4->text());
    settings->setValue("defaults/cond5", ui->eCond5->text());

    settings->setValue("defaults/defect1", ui->eDefect1->text());
    settings->setValue("defaults/defect2", ui->eDefect2->text());
    settings->setValue("defaults/defect3", ui->eDefect3->text());
    settings->setValue("defaults/defect4", ui->eDefect4->text());
    settings->setValue("defaults/defect5", ui->eDefect5->text());

    settings->setValue("defaults/compl1", ui->eCompl1->text());
    settings->setValue("defaults/compl2", ui->eCompl2->text());
    settings->setValue("defaults/compl3", ui->eCompl3->text());
    settings->setValue("defaults/compl4", ui->eCompl4->text());
    settings->setValue("defaults/compl5", ui->eCompl5->text());

    if (ui->rbMaximize->isChecked())
        settings->setValue("ui/mainwindowstate", "max");
    else if (ui->rbLastState->isChecked())
        settings->setValue("ui/mainwindowstate", "last");
    else if (ui->rbFullscreen->isChecked())
        settings->setValue("ui/mainwindowstate", "full");
    else
        settings->setValue("ui/mainwindowstate", "max");

    settings->setValue("ui/tableupdateinterval", ui->eTableUpdateInterval->text());

    if (ui->cbDefaultAdminUI->currentIndex() != -1) {

        switch(ui->cbDefaultAdminUI->currentIndex())  {
        case 0:
            settings->setValue("ui/adminmode", "acceptor");
            break;
        case 1:
            settings->setValue("ui/adminmode", "storekeeper");
            break;
        case 2:
            settings->setValue("ui/adminmode", "master");
            break;
        }
    }

    settings->setValue("user/username", ui->eUsername->text());
    settings->setValue("user/password", crypto.encryptToString(ui->ePassword->text()));

    settings->setValue("mysql/hostname", ui->server->text());
    settings->setValue("mysql/port", ui->port->text());
    settings->setValue("mysql/database", ui->dbname->text());
    settings->setValue("mysql/user", ui->username->text());
    settings->setValue("mysql/password", crypto.encryptToString(ui->password->text()));
    settings->setValue("mysql/conncheckinterval", ui->eConnCheckInterval->text());

    if(dbconnected)
    {
        QSqlRecord rec_a = model_a->record(ui->eDefAcceptor->currentIndex());
        QString id_a = rec_a.value(rec_a.indexOf("id")).toString();
        settings->setValue("defaults/acceptor", id_a);

        QSqlRecord rec_m = model_m->record(ui->eDefMaster->currentIndex());
        QString id_m = rec_m.value(rec_m.indexOf("id")).toString();
        settings->setValue("defaults/master", id_m);

        QSqlRecord rec_s = model_s->record(ui->eDefState->currentIndex());
        QString id_s = rec_s.value(rec_s.indexOf("id")).toString();
        settings->setValue("defaults/state", id_s);

        st.setNum(ui->prmast->text().toFloat() /100);
        q.exec(QString("UPDATE system SET value_n = " + st + " WHERE name = 'percMaster'"));
        st.setNum(ui->pracc->text().toFloat() /100);
        q.exec(QString("UPDATE system SET value_n = " + st + " WHERE name = 'percAcceptor'"));
        st.setNum(1 - (ui->pracc->text().toFloat() /100) - (ui->prmast->text().toFloat() /100));
        q.exec(QString("UPDATE system SET value_n = " + st + " WHERE name = 'percFirm'"));

        q.exec(QString("UPDATE system SET value_n = " + QString::number(ui->cbMEdSpares->isChecked()) + " WHERE name = 'masterCanEditSpares'"));
        q.exec(QString("UPDATE system SET value_n = " + QString::number(ui->cbMEdWorks->isChecked()) + " WHERE name = 'masterCanEditWorks'"));
        q.exec(QString("UPDATE system SET value_n = " + QString::number(ui->cbAEdDiag->isChecked()) + " WHERE name = 'acceptorCanEditDiag'"));
        q.exec(QString("UPDATE system SET value_n = " + QString::number(ui->cbAEdSpares->isChecked()) + " WHERE name = 'acceptorCanEditSpares'"));
        q.exec(QString("UPDATE system SET value_n = " + QString::number(ui->cbAEdWorks->isChecked()) + " WHERE name = 'acceptorCanEditWorks'"));

        q.exec(QString("UPDATE system SET value_n = " + QString::number(ui->cbProductTypeM->isChecked()) + " WHERE name = 'productTypeM'"));
        q.exec(QString("UPDATE system SET value_n = " + QString::number(ui->cbProduct->isChecked()) + " WHERE name = 'productM'"));
        q.exec(QString("UPDATE system SET value_n = " + QString::number(ui->cbSerialM->isChecked()) + " WHERE name = 'serialM'"));
        q.exec(QString("UPDATE system SET value_n = " + QString::number(ui->cbDefectM->isChecked()) + " WHERE name = 'defectM'"));
        q.exec(QString("UPDATE system SET value_n = " + QString::number(ui->cbConditionM->isChecked()) + " WHERE name = 'conditionM'"));
        q.exec(QString("UPDATE system SET value_n = " + QString::number(ui->cbCompletenessM->isChecked()) + " WHERE name = 'completenessM'"));
        q.exec(QString("UPDATE system SET value_n = " + QString::number(ui->cbCustomerM->isChecked()) + " WHERE name = 'customerM'"));
        q.exec(QString("UPDATE system SET value_n = " + QString::number(ui->cbPhoneM->isChecked()) + " WHERE name = 'phoneM'"));
    }


    if (ui->language->currentIndex() != langIdx) {

        switch(ui->language->currentIndex())  {
        case 0://system default
            settings->setValue("locale/language", "");
            break;
        case 1://american english
            settings->setValue("locale/language", "en_US");
            break;
        case 2://russian
            settings->setValue("locale/language", "ru_RU");
            break;
        case 3://italiano
            settings->setValue("locale/language", "it_IT");
            break;
//        case 3://dutch
//            settings->setValue("locale/language", "nl_NL");
//            break;
        }
    }
    settings->sync();

    QMessageBox mb;
    mb.setWindowTitle(tr("Attention!"));
    mb.setText(tr("Some changes will take effect the next time.\n Restart application?"));
    mb.setInformativeText(tr(""));
    QPushButton *bYes = mb.addButton(tr("Yes"), QMessageBox::ActionRole);
    QPushButton *bNo = mb.addButton(tr("No"), QMessageBox::ActionRole);
    mb.setDefaultButton(bNo);
    mb.exec();

    if (mb.clickedButton() == bYes){
        if ( QProcess::startDetached(QString("\"") + QApplication::applicationFilePath() + "\"", QStringList(Q_NULLPTR)) )
          QApplication::quit();
    }
    if (mb.clickedButton() == bNo){
        close();
    }

}
