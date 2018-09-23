#include "series.h"

Series::Series(QVector<double> x, QVector<double> y)
{
    update(x, y);
}

Series::~Series()
{
//    delete series; //TODO: odkomentowanie powoduje usuniecie serii przed dodaniem do wykresu
}

QLineSeries *Series::getSeries()
{
    return series;
}

void Series::update(QVector<double> x, QVector<double> y)
{
    series->clear();

    for(int i=0; i < x.length(); i++)
    {
        s.setX(x[i]);
        s.setY(y[i]);

        *series << QPointF(s.x(), s.y());
    }
}
