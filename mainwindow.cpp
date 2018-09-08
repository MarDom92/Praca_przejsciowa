#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    chart->createChart();

    //wczytanie komponentu listy umozliwiajacego zmiane wartosci parametrow wykresu
    Ui::Form uiList;
    uiList.setupUi(list);

    //rozny uklad elementow ui w zaleznosci od rodzaju systemu
#ifdef __ANDROID__
    //TODO: dodac odpowiedni uklad dla systemu ANDROID
#else
    //elementy ui ulozone poziomo obok siebie
    horizontalLayout->addWidget(list);
    horizontalLayout->addWidget(chart->chartView);

    //ustawienie glownego widgetu okna aplikacji
    central->setLayout(horizontalLayout);
    setCentralWidget(central);

    //minimalny i domyslny rozmiar okna aplikacji
    setMinimumSize(500, 500);
    resize(1200, 800);
#endif
}

MainWindow::~MainWindow()
{
    delete chart;
    delete list;
    delete horizontalLayout;
    delete central;
}
