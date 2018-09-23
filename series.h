#ifndef SERIES_H
#define SERIES_H

#include <QtCharts>

#include <iostream>
using namespace std;


class Series
{
public:
    Series(QVector<double> x, QVector<double> y);
    ~Series();

    QLineSeries *getSeries();

    void update(QVector<double> x, QVector<double> y);

    int getLength();

private:
    QPointF s;

    QLineSeries *series = new QLineSeries;
};

#endif // SERIES_H
