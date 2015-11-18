//#include <QCoreApplication>
#include <QApplication>
#include <QTimer>
#include <QDebug>
#include <QByteArray>
#include <QObject>

#include "co2_sensor_read_thread.h"
#include "sensor_output.h"
#include "sensor_gui.h"



int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    QApplication a(argc, argv);

    //QTimer::singleShot(30000, &a, SLOT(quit()));

    co2_sensor_read_thread thrd;

    sensor_output outp;
    QObject::connect(&thrd,SIGNAL(temperature_changed(double)), &outp,SLOT(print_temperature(double)));
    QObject::connect(&thrd,SIGNAL(carbon_dioxide_changed(double)), &outp,SLOT(print_carbon_dioxide(double)));
    QObject::connect(&thrd,SIGNAL(relative_humidity_changed(double)), &outp,SLOT(print_relative_humidity(double)));

    sensor_gui gui;
    QObject::connect(&thrd,SIGNAL(temperature_changed(double)), &gui,SLOT(print_temperature(double)));
    QObject::connect(&thrd,SIGNAL(carbon_dioxide_changed(double)), &gui,SLOT(print_carbon_dioxide(double)));
    QObject::connect(&thrd,SIGNAL(relative_humidity_changed(double)), &gui,SLOT(print_relative_humidity(double)));

    thrd.start();
    gui.show();

    return a.exec();

}
