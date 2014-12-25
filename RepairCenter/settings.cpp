#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    Settings::activateWindow();

    settings = new QSettings(QCoreApplication::applicationDirPath()+"/settings.conf",QSettings::IniFormat);
    settings->setIniCodec("UTF-8");
    ui->server->setText(settings->value("mysql/hostname").toString());
    ui->port->setText(settings->value("mysql/port").toString());
    ui->dbname->setText(settings->value("mysql/database").toString());
    ui->username->setText(settings->value("mysql/user").toString());
    ui->password->setText(settings->value("mysql/password").toString());

    QString lang = settings->value("locale/language").toString();
    if (lang == "") //default system language
        ui->language->setCurrentIndex(0);

    else if (lang == "ru_RU")//russian
        ui->language->setCurrentIndex(1);

    else if (lang == "en_US")//english
        ui->language->setCurrentIndex(2);

    langIdx = ui->language->currentIndex();
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
    settings->setValue("mysql/hostname", ui->server->text());
    settings->setValue("mysql/port", ui->port->text());
    settings->setValue("mysql/database", ui->dbname->text());
    settings->setValue("mysql/user", ui->username->text());
    settings->setValue("mysql/password", ui->password->text());

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
    mb.setWindowTitle(tr("Внимание!"));
    mb.setText(tr("Все изменения вступят в силу при следующем запуске.\n Перезапустить приложение?"));
    mb.setInformativeText(tr(""));
    QPushButton *bYes = mb.addButton(tr("Да"), QMessageBox::ActionRole);
    QPushButton *bNo = mb.addButton(tr("Нет"), QMessageBox::ActionRole);
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
