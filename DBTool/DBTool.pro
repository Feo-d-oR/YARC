#-------------------------------------------------
#
# Project created by QtCreator 2015-02-03T22:03:24
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DBTool
TEMPLATE = app

include($$PWD/../config.pri)

DESTDIR = $${DEST_DIRECTORY}

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    updatedb.h \
    createdb.h

FORMS    += mainwindow.ui

RESOURCES += \
    Icons.qrc \
    languages.qrc

TRANSLATIONS += i18n/dbtool_ru_RU.ts
TRANSLATIONS += i18n/dbtool_en_US.ts

OTHER_FILES += \
    i18n/dbtool_ru_RU.ts \
    i18n/dbtool_en_US.ts