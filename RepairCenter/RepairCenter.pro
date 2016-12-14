#-------------------------------------------------
#
# Project created by QtCreator 2014-11-13T05:43:00
#
#-------------------------------------------------

QT += core gui sql

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
    salaries.cpp \
    orderswidgetmain.cpp \
    orderswidgetmaster.cpp \
    simplecrypt.cpp \
    catsuppliers.cpp \
    editpartsrequest.cpp \
    jrnpartsrequests.cpp \
    partswidgetstorekeeper.cpp

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
    salaries.h \
    orderswidgetmain.h \
    orderswidgetmaster.h \
    simplecrypt.h \
    catsuppliers.h \
    editpartsrequest.h \
    jrnpartsrequests.h \
    partswidgetstorekeeper.h

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
    salaries.ui \
    orderswidgetmain.ui \
    orderswidgetmaster.ui \
    catsuppliers.ui \
    editpartsrequest.ui \
    jrnpartsrequests.ui \
    partswidgetstorekeeper.ui

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
#    i18n/repaircenter_nl_NL.ts \

RESOURCES += \
    Icons.qrc

TRANSLATIONS += i18n/repaircenter_ru_RU.ts
TRANSLATIONS += i18n/repaircenter_en_US.ts
#TRANSLATIONS += i18n/repaircenter_nl_NL.ts

win32:RC_FILE = appicon.rc

rpcupd.commands = lupdate $$PWD/RepairCenter.pro
rpcrel.commands = lrelease $$PWD/RepairCenter.pro
rpcrel.depends = rpcupd

QMAKE_EXTRA_TARGETS += rpcupd rpcrel

cf_copy.commands = $(COPY_DIR) $$shell_path($$PWD/../CommonFiles/*) $$shell_path($$DESTDIR)

first.depends = $(first) cf_copy
export(first.depends)
export(cf_copy.commands)

md.commands = $(MKDIR) $$shell_path($$DESTDIR/i18n/)
tl_copy.commands += $(COPY) $$shell_path($$PWD/i18n/*.qm) $$shell_path($$DESTDIR/i18n)
tl_copy.depends = rpcrel md

QMAKE_EXTRA_TARGETS += md first cf_copy tl_copy

PRE_TARGETDEPS += tl_copy


