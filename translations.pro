TEMPLATE = subdirs

rpcupd.commands = lupdate $$PWD/RepairCenter/RepairCenter.pro
rpcrel.commands = lrelease $$PWD/RepairCenter/RepairCenter.pro
rpcrel.depends = rpcupd

dbtupd.commands = lupdate $$PWD/DBTool/DBTool.pro
dbtrel.commands = lrelease $$PWD/DBTool/DBTool.pro
dbtrel.depends = dbtupd

QMAKE_EXTRA_TARGETS += dbtupd dbtrel rpcupd rpcrel

#translate.commands = $(COPY) *.qm $$DESTDIR/i18n/
