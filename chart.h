#ifndef CHART_H
#define CHART_H

#include <QMainWindow>
#include <QtCharts>


class Chart : public QWidget
{
    Q_OBJECT

public:
    Chart();
    ~Chart();

    void createChart();

private:
//    QLineSeries *series = new QLineSeries();

    QChart *chart = new QChart();

    //przykladowy obiekt klasy Series
//    Series *s = new Series();

public:
    QChartView *chartView = new QChartView(chart);
};

#endif // CHART_H
