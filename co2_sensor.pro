#-------------------------------------------------
#
# Project created by QtCreator 2015-11-17T09:24:06
#
#-------------------------------------------------

QT       += core gui script printsupport network scripttools

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = co2_sensor
#CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app
unix | win32-g++:{
    QMAKE_CXXFLAGS += -isystem $$[QT_INSTALL_HEADERS]
    QMAKE_CXXFLAGS += -isystem $$[QT_INSTALL_HEADERS]/QtCore
    QMAKE_CXXFLAGS += -isystem $$[QT_INSTALL_HEADERS]/QtGui
    QMAKE_CXXFLAGS += -isystem $$[QT_INSTALL_HEADERS]/QtScript
    QMAKE_CXXFLAGS += -isystem $$[QT_INSTALL_HEADERS]/QtWidgets
    QMAKE_CXXFLAGS += -isystem $$PWD/../libusb-1.0.20/qcustomplot
    #QMAKE_CXXFLAGS += -isystem $$PWD/../libusb-1.0.20/include/libusb-1.0
    QMAKE_CXXFLAGS += -Wall
    QMAKE_CXXFLAGS += -Wextra
    QMAKE_CXXFLAGS += -ansi
    QMAKE_CXXFLAGS += -pedantic
    QMAKE_CXXFLAGS += -Wshadow
    QMAKE_CXXFLAGS += -Weffc++
    QMAKE_CXXFLAGS += -Wstrict-aliasing
}

CONFIG += c++11


SOURCES += main.cpp \
    qt_co2_sensor.cpp \
    co2_sensor_read_thread.cpp \
    sensor_output.cpp \
    sensor_gui.cpp

HEADERS += \
    qt_co2_sensor.h \
    co2_sensor_read_thread.h \
    sensor_output.h \
    sensor_gui.h


#=============
#== LIB USB ==
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libusb-1.0.20/MinGW32/dll/ -llibusb-1.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libusb-1.0.20/MinGW32/dll/ -llibusb-1.0
else:unix: CONFIG(release, debug|release): LIBS +=-lusb-1.0
else:unix: CONFIG(debug, debug|release): LIBS +=-lusb-1.0

INCLUDEPATH += $$PWD/../libusb-1.0.20/include
DEPENDPATH += $$PWD/../libusb-1.0.20/include
#=============

#===================
#== Q CUSTOM PLOT ==
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../build-qcustomplot-Desktop_Qt_5_5_0_MinGW-Release/release/ -lqcustomplot
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../build-qcustomplot-Desktop_Qt_5_5_0_MinGW-Debug/debug/ -lqcustomplot
else:unix: CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../build-qcustomplot-Desktop_Qt_5_5_0_GCC_64bit-Release/ -lqcustomplot
else:unix: CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../build-qcustomplot-Desktop_Qt_5_5_0_GCC_64bit-Debug/ -lqcustomplot

INCLUDEPATH += $$PWD/../qcustomplot
DEPENDPATH += $$PWD/../qcustomplot

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../build-qcustomplot-Desktop_Qt_5_5_0_MinGW-Release/release/libqcustomplot.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../build-qcustomplot-Desktop_Qt_5_5_0_MinGW-Debug/debug/libqcustomplot.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../build-qcustomplot-Desktop_Qt_5_5_0_MinGW-Release/release/qcustomplot.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../build-qcustomplot-Desktop_Qt_5_5_0_MinGW-Debug/debug/qcustomplot.lib
#===================

