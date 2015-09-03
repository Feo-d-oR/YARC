TEMPLATE = subdirs   

SUBDIRS = DBTool RepairCenter
#SUBDIRS += QtRpt/QtRptDesigner

#Un-remark this line, if you want to buld QtRPT as a library
#DEFINES += QTRPT_LIBRARY
#contains(DEFINES,QTRPT_LIBRARY) {
#    SUBDIRS += QtRPT
#}

#prj2.file = $$PWD/translations.pro

CONFIG += ordered
