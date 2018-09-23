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
//    update();

    chart->createDefaultAxes();
    chart->setTitle("Sily w układzie tłokowo-korbowym");
}

//dodanie wszystkich serii danych do wykresu
void Chart::addSeries(Series s)
{
    chart->addSeries(s.getSeries());
}

void Chart::removeSeries(Series s)
{
    chart->removeSeries(s.getSeries());
}

void Chart::removeAllSeries()
{
    chart->removeAllSeries();
}

void Chart::refreshAxes()
{
    chart->createDefaultAxes();
}

void Chart::changeTitle(QString str)
{
    chart->setTitle(str);
}

void Chart::update()
{
    //TODO: aktualizacja osi wykresu (dopasowanie wyswietlanego zakresu do danych)
}
