#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    chart->createChart();
    setCentralWidget(chart->chartView);
    resize(800, 600);
}

MainWindow::~MainWindow()
{
    delete chart;
}
