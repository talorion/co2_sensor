#ifndef SENSOR_OUTPUT_H
#define SENSOR_OUTPUT_H

#include <QObject>


class sensor_output : public QObject
{
    Q_OBJECT
public:
    explicit sensor_output(QObject *par = 0);
    ~sensor_output();
    Q_DISABLE_COPY(sensor_output)

public slots:
    void print_temperature(double temp);
    void print_carbon_dioxide(double co2);
    void print_relative_humidity(double rh);
};

#endif // SENSOR_OUTPUT_H
