TEMPLATE = app

QT += qml quick bluetooth

SOURCES += main.cpp \
    connectionmanager.cpp \
    fotonledmessagefactory.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    connectionmanager.h \
    fotonledmessagefactory.h

CONFIG += C++11
