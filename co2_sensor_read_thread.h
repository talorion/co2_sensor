#ifndef CO2_SENSOR_READ_THREAD_H
#define CO2_SENSOR_READ_THREAD_H

#include <QMutex>
#include <QThread>
#include <QWaitCondition>

class co2_sensor_read_thread : public QThread
{
    Q_OBJECT
public:
    explicit co2_sensor_read_thread(QObject *par = 0);
    ~co2_sensor_read_thread();
    Q_DISABLE_COPY(co2_sensor_read_thread)

signals:
    void temperature_changed(double);
    void carbon_dioxide_changed(double);
    void relative_humidity_changed(double);

public slots:

    // QThread interface
protected:
    void run();

private:
    QMutex mutex;
    bool abort;
    QWaitCondition condition;
};

#endif // CO2_SENSOR_READ_THREAD_H
