#include "chart.h"

Chart::Chart()
{
    //wygladza linie wykresu - poprawia jakosc wyswietlania wykresu
    chartView->setRenderHint(QPainter::Antialiasing);
}

Chart::~Chart()
{
    delete inertialForce;
    delete gasPressureForce;
    delete pistonForce;
    delete pistonForce_Pk;
    delete pistonForce_N;
    delete pistonForce_Pk_tangencial;
    delete pistonForce_Pk_centripetal;

    delete torque_Pk;
    delete torqueCrankshaft;
    delete torqueReactive;

    delete chart;
    delete chartView;
}

void Chart::createChart()
{
    createData();

    addSeries();

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
    //sily
    gasPressureForce = new Series(seriesX, seriesY[0]);
    inertialForce = new Series(seriesX, seriesY[1]);
    pistonForce = new Series(seriesX, seriesY[2]);
    pistonForce_N = new Series(seriesX, seriesY[3]);
    pistonForce_Pk = new Series(seriesX, seriesY[4]);
    pistonForce_Pk_tangencial = new Series(seriesX, seriesY[5]);
    pistonForce_Pk_centripetal = new Series(seriesX, seriesY[6]);

    //momenty
//    torque_Pk = new Series(seriesX, seriesY[]);
//    torqueCrankshaft = new Series(seriesX, seriesY[]);
//    torqueReactive = new Series(seriesX, seriesY[]);
}

//dodanie serii danych do wykresu
void Chart::addSeries()
{
    //sily
    chart->addSeries(gasPressureForce->getSeries());
    chart->addSeries(inertialForce->getSeries());
    chart->addSeries(pistonForce->getSeries());
    chart->addSeries(pistonForce_N->getSeries());
    chart->addSeries(pistonForce_Pk->getSeries());
    chart->addSeries(pistonForce_Pk_tangencial->getSeries());
    chart->addSeries(pistonForce_Pk_centripetal->getSeries());
}
