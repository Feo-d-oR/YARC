REPAIRC_VERSION = v0.3

win32{
    CONFIG(debug, debug|release) {
        DEST_DIRECTORY = $$PWD/../RepairCenter_$${REPAIRC_VERSION}_windows_x86_Qt$$[QT_VERSION]_binary/debug
    }
    CONFIG(release, debug|release) {
        DEST_DIRECTORY = $$PWD/../RepairCenter_$${REPAIRC_VERSION}_windows_x86_Qt$$[QT_VERSION]_binary
    }
    DEST_DIRECTORY ~= s,/,\\,g
}

linux-g++-64{
    CONFIG(debug, debug|release) {
        DEST_DIRECTORY = $$PWD/../RepairCenter_$${REPAIRC_VERSION}_linux_x64_Qt$$[QT_VERSION]_binary/debug
    }
    CONFIG(release, debug|release) {
        DEST_DIRECTORY = $$PWD/../RepairCenter_$${REPAIRC_VERSION}_linux_x64_$$[QT_VERSION]_binary
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
