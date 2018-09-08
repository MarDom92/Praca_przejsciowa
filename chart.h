#ifndef CHART_H
#define CHART_H

#include <QMainWindow>
#include <QtCharts>


class Chart : public QMainWindow
{
    Q_OBJECT

public:
    Chart(QWidget *parent = nullptr);
    ~Chart();

    void createChart();

private:
    QLineSeries *series = new QLineSeries();

    QChart *chart = new QChart();

public:
    QChartView *chartView = new QChartView(chart);
};

#endif // CHART_H
