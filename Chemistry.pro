#-------------------------------------------------
#
# Project created by QtCreator 2014-12-12T17:25:23
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chemistry

TEMPLATE = app

SOURCES += main.cpp \
    mainwindow.cpp \
    core.cpp \
    elements_table.cpp \
    inputbox.cpp \
    wizardpage.cpp

HEADERS += mainwindow.h \
    core.h \
    character_set.h \
    elements_table.h \
    inputbox.h \
    wizardpage.h

FORMS += mainwindow.ui \
    inputbox.ui \
    wizardpage.ui

RESOURCES += \
    res.qrc

TRANSLATIONS += chemistry_zh_CN.ts

win32:RC_FILE += scales.rc
