#include "sensor_output.h"

#include <QDebug>

sensor_output::sensor_output(QObject *par) : QObject(par)
{

}

sensor_output::~sensor_output()
{

}

void sensor_output::print_temperature(double temp)     {qDebug()<<"temperature="<<temp<<"Celsius";}

void sensor_output::print_carbon_dioxide(double co2)   {qDebug()<<"carbon_dioxide="<<co2<<"ppm";}

void sensor_output::print_relative_humidity(double rh) {qDebug()<<"relative_humidity="<<rh<<"%";}

