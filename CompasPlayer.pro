#-------------------------------------------------
#
# Project created by QtCreator 2015-07-23T18:46:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CompasPlayer
TEMPLATE = app




SOURCES += main.cpp\
        mainwindow.cpp \
    gestionxml.cpp \
    lecteur.cpp \
    pattern.cpp \
    son.cpp \
    subtemps.cpp \
    temps.cpp \
    tinyxml2.cpp

HEADERS  += mainwindow.h \
    gestionxml.h \
    lecteur.h \
    pattern.h \
    son.h \
    subtemps.h \
    temps.h \
    tinyxml2.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../_libraries/SFML-2.3.1/monBuild/lib/ -lsfml-audio -lsfml-system
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../_libraries/SFML-2.3.1/monBuild/lib/ -lsfml-audio -lsfml-system

CONFIG += static

INCLUDEPATH += $$PWD/../_libraries/SFML-2.3.1/include
DEPENDPATH += $$PWD/../_libraries/SFML-2.3.1/monBuild
