#-------------------------------------------------
#
# Project created by QtCreator 2014-11-13T05:43:00
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RepairCenter
TEMPLATE = app
VERSION = 0.1a

include(../QtRpt/QtRpt/QtRpt.pri)
include($$PWD/../config.pri)

#DESTDIR = $${DEST_DIRECTORY}

SOURCES += main.cpp\
        mainwindow.cpp \
    createdbdialog.cpp \
    dbsettingsdialog.cpp \
    editorder.cpp \
    catemployees.cpp \
    catconstants.cpp \
    catproducttypes.cpp \
    catcustomers.cpp \
    editworkreport.cpp \
    jrnworkreports.cpp \
    jrndiagreports.cpp \
    editdiagreport.cpp \
    catworktypes.cpp \
    catspares.cpp \
    catsparetypes.cpp \
    giveorder.cpp

HEADERS  += mainwindow.h \
    createdbdialog.h \
    dbsettingsdialog.h \
    dbwork.h \
    editorder.h \
    catemployees.h \
    catconstants.h \
    catproducttypes.h \
    catcustomers.h \
    editworkreport.h \
    jrnworkreports.h \
    jrndiagreports.h \
    editdiagreport.h \
    catworktypes.h \
    catspares.h \
    catsparetypes.h \
    giveorder.h

FORMS    += mainwindow.ui \
    createdbdialog.ui \
    dbsettingsdialog.ui \
    editorder.ui \
    catemployees.ui \
    catconstants.ui \
    catproducttypes.ui \
    catcustomers.ui \
    editworkreport.ui \
    jrnworkreports.ui \
    jrndiagreports.ui \
    editdiagreport.ui \
    catworktypes.ui \
    catspares.ui \
    catsparetypes.ui \
    giveorder.ui

OTHER_FILES += \
    about_code_style.txt \
    print_forms/order.xml \
    db.conf

RESOURCES += \
    Icons.qrc

win32:RC_FILE = appicon.rc
