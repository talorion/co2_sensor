#ifndef QT_CO2_SENSOR_H
#define QT_CO2_SENSOR_H

#include <QObject>
#include <QSharedPointer>

struct libusb_device_handle;

class qt_co2_sensor : public QObject
{
    Q_OBJECT
public:
    explicit qt_co2_sensor(QObject *parent = 0);
    ~qt_co2_sensor();

    void read();

//public slots:
//    void start_read();

    double get_temperature() const;

    double get_carbon_dioxide() const;

    double get_relative_humidity() const;

signals:
    void temperature_changed(double);
    void carbon_dioxide_changed(double);
    void relative_humidity_changed(double);

private:

    int init_usb();

    void decrypt(unsigned char* buf, unsigned char* read_data);

    void dispose_usb();

//private slots:
    //void read();

    void set_temperature(quint16 val);
    void set_carbon_dioxide(quint16 val);
    void set_relative_humidity(quint16 val);

private:
    static const quint16 VENDOR_ID     = 0x04d9;
    static const quint16 PRODUCT_ID    = 0xa052;

    quint8 endpoint_in;
    quint8 endpoint_out;

    libusb_device_handle* devh;

    double temperature;
    double carbon_dioxide;
    double relative_humidity;
};

#endif // QT_CO2_SENSOR_H
