#ifndef CHART_H
#define CHART_H

#include <QMainWindow>
#include <QtCharts>

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

private:
    QChart *chart = new QChart();

    QVector<double> seriesX;

    QVector<QVector<double>> seriesY;

public:
    QChartView *chartView = new QChartView(chart);
};

#endif // CHART_H
