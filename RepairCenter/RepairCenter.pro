#-------------------------------------------------
#
# Project created by QtCreator 2014-11-13T05:43:00
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RepairCenter
TEMPLATE = app
VERSION = 0.3

include(../QtRpt/QtRpt/QtRpt.pri)
include($$PWD/../config.pri)

DESTDIR = $${DEST_DIRECTORY}

SOURCES += main.cpp\
        mainwindow.cpp \
    editorder.cpp \
    catemployees.cpp \
    catproducttypes.cpp \
    catcustomers.cpp \
    editworkreport.cpp \
    jrnworkreports.cpp \
    jrndiagreports.cpp \
    editdiagreport.cpp \
    catworktypes.cpp \
    catspares.cpp \
    catsparetypes.cpp \
    giveorder.cpp \
    settings.cpp \
    giveorderdiag.cpp \
    printhwdocuments.cpp

HEADERS  += mainwindow.h \
    editorder.h \
    catemployees.h \
    catproducttypes.h \
    catcustomers.h \
    editworkreport.h \
    jrnworkreports.h \
    jrndiagreports.h \
    editdiagreport.h \
    catworktypes.h \
    catspares.h \
    catsparetypes.h \
    giveorder.h \
    settings.h \
    giveorderdiag.h \
    printhwdocuments.h

FORMS    += mainwindow.ui \
    editorder.ui \
    catemployees.ui \
    catproducttypes.ui \
    catcustomers.ui \
    editworkreport.ui \
    jrnworkreports.ui \
    jrndiagreports.ui \
    editdiagreport.ui \
    catworktypes.ui \
    catspares.ui \
    catsparetypes.ui \
    giveorder.ui \
    settings.ui \
    giveorderdiag.ui \
    printhwdocuments.ui

OTHER_FILES += \
    about_code_style.txt \
    print_forms/order.xml \
    db.conf \
    i18n/README_en.txt \
    help/RU_ru/application.html \
    help/RU_ru/catalogs.html \
    help/RU_ru/firststart.html \
    help/RU_ru/index.html \
    help/RU_ru/install.html \
    help/RU_ru/journals.html \
    help/RU_ru/mainwindow.html \
    help/RU_ru/print_forms.html \
    help/RU_ru/qtrpt.html \
    help/RU_ru/workflow.html \
    ../print_forms/act_diag.xml \
    ../print_forms/act_works.xml \
    ../print_forms/order.xml \
    ../print_forms/warranty_works.xml \
    ../print_forms/act_diag_hw.xml \
    ../print_forms/act_works_hw.xml \
    ../print_forms/order_hw.xml \
    ../print_forms/warranty_works_hw.xml

RESOURCES += \
    Icons.qrc \
    languages.qrc

TRANSLATIONS += i18n/repaircenter_ru_RU.ts
TRANSLATIONS += i18n/repaircenter_en_US.ts

OTHER_FILES += \
    i18n/repaircenter_ru_RU.ts \
    i18n/repaircenter_en_US.ts

win32:RC_FILE = appicon.rc
