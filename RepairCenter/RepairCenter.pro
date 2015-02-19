#-------------------------------------------------
#
# Project created by QtCreator 2014-11-13T05:43:00
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RepairCenter
TEMPLATE = app

include(../QtRpt/QtRpt/QtRpt.pri)
include($$PWD/../config.pri)

#DESTDIR = $${DEST_DIRECTORY}

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
    printhwdocuments.cpp \
    about.cpp \
    salaries.cpp

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
    printhwdocuments.h \
    about.h \
    salaries.h

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
    printhwdocuments.ui \
    about.ui \
    salaries.ui

OTHER_FILES += \
    about_code_style.txt \
    print_forms/order.xml \
    db.conf \
    ../CommonFiles/README_en.txt \
    ../CommonFiles/setting.ini \
    ../CommonFiles/print_forms/act_diag_hw.xml \
    ../CommonFiles/print_forms/act_diag.xml \
    ../CommonFiles/print_forms/act_works_hw.xml \
    ../CommonFiles/print_forms/act_works.xml \
    ../CommonFiles/print_forms/order_hw.xml \
    ../CommonFiles/print_forms/order.xml \
    ../CommonFiles/print_forms/warranty_works_hw.xml \
    ../CommonFiles/print_forms/warranty_works.xml \
    ../CommonFiles/help/RU_ru/application.html \
    ../CommonFiles/help/RU_ru/catalogs.html \
    ../CommonFiles/help/RU_ru/firststart.html \
    ../CommonFiles/help/RU_ru/index.html \
    ../CommonFiles/help/RU_ru/install.html \
    ../CommonFiles/help/RU_ru/journals.html \
    ../CommonFiles/help/RU_ru/mainwindow.html \
    ../CommonFiles/help/RU_ru/print_forms.html \
    ../CommonFiles/help/RU_ru/qtrpt.html \
    ../CommonFiles/help/RU_ru/workflow.html

RESOURCES += \
    Icons.qrc \
    languages.qrc

TRANSLATIONS += i18n/repaircenter_ru_RU.ts
TRANSLATIONS += i18n/repaircenter_en_US.ts

OTHER_FILES += \
    i18n/repaircenter_ru_RU.ts \
    i18n/repaircenter_en_US.ts

win32:RC_FILE = appicon.rc
