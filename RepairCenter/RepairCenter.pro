#-------------------------------------------------
#
# Project created by QtCreator 2014-11-13T05:43:00
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RepairCenter
TEMPLATE = app

include(../QtRpt/QtRPT/QtRPT.pri)
include($$PWD/../config.pri)

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
    ../CommonFiles/README_en.txt \
    ../CommonFiles/print_forms/act_diag_hw.xml \
    ../CommonFiles/print_forms/act_diag.xml \
    ../CommonFiles/print_forms/act_works_hw.xml \
    ../CommonFiles/print_forms/act_works.xml \
    ../CommonFiles/print_forms/order_hw.xml \
    ../CommonFiles/print_forms/order.xml \
    ../CommonFiles/print_forms/warranty_works_hw.xml \
    ../CommonFiles/print_forms/warranty_works.xml \
    ../CommonFiles/help/ru_RU/application.html \
    ../CommonFiles/help/ru_RU/catalogs.html \
    ../CommonFiles/help/ru_RU/firststart.html \
    ../CommonFiles/help/ru_RU/index.html \
    ../CommonFiles/help/ru_RU/install.html \
    ../CommonFiles/help/ru_RU/journals.html \
    ../CommonFiles/help/ru_RU/mainwindow.html \
    ../CommonFiles/help/ru_RU/print_forms.html \
    ../CommonFiles/help/ru_RU/qtrpt.html \
    ../CommonFiles/help/ru_RU/workflow.html \
    ../CommonFiles/Launch QtRptDesigner.sh \
    ../CommonFiles/Launch RepairCenter.sh \
    i18n/repaircenter_en_US.ts \
    i18n/repaircenter_ru_RU.ts \
    ../CommonFiles/help/en_US/application.html \
    ../CommonFiles/help/en_US/catalogs.html \
    ../CommonFiles/help/en_US/dbservice.html \
    ../CommonFiles/help/en_US/firststart.html \
    ../CommonFiles/help/en_US/index.html \
    ../CommonFiles/help/en_US/install.html \
    ../CommonFiles/help/en_US/journals.html \
    ../CommonFiles/help/en_US/mainwindow.html \
    ../CommonFiles/help/en_US/others.html \
    ../CommonFiles/help/en_US/print_forms.html \
    ../CommonFiles/help/en_US/qtrpt.html \
    ../CommonFiles/help/en_US/salaries.html \
    ../CommonFiles/help/en_US/workflow.html \
    ../CommonFiles/help/ru_RU/dbservice.html \
    ../CommonFiles/help/ru_RU/others.html \
    ../CommonFiles/help/ru_RU/salaries.html


RESOURCES += \
    Icons.qrc \
    languages.qrc

TRANSLATIONS += i18n/repaircenter_ru_RU.ts
TRANSLATIONS += i18n/repaircenter_en_US.ts

win32:RC_FILE = appicon.rc

rpcupd.commands = lupdate $$PWD/RepairCenter.pro
rpcrel.commands = lrelease $$PWD/RepairCenter.pro
rpcrel.depends = rpcupd
#translate.commands = $(COPY) *.qm $$DESTDIR/i18n/

QMAKE_EXTRA_TARGETS += rpcupd rpcrel
PRE_TARGETDEPS += rpcrel

cf_copy.commands = $(COPY_DIR) $$PWD/../CommonFiles/* $$DESTDIR
first.depends = $(first) cf_copy
export(first.depends)
export(cf_copy.commands)
QMAKE_EXTRA_TARGETS += first cf_copy

