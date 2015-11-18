#include "qt_co2_sensor.h"

#include <QDebug>

#include "libusb.h"
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <libusb.h>

qt_co2_sensor::qt_co2_sensor(QObject *par) :
    QObject(par),
    endpoint_in(0),
    endpoint_out(0),
    devh(NULL),
    temperature(0),
    carbon_dioxide(0),
    relative_humidity(0)
{
    init_usb();
}

qt_co2_sensor::~qt_co2_sensor()
{
    dispose_usb();
}

int qt_co2_sensor::init_usb()
{
    int r = 1;
    //struct libusb_device_handle *devh = NULL;
    struct libusb_device * dev = NULL;
    struct libusb_config_descriptor *conf_desc;
    const struct libusb_endpoint_descriptor *endpoint =NULL;


    //=============
    r = libusb_init(NULL);
    if (r < 0) {
        qDebug("Failed to initialise libusb\n");
        exit(1);
    }
    //=============
    //=============
    devh = libusb_open_device_with_vid_pid(NULL, VENDOR_ID, PRODUCT_ID);
    r = (devh ? 0 : -EIO);
    if (r < 0) {
        qDebug("Could not find/open LVR Generic HID device\n");
    }
    //qDebug("Successfully find the LVR Generic HID device\n");

    dev = libusb_get_device(devh);
    r = (dev ? 0 : -EIO);
    if (r < 0) {
        qDebug("Could not get device\n");
    }
    //qDebug("Successfully got device\n");
    //=============
    //=============
    libusb_device_handle *  	dev_handle  = devh;
    uint8_t  	bmRequestType               = 0x21;
    uint8_t  	bRequest                    = 0x09;
    uint16_t  	wValue                      = 0x0300;
    uint16_t  	wIndex                      = 0x00;
    unsigned char   	data[8]             = {0xc4, 0xc6, 0xc0, 0x92, 0x40, 0x23, 0xdc, 0x96};
    uint16_t  	wLength                     = sizeof(data);
    unsigned int  	timeout                 = 5000;

    r= libusb_control_transfer 	(dev_handle, bmRequestType, bRequest, wValue, wIndex, data, wLength, timeout);
    if (r < 0) {
        qDebug("Interrupt write error %d %s\n", r, libusb_error_name(r));
        return r;
    }
    //qDebug("Successfully libusb_control_transfer\n");
    //=============
    //=============
    /* We need to claim the first interface */
    libusb_set_auto_detach_kernel_driver(dev_handle, 1);
    r = libusb_claim_interface(dev_handle, 0);
    if (r != LIBUSB_SUCCESS) {
        qDebug("libusb_claim_interface failed: %s\n", libusb_error_name(r));
    }
    //qDebug("Successfully claimed first interface\n");

    r = libusb_get_config_descriptor(dev, 0, &conf_desc);
    if (r != LIBUSB_SUCCESS) {
        qDebug("libusb_get_config_descriptor failed: %s\n", libusb_error_name(r));
    }
    //qDebug("Successfully libusb_get_config_descriptor\n");


    uint8_t nb_ifaces = conf_desc->bNumInterfaces;
    for (int i=0; i<nb_ifaces; i++) {
        for (int j=0; j<conf_desc->interface[i].num_altsetting; j++) {
            for (int k=0; k<conf_desc->interface[i].altsetting[j].bNumEndpoints; k++) {
                endpoint = &conf_desc->interface[i].altsetting[j].endpoint[k];
                if ((endpoint->bmAttributes & LIBUSB_TRANSFER_TYPE_MASK) & (LIBUSB_TRANSFER_TYPE_BULK | LIBUSB_TRANSFER_TYPE_INTERRUPT)) {
                    if (endpoint->bEndpointAddress & LIBUSB_ENDPOINT_IN) {
                        if (!endpoint_in)
                            endpoint_in = endpoint->bEndpointAddress;
                    } else {
                        if (!endpoint_out)
                            endpoint_out = endpoint->bEndpointAddress;
                    }
                }
            }
        }
    }

    return 0;
}

void qt_co2_sensor::read()
{
    if(!devh)
        return;

    struct libusb_device_handle *dev_handle = devh;
    unsigned char ep                        = endpoint_in;
    unsigned char read_data[8];
    int read_length                         =sizeof(read_data);
    int transferred                         =0;
    unsigned int timeout                    = 5000;
    unsigned char   	data[8]             = {0xc4, 0xc6, 0xc0, 0x92, 0x40, 0x23, 0xdc, 0x96};

    int r = libusb_bulk_transfer(dev_handle, ep,read_data,read_length,&transferred,timeout);
    if (r == 0 && transferred == sizeof(read_data)) {
        decrypt(data,read_data);
    } else {
        qDebug("libusb_bulk_transfer failed: %s\n", libusb_error_name(r));
    }

}

void qt_co2_sensor::decrypt(unsigned char *buf, unsigned char *read_data)
{
    unsigned char   	cstate [8]  = {0x48, 0x74, 0x65, 0x6D, 0x70, 0x39, 0x39, 0x65};
    unsigned char       shuffle[8]  = {2, 4, 0, 7, 1, 6, 5, 3};

    size_t lengtht = 8;

    unsigned char   	phase1 [8];
    for(size_t i = 0; i < lengtht; i++) {
        phase1[shuffle[i]] = read_data[i];
    }

    unsigned char   	phase2 [8];
    for(size_t i = 0; i < lengtht; i++) {
        phase2[i] = phase1[i] ^ buf[i];
    }

    unsigned char   	phase3 [8];
    for(size_t i = 0; i < lengtht; i++) {
        phase3[i] =  ((phase2[i] >> 3) | (phase2[ (i-1+8)%8 ] << 5) ) & 0xff;
    }

    unsigned char   	ctmp  [8];
    for(size_t i = 0; i < lengtht; i++) {
        ctmp[i] = ( (cstate[i] >> 4) | (cstate[i]<<4) ) & 0xff;
    }

    unsigned char   	out  [8];
    for(size_t i = 0; i < lengtht ; i++) {
        out[i] = ((0x100 + phase3[i] - ctmp[i]) & 0xff);
        //qDebug()<<out[i];
    }

    int sum=out[0]+out[1]+out[2];
    if (out[4] != 0x0d || (((sum) & 0xff) != out[3])){
        qDebug()<<"Checksum error";
    }
    unsigned char  op  = out[0];
    uint16_t       val = out[1] << 8 | out[2];

    if(op==80){
        //qDebug()<<"co2="<<val;
        set_carbon_dioxide(val);
    }

    if(op==66){
        //qDebug()<<"temp="<<val/16.0-273.15;
        set_temperature(val);
    }

    if(op==68){
        //qDebug()<<"RH="<<val/100.0;
        set_relative_humidity(val);
    }
}

void qt_co2_sensor::dispose_usb()
{

    struct libusb_device_handle *dev_handle = devh;
    libusb_release_interface(dev_handle, 0);
    libusb_close(dev_handle);
    libusb_exit(NULL);
}

void qt_co2_sensor::set_temperature(quint16 val)
{
    double newval = val/16.0-273.15;;
    if(temperature != newval){
        temperature =newval;
        //emit temperature_changed(temperature);
    }
    emit temperature_changed(temperature);
}

void qt_co2_sensor::set_carbon_dioxide(quint16 val)
{
    double newval = val;
    if(carbon_dioxide != newval){
        carbon_dioxide =newval;
        //emit carbon_dioxide_changed(carbon_dioxide);
    }
    emit carbon_dioxide_changed(carbon_dioxide);
}

void qt_co2_sensor::set_relative_humidity(quint16 val)
{
    double newval = val/100.0;
    if(relative_humidity != newval){
        relative_humidity =newval;
        //emit relative_humidity_changed(relative_humidity);
    }
    emit relative_humidity_changed(relative_humidity);
}
double qt_co2_sensor::get_relative_humidity() const
{
    return relative_humidity;
}

double qt_co2_sensor::get_carbon_dioxide() const
{
    return carbon_dioxide;
}

double qt_co2_sensor::get_temperature() const
{
    return temperature;
}


