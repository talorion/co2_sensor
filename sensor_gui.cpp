#include "sensor_gui.h"

#include "qcustomplot.hpp"

sensor_gui::sensor_gui(QWidget *par):
    QMainWindow(par),
    temp_plot(NULL),
    co2_plot(NULL),
    rh_plot(NULL),
    temp_graph(NULL),
    co2_graph(NULL),
    rh_graph(NULL)
{
    temp_plot = new QCustomPlot();
    setupPlot(temp_plot);
    temp_plot->yAxis->setRangeLower(15);
    temp_plot->yAxis->setRangeUpper(35);
    temp_plot->yAxis->setLabel(tr("temperature [°C]"));
    temp_plot->legend->setVisible(true);

    temp_graph = temp_plot->addGraph();
    temp_graph->setAdaptiveSampling(true);
    temp_graph->setPen(QPen(QColor(255,0,0)));
    temp_graph->setName("temperature [°C]");
    //==========

    temp_plot->yAxis2->setVisible(true);
    temp_plot->yAxis2->setRangeLower(400);
    temp_plot->yAxis2->setRangeUpper(1200);
    temp_plot->yAxis2->setLabel(tr("CO2 [ppm]"));

    co2_graph = temp_plot->addGraph(temp_plot->xAxis, temp_plot->yAxis2);
    co2_graph->setPen(QPen(QColor(0,255,0)));
    co2_graph->setName("CO2 [ppm]");


    //    co2_plot = new QCustomPlot();
    //    setupPlot(co2_plot);
    //    co2_plot->yAxis->setRangeLower(400);
    //    co2_plot->yAxis->setRangeUpper(1200);
    //    co2_plot->legend->setVisible(true);

    //    co2_graph = co2_plot->addGraph();
    //    co2_graph->setPen(QPen(QColor(0,255,0)));
    //    co2_graph->setName("CO2 [ppm]");
    //==========
    //    rh_plot = new QCustomPlot();
    //    setupPlot(rh_plot);
    //    rh_plot->yAxis->setRangeLower(0);
    //    rh_plot->yAxis->setRangeUpper(100);
    //    rh_plot->legend->setVisible(true);

    //    rh_graph = rh_plot->addGraph();
    //    rh_graph->setAdaptiveSampling(true);
    //    rh_graph->setPen(QPen(QColor(0,0,255)));
    //    rh_graph->setName("RH [%]");
    //==========

    QWidget* plot_widget = new QWidget();
    QVBoxLayout *plot_widget_layout = new QVBoxLayout();
    plot_widget_layout->addWidget(temp_plot);
    //plot_widget_layout->addWidget(co2_plot);
    //layout->addWidget(rh_plot);
    plot_widget->setLayout(plot_widget_layout);

    setCentralWidget(plot_widget);

}

sensor_gui::~sensor_gui()
{

}

void sensor_gui::setupPlot(QCustomPlot *plt)
{
    QDateTime t;
    double time = t.currentMSecsSinceEpoch()/1000.0;

    plt->yAxis->setAutoTickCount(2);
    plt->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    plt->xAxis->setAutoTickCount(2);
    plt->xAxis->setDateTimeFormat("hh:mm:ss");
    plt->xAxis->setRangeLower(QDateTime::currentMSecsSinceEpoch()/1000.0);
    plt->xAxis->setLabel(tr("Time"));
    plt->xAxis->setRangeLower(time - 60);


}

void sensor_gui::print_temperature(double temp)
{
    //Q_UNUSED(temp);
    //temperature [°C]
    updatePlot(temp_plot, temp_graph, temp,"temperature", "°C");
}

void sensor_gui::print_carbon_dioxide(double co2)
{
    //Q_UNUSED(co2);
    //CO2 [ppm]
    //updatePlot(co2_plot, co2_graph, co2, "CO2", "ppm");
    updatePlot(temp_plot, co2_graph, co2, "CO2", "ppm");
}

void sensor_gui::print_relative_humidity(double rh)
{
    Q_UNUSED(rh);
    //RH [%]
    //updatePlot(rh_plot, rh_graph, rh, "humidity", "%");
}

void sensor_gui::updatePlot(QCustomPlot *plt, QCPGraph* grap, double value, QString name, QString unit)
{
    //double graph_persistance_time = 24*60*60;

    //QDateTime* t = new QDateTime();
    QDateTime t;
    double time = t.currentMSecsSinceEpoch()/1000.0;
    grap->setName(name+" "+QString::number(value)+unit);
    grap->addData(time, value);
    //plt->xAxis->setRangeUpper(time);
    plt->xAxis->setRangeUpper(time + 60);
    //plt->xAxis->setRangeLower(time - 60);
    //grap->removeDataBefore(time - graph_persistance_time);
    plt->replot();
}
