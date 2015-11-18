#-------------------------------------------------
#
# Project created by QtCreator 2015-11-17T09:24:06
#
#-------------------------------------------------

QT       += core gui script printsupport network scripttools

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = co2_sensor
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

win32-g++: QMAKE_CXXFLAGS += -isystem $$[QT_INSTALL_HEADERS]
win32-g++: QMAKE_CXXFLAGS += -isystem $$[QT_INSTALL_HEADERS]/QtCore
win32-g++: QMAKE_CXXFLAGS += -isystem $$[QT_INSTALL_HEADERS]/QtGui
win32-g++: QMAKE_CXXFLAGS += -isystem $$[QT_INSTALL_HEADERS]/QtScript
win32-g++: QMAKE_CXXFLAGS += -isystem $$[QT_INSTALL_HEADERS]/QtWidgets
win32-g++: QMAKE_CXXFLAGS += -isystem $$PWD/../libusb-1.0.20/qcustomplot
win32-g++: QMAKE_CXXFLAGS += -isystem $$PWD/../libusb-1.0.20/include/libusb-1.0
win32-g++: QMAKE_CXXFLAGS += -Wall
win32-g++: QMAKE_CXXFLAGS += -Wextra
win32-g++: QMAKE_CXXFLAGS += -ansi
win32-g++: QMAKE_CXXFLAGS += -pedantic
win32-g++: QMAKE_CXXFLAGS += -Wshadow
win32-g++: QMAKE_CXXFLAGS += -Weffc++
win32-g++: QMAKE_CXXFLAGS += -Wstrict-aliasing

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

INCLUDEPATH += $$PWD/../libusb-1.0.20/include/libusb-1.0
DEPENDPATH += $$PWD/../libusb-1.0.20/include/libusb-1.0

#=============

#===================
#== Q CUSTOM PLOT ==
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../build-qcustomplot-Desktop_Qt_5_5_0_MinGW-Release/release/ -lqcustomplot
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../build-qcustomplot-Desktop_Qt_5_5_0_MinGW-Debug/debug/ -lqcustomplot
else:unix: LIBS += -L$$OUT_PWD/../qcustomplot/ -lqcustomplot

INCLUDEPATH += $$PWD/../qcustomplot
DEPENDPATH += $$PWD/../qcustomplot

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../build-qcustomplot-Desktop_Qt_5_5_0_MinGW-Release/release/libqcustomplot.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../build-qcustomplot-Desktop_Qt_5_5_0_MinGW-Debug/debug/libqcustomplot.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../build-qcustomplot-Desktop_Qt_5_5_0_MinGW-Release/release/qcustomplot.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../build-qcustomplot-Desktop_Qt_5_5_0_MinGW-Debug/debug/qcustomplot.lib
#===================

