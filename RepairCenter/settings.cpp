#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    crypto = SimpleCrypt(Q_UINT64_C(0xd3752f1e9b140689));
//    Settings::activateWindow();

    settings = new QSettings(QCoreApplication::applicationDirPath()+"/settings.conf",QSettings::IniFormat);
    settings->setIniCodec("UTF-8");
    ui->server->setText(settings->value("mysql/hostname").toString());
    ui->port->setText(settings->value("mysql/port").toString());
    ui->dbname->setText(settings->value("mysql/database").toString());
    ui->username->setText(settings->value("mysql/user").toString());
    ui->password->setText(crypto.decryptToString(settings->value("mysql/password").toString()));
    ui->eUsername->setText(settings->value("user/username").toString());
    ui->ePassword->setText(crypto.decryptToString(settings->value("mysql/password").toString()));

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

    ui->wDate->setText(settings->value("orderstable/datew").toString());
    ui->wState->setText(settings->value("orderstable/statew").toString());
    ui->wCustomer->setText(settings->value("orderstable/customerw").toString());
    ui->wType->setText(settings->value("orderstable/typew").toString());
    ui->wProduct->setText(settings->value("orderstable/productw").toString());
    ui->wDefect->setText(settings->value("orderstable/defectw").toString());
    ui->wAcceptor->setText(settings->value("orderstable/acceptorw").toString());
    ui->wMaster->setText(settings->value("orderstable/masterw").toString());
    ui->wNotified->setText(settings->value("orderstable/notifiedw").toString());
    }

    QString lang = settings->value("locale/language").toString();
    if (lang == "") //default system language
        ui->language->setCurrentIndex(0);

    else if (lang == "ru_RU")//russian
        ui->language->setCurrentIndex(1);

    else if (lang == "en_US")//english
        ui->language->setCurrentIndex(2);

    langIdx = ui->language->currentIndex();

    readDBSettings();
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

Settings::~Settings()
{
    delete ui;
}

void Settings::on_cancel_clicked()
{
    close();
}

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

    settings->setValue("orderstable/datew", ui->wDate->text());
    settings->setValue("orderstable/statew", ui->wState->text());
    settings->setValue("orderstable/customerw", ui->wCustomer->text());
    settings->setValue("orderstable/typew", ui->wType->text());
    settings->setValue("orderstable/productw", ui->wProduct->text());
    settings->setValue("orderstable/defectw", ui->wDefect->text());
    settings->setValue("orderstable/acceptorw", ui->wAcceptor->text());
    settings->setValue("orderstable/masterw", ui->wMaster->text());
    settings->setValue("orderstable/notifiedw", ui->wNotified->text());

    settings->setValue("user/username", ui->eUsername->text());
    settings->setValue("user/password", crypto.encryptToString(ui->ePassword->text()));

    settings->setValue("mysql/hostname", ui->server->text());
    settings->setValue("mysql/port", ui->port->text());
    settings->setValue("mysql/database", ui->dbname->text());
    settings->setValue("mysql/user", ui->username->text());
    settings->setValue("mysql/password", crypto.encryptToString(ui->password->text()));


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
    }


    if (ui->language->currentIndex() != langIdx) {

        switch(ui->language->currentIndex())  {
        case 0://system default
            settings->setValue("locale/language", "");
            break;
        case 1://russian
            settings->setValue("locale/language", "ru_RU");
            break;
        case 2://american english
            settings->setValue("locale/language", "en_US");
            break;
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
        if ( QProcess::startDetached(QString("\"") + QApplication::applicationFilePath() + "\"") )
          QApplication::quit();
    }
    if (mb.clickedButton() == bNo){
        close();
    }

}
