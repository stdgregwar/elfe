#-------------------------------------------------
#
# Project created by QtCreator 2016-10-21T14:02:36
#
#-------------------------------------------------

QT       += core gui

TARGET = BlifLoaderPlugin
TEMPLATE = lib
CONFIG += plugin c++11
CONFIG += no_plugin_name_prefix

DESTDIR = ../../Elve/plugins/loaders

SOURCES += BlifLoader.cpp

HEADERS += BlifLoader.h

INCLUDEPATH += ../../Core/interfaces

#DISTFILES += BlifLoaderPlugin.json

unix {
    target.path = /usr/lib
    #target.path = ../Core/plugins
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../Core/release/ -lElveCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../Core/debug/ -lElveCore
else:unix: LIBS += -L$$OUT_PWD/../../Core/ -lElveCore

INCLUDEPATH += $$PWD/../Core
DEPENDPATH += $$PWD/../Core
