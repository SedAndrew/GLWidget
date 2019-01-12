#-------------------------------------------------
#
# Project created by QtCreator 2018-12-12T22:38:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GLWidget
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


win32-g* {
 LIBS += -lopengl32
}

win32-msvc* {
 LIBS += opengl32.lib
}

SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    simpleobject3d.cpp \
    camera3d.cpp \
    group3d.cpp \
    skybox.cpp \
    material.cpp \
    materiallibrary.cpp \
    objectengine3d.cpp \
    light.cpp \
    lightwidget.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    simpleobject3d.h \
    camera3d.h \
    group3d.h \
    transformational.h \
    skybox.h \
    material.h \
    materiallibrary.h \
    objectengine3d.h \
    global.h \
    light.h \
    lightwidget.h \
    transparencycheck.h

FORMS    += \
    mainwindow.ui

CONFIG += resources_big

RESOURCES += \
    textures.qrc \
    shaders.qrc \
    skybox.qrc \
    modeles.qrc

DISTFILES +=
