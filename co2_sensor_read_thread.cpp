#include "co2_sensor_read_thread.h"

#include "qt_co2_sensor.h"

co2_sensor_read_thread::co2_sensor_read_thread(QObject *parent) :
    QThread(parent),
    mutex(),
    abort(false),
    condition()
{

}

co2_sensor_read_thread::~co2_sensor_read_thread()
{
    mutex.lock();
    abort = true;
    condition.wakeOne();
    mutex.unlock();

    wait();
}

void co2_sensor_read_thread::run()
{
    mutex.lock();
    qt_co2_sensor sens;
    abort =false;

    connect(&sens,SIGNAL(temperature_changed(double)),this,SIGNAL(temperature_changed(double)));
    connect(&sens,SIGNAL(carbon_dioxide_changed(double)),this,SIGNAL(carbon_dioxide_changed(double)));
    connect(&sens,SIGNAL(relative_humidity_changed(double)),this,SIGNAL(relative_humidity_changed(double)));
    mutex.unlock();

    while(!abort){
        sens.read();
    }

    mutex.lock();
    disconnect(&sens,SIGNAL(temperature_changed(double)),this,SIGNAL(temperature_changed(double)));
    disconnect(&sens,SIGNAL(carbon_dioxide_changed(double)),this,SIGNAL(carbon_dioxide_changed(double)));
    disconnect(&sens,SIGNAL(relative_humidity_changed(double)),this,SIGNAL(relative_humidity_changed(double)));
    mutex.unlock();
}

