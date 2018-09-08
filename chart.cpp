#include "chart.h"

Chart::Chart(QWidget *parent)
    : QMainWindow(parent)
{
    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);

    //wygladza linie wykresu - poprawia jakosc wyswietlania wykresu
    chartView->setRenderHint(QPainter::Antialiasing);
}

Chart::~Chart()
{
    delete series;
    delete chart;
    delete  chartView;
}

void Chart::createChart()
{
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Simple line chart example");
}
