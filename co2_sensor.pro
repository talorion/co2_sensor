#-------------------------------------------------
#
# Project created by QtCreator 2015-11-17T09:24:06
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = co2_sensor
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    qt_co2_sensor.cpp \
    co2_sensor_read_thread.cpp \
    sensor_output.cpp



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libusb-1.0.20/MinGW32/dll/ -llibusb-1.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libusb-1.0.20/MinGW32/dll/ -llibusb-1.0

INCLUDEPATH += $$PWD/../libusb-1.0.20/include/libusb-1.0
DEPENDPATH += $$PWD/../libusb-1.0.20/include/libusb-1.0

HEADERS += \
    qt_co2_sensor.h \
    co2_sensor_read_thread.h \
    sensor_output.h
