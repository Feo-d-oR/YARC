REPAIRC_VERSION = v0.4

win32{
    TARGET_CUSTOM_EXT = .exe
    DEPLOY_COMMAND = windeployqt

    CONFIG(debug, debug|release) {
        DEPLOY_TARGET = $$shell_quote($$shell_path($$PWD/../RepairCenter_$${REPAIRC_VERSION}_windows_x86_Qt$$[QT_VERSION]_binary/debug/$${TARGET}$${TARGET_CUSTOM_EXT}))
        DEST_DIRECTORY = $$shell_quote($$shell_path($$PWD/../RepairCenter_$${REPAIRC_VERSION}_windows_x86_Qt$$[QT_VERSION]_binary/debug))
    }
    CONFIG(release, debug|release) {
        DEPLOY_TARGET = $$shell_quote($$shell_path($$PWD/../RepairCenter_$${REPAIRC_VERSION}_windows_x86_Qt$$[QT_VERSION]_binary/$${TARGET}$${TARGET_CUSTOM_EXT}))
        DEST_DIRECTORY = $$shell_quote($$shell_path($$PWD/../RepairCenter_$${REPAIRC_VERSION}_windows_x86_Qt$$[QT_VERSION]_binary))
    }
    QMAKE_POST_LINK = $${DEPLOY_COMMAND} $${DEPLOY_TARGET}
#    DEST_DIRECTORY ~= s,/,\\,g
}

linux-g++-64{
    CONFIG(debug, debug|release) {
        DEST_DIRECTORY = $$PWD/../RepairCenter_$${REPAIRC_VERSION}_linux_x64_Qt$$[QT_VERSION]_binary/debug
    }
    CONFIG(release, debug|release) {
        DEST_DIRECTORY = $$PWD/../RepairCenter_$${REPAIRC_VERSION}_linux_x64_Qt$$[QT_VERSION]_binary
    }
}

linux-g++{
    CONFIG(debug, debug|release) {
        DEST_DIRECTORY = $$PWD/../RepairCenter_$${REPAIRC_VERSION}_linux_x86_Qt$$[QT_VERSION]_binary/debug
    }
    CONFIG(release, debug|release) {
        DEST_DIRECTORY = $$PWD/../RepairCenter_$${REPAIRC_VERSION}_linux_x86_Qt$$[QT_VERSION]_binary
    }
}

PROJECT_ROOT_DIRECTORY = $$PWD #not $$_PRO_FILE_PWD_!
DESTDIR = $${DEST_DIRECTORY}
