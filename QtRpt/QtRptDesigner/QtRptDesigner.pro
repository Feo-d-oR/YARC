#-------------------------------------------------
#
# Project created by QtCreator 2012-03-29T16:09:02
#
#-------------------------------------------------

QT       += core gui xml network

greaterThan(QT_MAJOR_VERSION, 4){
    QT += widgets
    DEFINES += HAVE_QT5
}

TARGET = QtRptDesigner
VERSION = 1.4.5
DEFINES += VERSION=\\\"$$VERSION\\\"
TEMPLATE = app

include(../CommonFiles/CommonFiles_QtRptDesigner.pri)
include(../QtRpt/QtRpt.pri)
include(SQLDiagram/SQLDiagram.pri)

SOURCES += main.cpp\
    mainwindow.cpp \
    PageSettingDlg.cpp \
    ReportBand.cpp \
    RptContainer.cpp \
    EditFldDlg.cpp \
    aboutDlg.cpp \
    FldPropertyDlg.cpp \
    RepScrollArea.cpp \
    SettingDlg.cpp \
    overlay.cpp \
    SqlDesigner.cpp \
    TContainerLine.cpp \
    TContainerField.cpp \
    UndoCommands.cpp

HEADERS  += mainwindow.h \
    PageSettingDlg.h \
    ReportBand.h \
    RptContainer.h \
    EditFldDlg.h \
    aboutDlg.h \
    FldPropertyDlg.h \
    RepScrollArea.h \
    SettingDlg.h \
    overlay.h \
    SqlDesigner.h \
    TContainerLine.h \
    TContainerField.h \
    UndoCommands.h

FORMS    += mainwindow.ui \
    PageSettingDlg.ui \
    ReportBand.ui \
    EditFldDlg.ui \
    FldPropertyDlg.ui \
    RepScrollArea.ui \
    SettingDlg.ui \
    SqlDesigner.ui

RESOURCES += \
    images.qrc

RC_FILE = QtRptDesigner.rc

TRANSLATIONS += i18n/QtRprtDesigner_uk_UA.ts
TRANSLATIONS += i18n/QtRprtDesigner_sr_RS.ts
TRANSLATIONS += i18n/QtRprtDesigner_sr_RS@latin.ts
TRANSLATIONS += i18n/QtRprtDesigner_ar.ts
TRANSLATIONS += i18n/QtRprtDesigner_ka_GE.ts
TRANSLATIONS += i18n/QtRprtDesigner_pt_PT.ts
TRANSLATIONS += i18n/QtRprtDesigner_zh_CN.ts

OTHER_FILES += \
    i18n/QtRprtDesigner_ar.ts \
    i18n/QtRprtDesigner_sr_RS.ts \
    i18n/QtRprtDesigner_sr_RS@latin.ts \
    i18n/QtRprtDesigner_uk_UA.ts \
    i18n/QtRprtDesigner_ka_GE.ts \
    i18n/QtRprtDesigner_pt_PT.ts \
    i18n/QtRprtDesigner_zh_CN.ts

win32 {
    MOC_DIR = tmp-win32
    #UI_DIR = tmp-win32
    #UI_HEADERS_DIR = tmp-win32
    #UI_SOURCES_DIR = tmp-win32
    OBJECTS_DIR = tmp-win32
    RCC_DIR = tmp-win32
}

linux {
    MOC_DIR = tmp-lin64
    #UI_DIR = tmp-lin64
    #UI_HEADERS_DIR = tmp-lin64
    #UI_SOURCES_DIR = tmp-lin64
    OBJECTS_DIR = tmp-lin64
    RCC_DIR = tmp-lin64
}

CONFIG += c++11
