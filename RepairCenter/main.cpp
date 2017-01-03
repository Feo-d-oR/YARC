#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("UTF8");
    QTextCodec::setCodecForLocale(codec);

    QTranslator qTranslator;
    QString locale = QLocale::system().name(); //reading system locale
    QString loSettings;
    QSettings *settings = new QSettings(QCoreApplication::applicationDirPath()+"/repaircenter.conf",QSettings::IniFormat);
    settings->setIniCodec("UTF-8");
    loSettings = settings->value("locale/language").toString();

    if (loSettings != "")//if language is set then ignore system locale
        locale = loSettings;

    if (qTranslator.load("./i18n/repaircenter_"+locale+".qm")) {
        a.installTranslator(&qTranslator);
    } else
    {   qTranslator.load("./i18n/repaircenter_en_US.qm");
        a.installTranslator(&qTranslator);
    }

    MainWindow w;
    w.show();

    return a.exec();
}
