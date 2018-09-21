#include "series.h"

Series::Series(QVector<double> x, QVector<double> y)
{
    for(int i=0; i < x.length(); i++)
    {
        s.setX(x[i]);
        s.setY(y[i]);

        *series << QPointF(s.x(), s.y());
    }
}

Series::~Series()
{
    delete series;
}

QLineSeries *Series::getSeries()
{
    return series;
}
