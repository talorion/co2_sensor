#ifndef SENSOR_GUI_H
#define SENSOR_GUI_H

#include <QMainWindow>

class QCPGraph;
class QCustomPlot;

class sensor_gui : public QMainWindow
{
    Q_OBJECT
public:
    explicit sensor_gui(QWidget *par = 0);
    ~sensor_gui();
    Q_DISABLE_COPY(sensor_gui)

private:
    void setupPlot(QCustomPlot* plt);
    void updatePlot(QCustomPlot *plt, QCPGraph *grap, double value, QString name=QString(), QString unit=QString());

public slots:
    void print_temperature(double temp);
    void print_carbon_dioxide(double co2);
    void print_relative_humidity(double rh);

private:
    QCustomPlot* temp_plot;
    QCustomPlot* co2_plot;
    QCustomPlot* rh_plot;

    QCPGraph* temp_graph;
    QCPGraph* co2_graph;
    QCPGraph* rh_graph;
};

#endif // SENSOR_GUI_H
