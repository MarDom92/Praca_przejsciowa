#include "chart.h"

Chart::Chart()
{
    //wygladza linie wykresu - poprawia jakosc wyswietlania wykresu
    chartView->setRenderHint(QPainter::Antialiasing);
}

Chart::~Chart()
{
    delete chart;
    delete chartView;
}

void Chart::createChart()
{
//    chart->addSeries(series);
//    chart->addSeries(s);

    chart->createDefaultAxes();
    chart->setTitle("Simple line chart example");
}

//stworzenie dziedziny funkcji
void Chart::addSeriesX(double x[])
{
    for(int i=0; i<=360; i++)
    {
        seriesX.push_back(x[i]);
    }
}

//stworzenie wektora z funkcjami y(x)
void Chart::addSeriesY(double y[])
{
    //wektor tymczasowy zawierajacy dane jednej funkcji y(x)
    QVector<double> v;

    for(int i=0; i<=360; i++)
    {
        v.push_back(y[i]);
    }

    //dodanie kolejnej funkcji y(x) do wektora z funkcjami y(x)
    seriesY.push_back(v);
}
