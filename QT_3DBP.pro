#-------------------------------------------------
#
# Project created by QtCreator 2022-06-01T17:57:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QT_3DBP
TEMPLATE = app
RC_ICONS = $$PWD/resources/images/logo_3d.ico
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        addwindow.cpp \
        datawindow.cpp \
        load_window.cpp \
        main.cpp \
        mainwindow.cpp \
        multiselectcombobox.cpp \
        osg_widget.cpp \
        packing.cpp

HEADERS += \
        addwindow.h \
        datawindow.h \
        load_window.h \
        mainwindow.h \
        multiselectcombobox.h \
        osg_widget.h \
        packing.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


win32: LIBS += -L$$PWD/packages/lib/ -losgQOpenGL -losg -losgViewer -lOpenThreads -losgGA -losgDB -losgAnimation
INCLUDEPATH += $$PWD/packages/include
DEPENDPATH += $$PWD/release/packages/include

win32: LIBS += -L$$PWD/python38/libs/ -lpython3

INCLUDEPATH += $$PWD/python38/include
DEPENDPATH += $$PWD/python38/include

RESOURCES += \
    image.qrc \
    logo.qrc \
    pys.qrc

DISTFILES += \
    resources/images/logo_3d.ico
