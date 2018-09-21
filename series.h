#ifndef SERIES_H
#define SERIES_H

#include <QtCharts>


class Series
{
public:
    Series(QVector<double> x, QVector<double> y);
    ~Series();

    QLineSeries *getSeries();

private:
    QPointF s;

    QLineSeries *series = new QLineSeries;
};

#endif // SERIES_H
