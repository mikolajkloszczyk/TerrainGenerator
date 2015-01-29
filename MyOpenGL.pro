#-------------------------------------------------
#
# Project created by QtCreator 2013-09-25T09:11:42
#
#-------------------------------------------------
QT       += core gui opengl widgets
    QMAKE_CXXFLAGS += -fopenmp -mavx -fabi-version=0 -ffast-math
    QMAKE_LFLAGS += -fopenmp
    QMAKE_CXXFLAGS_RELEASE *= -O3

TARGET = MyOpenGL
TEMPLATE = app
CONFIG += c++11

FORMS += \
    createmapprogresdialog.ui \
    mapgeneratedialog.ui \
    window.ui

HEADERS += \
    camera.h \
    createmapprogresdialog.h \
    errorlog.h \
    map.h \
    mapdrawer.h \
    mapgeneratedialog.h \
    mapinfo.h \
    model.h \
    myglwidget.h \
    window.h \
    xmlreader.h \
    perlinnoise.h

SOURCES += \
    camera.cpp \
    createmapprogresdialog.cpp \
    errorlog.cpp \
    main.cpp \
    map.cpp \
    mapdrawer.cpp \
    mapgeneratedialog.cpp \
    mapinfo.cpp \
    model.cpp \
    myglwidget.cpp \
    window.cpp \
    xmlreader.cpp \
    perlinnoise.cpp


