#-------------------------------------------------
#
# Project created by QtCreator 2014-11-13T05:43:00
#
#-------------------------------------------------

QT += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RepairCenter
TEMPLATE = app

QMAKE_CXXFLAGS += -std=gnu++11

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
    partswidgetstorekeeper.cpp \
    orderslog.cpp

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
    partswidgetstorekeeper.h \
    orderslog.h

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
    partswidgetstorekeeper.ui \
    orderslog.ui

OTHER_FILES += \
    ../CommonFiles/print_forms/act_diag_hw.xml \
    ../CommonFiles/print_forms/act_diag.xml \
    ../CommonFiles/print_forms/act_works_hw.xml \
    ../CommonFiles/print_forms/act_works.xml \
    ../CommonFiles/print_forms/order_hw.xml \
    ../CommonFiles/print_forms/order.xml \
    ../CommonFiles/print_forms/warranty_works_hw.xml \
    ../CommonFiles/print_forms/warranty_works.xml \
    i18n/repaircenter_en_US.ts \
    i18n/repaircenter_ru_RU.ts \
#    i18n/repaircenter_nl_NL.ts \

DISTFILES += \
    ../CommonFiles/CHANGELOG.txt \
    ../CommonFiles/README.txt \
    repaircenter.conf

RESOURCES += \
    Icons.qrc

win32:RC_FILE = appicon.rc

TRANSLATIONS += i18n/repaircenter_ru_RU.ts
TRANSLATIONS += i18n/repaircenter_en_US.ts
#TRANSLATIONS += i18n/repaircenter_nl_NL.ts

rpcupd.commands = lupdate $$PWD/RepairCenter.pro
rpcrel.commands = lrelease $$PWD/RepairCenter.pro
rpcrel.depends = rpcupd

cf_copy.commands += $(COPY_DIR) $$shell_path($$PWD/../CommonFiles/*) $$shell_path($$DESTDIR)
#var_copy.commands += $(COPY) $$shell_path($$PWD/repaircenter.conf) $$shell_path($$DESTDIR)

md.commands = $(MKDIR) $$shell_path($$DESTDIR/i18n/)
tl_copy.commands += $(COPY) $$shell_path($$PWD/i18n/*.qm) $$shell_path($$DESTDIR/i18n)
tl_copy.depends = rpcrel md

QMAKE_EXTRA_TARGETS += md cf_copy tl_copy rpcupd rpcrel first #var_copy
first.depends = $(first) cf_copy tl_copy #var_copy


