CONFIG(debug, debug|release) {
    DEST_DIRECTORY = $$PWD/../RepairCenter_bin/debug
}
CONFIG(release, debug|release) {
    DEST_DIRECTORY = $$PWD/../RepairCenter_bin/release
}
PROJECT_ROOT_DIRECTORY = $$PWD #not $$_PRO_FILE_PWD_!

DESTDIR = $${DEST_DIRECTORY}
