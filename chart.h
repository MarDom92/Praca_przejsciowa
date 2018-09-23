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

    void removeSeries(Series s);

    void refreshAxes();

public slots:
    void update();

private:
    QChart *chart = new QChart();

public:
    QChartView *chartView = new QChartView(chart);
};

#endif // CHART_H
