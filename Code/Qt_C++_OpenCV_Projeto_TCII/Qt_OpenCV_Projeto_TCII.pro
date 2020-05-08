#-------------------------------------------------
#
# Project created by QtCreator 2017-10-11T15:53:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt_OpenCV_Projeto_TCII
TEMPLATE = app

INCLUDEPATH += D:\Programas\opencv\build_CMake\include
LIBS += D:\Programas\opencv\build_CMake\lib\libopencv_world310.dll.a

SOURCES += main.cpp\
        mainwindow.cpp \
    configinputs.cpp \
    setinput.cpp \
    configprocess.cpp \
    addpartdefault.cpp \
    infoabout.cpp

HEADERS  += mainwindow.h \
    configinputs.h \
    setinput.h \
    configprocess.h \
    addpartdefault.h \
    infoabout.h

FORMS    += mainwindow.ui \
    configinputs.ui \
    setinput.ui \
    configprocess.ui \
    addpartdefault.ui \
    infoabout.ui

RESOURCES += \
    resources.qrc
