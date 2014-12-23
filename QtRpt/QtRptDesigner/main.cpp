/*
Name: QtRptDesigner
Version: 1.4.5
Programmer: Aleksey Osipov
e-mail: aliks-os@ukr.net
2012-2014
*/

#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setApplicationName(QApplication::tr("QtRptDesigner"));
    a.setOrganizationName("Aleksey Osipov");
    a.setOrganizationDomain("https://sourceforge.net/projects/qtrpt/");//projects web page
    a.setApplicationVersion("1.4.5");

    QTextCodec *codec = QTextCodec::codecForName("UTF8");
    QTextCodec::setCodecForLocale(codec);

    QTranslator qTranslator;
    QString locale = QLocale::system().name(); //reading system locale
    QString loSettings;
    QSettings settings(QCoreApplication::applicationDirPath()+"/setting.ini",QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    settings.beginGroup("language");
    loSettings = settings.value("language").toString();
    settings.endGroup();

    if (loSettings != "")//if language is set then ignore system locale
        locale = loSettings;
    //! NOTE: windows and linux system locale are different for serbian language, sr_RS is latin not cyril, this differenc is corrected in code

    if ( qTranslator.load(":/language/i18n/QtRprtDesigner_"+locale+".qm") ) { a.installTranslator(&qTranslator); }

    //NOTE: Arabic language is the same for all Arabic countries (ex. ar_SY = ar_LY) for that we've to use language name instaed of locale name

    if (locale.left(2) == "ar") {
        a.setLayoutDirection(Qt::RightToLeft);
    }


    MainWindow w;
    w.show();

    return a.exec();
}
