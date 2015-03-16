#-------------------------------------------------
#
# Project created by QtCreator 2015-02-03T22:03:24
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DBTool
TEMPLATE = app

include($$PWD/../config.pri)

SOURCES += main.cpp\
        mainwindow.cpp \
    dbwork.cpp

HEADERS  += mainwindow.h \
    dbwork.h

FORMS    += mainwindow.ui

RESOURCES += \
    Icons.qrc \
    languages.qrc

TRANSLATIONS += i18n/dbtool_ru_RU.ts
TRANSLATIONS += i18n/dbtool_en_US.ts

OTHER_FILES += \
    i18n/dbtool_ru_RU.ts \
    i18n/dbtool_en_US.ts

dbtupd.commands = lupdate $$PWD/DBTool.pro
dbtrel.commands = lrelease $$PWD/DBTool.pro
dbtrel.depends = dbtupd

QMAKE_EXTRA_TARGETS += dbtupd dbtrel
PRE_TARGETDEPS += dbtrel
#translate.commands = $(COPY) *.qm $$DESTDIR/i18n/
