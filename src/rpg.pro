CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

include(deployment.pri)
qtcAddDeployment()

LIBS += -L"$$PWD/include"
LIBS += -L"$$PWD/include/SFML/lib"

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

TEMPLATE = app

SOURCES += main.cpp \
    inputmanager.cpp \
    state/maingame.cpp \
    mapload.cpp \
    map.cpp

HEADERS += \
    inputmanager.h \
    entity.h \
    entitymanager.h \
    gamestate.h \
    state/maingame.h \
    mapload.h \
    map.h
