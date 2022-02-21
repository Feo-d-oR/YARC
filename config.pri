REPAIRC_VERSION = v0.4.2

#DEFINES += AUTO_DEPLOY     #select either
#DEFINES += MANUAL_DEPLOY

CONFIG += optimize_full
QMAKE_CXXFLAGS += -std=gnu++11

win32 {
    TARGET_CUSTOM_EXT = .exe

    CONFIG(debug, debug|release) {
        DEPLOY_TARGET = $$shell_quote($$shell_path($$PWD/../RepairCenter_$${REPAIRC_VERSION}_windows_x86_Qt$${QT_VERSION}_binary/debug/$${TARGET}$${TARGET_CUSTOM_EXT}))
        DEST_DIRECTORY = $$shell_quote($$shell_path($$PWD/../RepairCenter_$${REPAIRC_VERSION}_windows_x86_Qt$${QT_VERSION}_binary/debug))
    } else {
        DEPLOY_TARGET = $$shell_quote($$shell_path($$PWD/../RepairCenter_$${REPAIRC_VERSION}_windows_x86_Qt$${QT_VERSION}_binary/$${TARGET}$${TARGET_CUSTOM_EXT}))
        DEST_DIRECTORY = $$shell_quote($$shell_path($$PWD/../RepairCenter_$${REPAIRC_VERSION}_windows_x86_Qt$${QT_VERSION}_binary))
    }

#    contains(DEFINES,AUTO_DEPLOY) {
#        DEPLOY_COMMAND = windeployqt
#        QMAKE_POST_LINK = $${DEPLOY_COMMAND} $${DEPLOY_TARGET}
#    } else {
#        QMAKE_POST_LINK += $(COPY) $$[QT_INSTALL_BINS]/Qt5Core.dll $${DEST_DIRECTORY}
#        QMAKE_POST_LINK += $(COPY) $$[QT_INSTALL_BINS]/Qt5Sql.dll $${DEST_DIRECTORY}
#        QMAKE_POST_LINK += $(COPY) $$[QT_INSTALL_BINS]/Qt5Gui.dll $${DEST_DIRECTORY}
#        QMAKE_POST_LINK += $(COPY) $$[QT_INSTALL_BINS]/Qt5Widgets.dll $${DEST_DIRECTORY}
#        QMAKE_POST_LINK += $(COPY) $$[QT_INSTALL_BINS]/Qt5Network.dll $${DEST_DIRECTORY}
#    }
}

linux-g++-64{
    CONFIG(debug, debug|release) {
        DEST_DIRECTORY = $$PWD/../RepairCenter_$${REPAIRC_VERSION}_linux_x64_Qt$$[QT_VERSION]_binary/debug
    } else {
        DEST_DIRECTORY = $$PWD/../RepairCenter_$${REPAIRC_VERSION}_linux_x64_Qt$$[QT_VERSION]_binary
    }
}

linux-g++{
    CONFIG(debug, debug|release) {
        DEST_DIRECTORY = $$PWD/../RepairCenter_$${REPAIRC_VERSION}_linux_x86_Qt$$[QT_VERSION]_binary/debug
    } else {
        DEST_DIRECTORY = $$PWD/../RepairCenter_$${REPAIRC_VERSION}_linux_x86_Qt$$[QT_VERSION]_binary
    }
}

PROJECT_ROOT_DIRECTORY = $$PWD #not $$_PRO_FILE_PWD_!
DESTDIR = $${DEST_DIRECTORY}
