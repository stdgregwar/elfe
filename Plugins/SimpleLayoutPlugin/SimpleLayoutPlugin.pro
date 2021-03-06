#-------------------------------------------------
#
# Project created by QtCreator 2016-10-28T14:23:10
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = SimpleLayoutPlugin
TEMPLATE = lib
CONFIG += plugin c++11
CONFIG += no_plugin_name_prefix

DESTDIR = ../../Elve/plugins/layouts

unix {
    target.path = ~/.elve/plugins/layouts
    INSTALLS += target
}


INCLUDEPATH+= ../../Core/interfaces
INCLUDEPATH += ../../Core

LIBS += -L$$OUT_PWD/../../Core/ -lElveCore
win32:LIBS += -lboost_system-mt -lboost_program_options-mt -lboost_regex-mt -lboost_filesystem-mt

SOURCES += \
    SimpleLayout.cpp

HEADERS += \
    SimpleLayout.h
DISTFILES +=
