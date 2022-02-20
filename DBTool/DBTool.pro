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
    dbwork.cpp \
    simplecrypt.cpp

HEADERS  += mainwindow.h \
    dbwork.h \
    simplecrypt.h

FORMS    += mainwindow.ui

RESOURCES += \
    Icons.qrc

TRANSLATIONS += i18n/dbtool_ru_RU.ts
TRANSLATIONS += i18n/dbtool_en_US.ts
TRANSLATIONS += i18n/dbtool_it_IT.ts
#TRANSLATIONS += i18n/dbtool_nl_NL.ts

OTHER_FILES += \
    i18n/dbtool_ru_RU.ts \
    i18n/dbtool_en_US.ts \
    i18n/dbtool_it_IT.ts \
#    i18n/dbtool_nl_NL.ts

dbtupd.commands = lupdate $$PWD/DBTool.pro
dbtrel.commands = lrelease $$PWD/DBTool.pro
dbtrel.depends = dbtupd

if ( ! exists( $$shell_path($$DESTDIR/i18n/) ) )
{
    message("Creating $$shell_path($$DESTDIR/i18n/)")
    md.commands = $(MKDIR) $$shell_path($$DESTDIR/i18n/)
}
if ( exists( $$shell_path($$DESTDIR/i18n/) ) )
{
    message("Skipping $$shell_path($$DESTDIR/i18n/)")
    md.commands = echo skip $(MKDIR) $$shell_path($$DESTDIR/i18n/)
}

#exists ( $$shell_path($$DESTDIR/i18n/) )
#{
#    message("Creating $$shell_path($$DESTDIR/i18n/)")
#    md.commands = $(MKDIR) $$shell_path($$DESTDIR/i18n/)
#}

tl_copy.commands += $(COPY) $$shell_path($$PWD/i18n/*.qm) $$shell_path($$DESTDIR/i18n)
tl_copy.depends = dbtrel #md

QMAKE_EXTRA_TARGETS += dbtupd dbtrel tl_copy # md
PRE_TARGETDEPS += tl_copy

