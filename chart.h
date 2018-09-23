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

    void addSeries(Series s);

public slots:
    void update();

private:
    QChart *chart = new QChart();

    //serie danych sil
    Series *gasPressureForce;
    Series *inertialForce;
    Series *pistonForce;
    Series *pistonForce_N;
    Series *pistonForce_Pk;
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
