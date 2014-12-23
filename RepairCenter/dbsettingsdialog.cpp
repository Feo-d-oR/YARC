#include "dbsettingsdialog.h"
#include "ui_dbsettingsdialog.h"

DBSettingsDialog::DBSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DBSettingsDialog)
{
    ui->setupUi(this);
    DBSettingsDialog::activateWindow();

    QSettings *settings = new QSettings("db.conf",QSettings::IniFormat);
    ui->server->setText(settings->value("mysql/hostname").toString());
    ui->port->setText(settings->value("mysql/port").toString());
    ui->dbname->setText(settings->value("mysql/database").toString());
    ui->username->setText(settings->value("mysql/user").toString());
    ui->password->setText(settings->value("mysql/password").toString());
}

DBSettingsDialog::~DBSettingsDialog()
{
    delete ui;
}

void DBSettingsDialog::on_cancel_clicked()
{
    close();
}

void DBSettingsDialog::on_save_clicked()
{
    QSettings *settings = new QSettings("db.conf",QSettings::IniFormat);
    settings->setValue("mysql/hostname", ui->server->text());
    settings->setValue("mysql/port", ui->port->text());
    settings->setValue("mysql/database", ui->dbname->text());
    settings->setValue("mysql/user", ui->username->text());
    settings->setValue("mysql/password", ui->password->text());
    settings->sync();
    close();
}
