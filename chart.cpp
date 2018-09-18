#include "chart.h"

Chart::Chart()
{
    //wygladza linie wykresu - poprawia jakosc wyswietlania wykresu
    chartView->setRenderHint(QPainter::Antialiasing);
}

Chart::~Chart()
{
    delete chart;
    delete series;
    delete chartView;
}

void Chart::createChart()
{
    createData();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Simple line chart example");
}

//stworzenie dziedziny funkcji
void Chart::addSeriesX(QVector<double> x[])
{
    for(int i=0; i < x->length(); i++)
    {
        seriesX.push_back(x->at(i));
    }
}

//stworzenie wektora z funkcjami y(x)
void Chart::addSeriesY(QVector<double> y[])
{
    //wektor tymczasowy zawierajacy dane jednej funkcji y(x)
    QVector<double> v;

    for(int i=0; i < y->length(); i++)
    {
        v.push_back(y->at(i));
    }

    //dodanie kolejnej funkcji y(x) do wektora z funkcjami y(x)
    seriesY.push_back(v);
}

//stworzenie serii danych dla wykresu
void Chart::createData()
{
    for(int i=0; i < seriesX.length(); i++)
    {
        QPointF s;
        s.setX(seriesX.at(i));
        s.setY(seriesX.at(i));
        series->append(s.x(), s.y());
    }
}
