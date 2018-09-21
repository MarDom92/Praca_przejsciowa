#ifndef CHART_H
#define CHART_H

#include <QMainWindow>
#include <QtCharts>

#include "series.h"

#include <iostream>
using namespace std;


class Chart : public QWidget
{
    Q_OBJECT

public:
    Chart();
    ~Chart();

    void createChart();

    void addSeriesX(QVector<double> x[]);

    void addSeriesY(QVector<double> y[]);

    void createData();

    void addSeries();

private:
    QChart *chart = new QChart();

    QVector<double> seriesX;

    QVector<QVector<double>> seriesY;

    //serie danych sil
    Series *inertialForce;
    Series *gasPressureForce;
    Series *pistonForce;
    Series *pistonForce_Pk;
    Series *pistonForce_N;
    Series *pistonForce_Pk_tangencial;
    Series *pistonForce_Pk_centripetal;

    //serie danych momentow sil
    Series *torque_Pk;
    Series *torqueCrankshaft;
    Series *torqueReactive;

public:
    QChartView *chartView = new QChartView(chart);
};

#endif // CHART_H
