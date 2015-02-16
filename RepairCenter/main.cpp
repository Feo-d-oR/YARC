#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("UTF8");
    QTextCodec::setCodecForLocale(codec);

    QTranslator qTranslator;
    QString loSettings;
    QSettings *settings = new QSettings(QCoreApplication::applicationDirPath()+"/settings.conf",QSettings::IniFormat);
    settings->setIniCodec("UTF-8");
    loSettings = settings->value("locale/language").toString();

    if (loSettings != "")//if language is set then ignore system locale
        MainWindow::local = loSettings;

    if (qTranslator.load(":/langs/i18n/repaircenter_"+MainWindow::local+".qm")) {
        a.installTranslator(&qTranslator);
    }

    MainWindow w;
    w.show();

    return a.exec();
}
