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
    update();

    chart->createDefaultAxes();
    chart->setTitle("Simple line chart example");
}

//dodanie wszystkich serii danych do wykresu
void Chart::addSeries(Series s)
{
    chart->addSeries(s.getSeries());
}

void Chart::update()
{
    //TODO: aktualizacja osi wykresu (dopasowanie wyswietlanego zakresu do danych)
}
