INCLUDEPATH += $$PWD

INCLUDEPATH += $$PWD/../zint-2.4.4/backend_qt4
INCLUDEPATH += $$PWD/../zint-2.4.4/backend

SOURCES += $$PWD/CommonClasses.cpp \
           $$PWD/chart.cpp \
           $$PWD/Barcode.cpp
HEADERS += $$PWD/CommonClasses.h \
           $$PWD/chart.h \
           $$PWD/Barcode.h

include($$PWD/../../config.pri)

LIBS += -L $$DEST_DIRECTORY/lib -lQtZint

