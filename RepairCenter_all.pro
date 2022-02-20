TEMPLATE = subdirs

# Comment to not build excessive
SUBDIRS += RepairCenter
SUBDIRS += DBTool
SUBDIRS += QtRpt/QtRptDesigner  #uncomment to build QtRptDesigner (last thing to do)#

#Un-remark this line, if you want to buld QtRPT as a library
DEFINES += QTRPT_LIBRARY
contains(DEFINES,QTRPT_LIBRARY) {
    SUBDIRS += QtRpt/QtRPT
}


CONFIG += ordered
