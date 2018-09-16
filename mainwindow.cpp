#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    chart->createChart();

    //wczytanie komponentu listy umozliwiajacego zmiane wartosci parametrow wykresu
    uiList.setupUi(list);

    //rozny uklad elementow ui w zaleznosci od rodzaju systemu
#ifdef __ANDROID__
    //TODO: dodac odpowiedni uklad dla systemu ANDROID
#else
    //elementy ui ulozone poziomo obok siebie
    horizontalLayout->addWidget(list);
    horizontalLayout->addWidget(chart->chartView);

    //proporcja kolumn 2/7 do 5/7 rozmiaru okna
    horizontalLayout->setStretch(0,2);
    horizontalLayout->setStretch(1,5);

    //ustawienie glownego widgetu okna aplikacji
    central->setLayout(horizontalLayout);
    setCentralWidget(central);

    //minimalny i domyslny rozmiar okna aplikacji
    setMinimumSize(500, 500);
    resize(1200, 800);

    connectSliders();
#endif

    //pobranie wartosci zmiennych do obliczen sil z wartosci ustawionych sliderami
    calculations.setDataValues(
                uiList.horizontalSlider_gasPressure->value(),
                uiList.horizontalSlider_massPiston->value(),
                uiList.horizontalSlider_massCrankPin->value(),
                uiList.horizontalSlider_massConnectingRod->value(),
                uiList.horizontalSlider_d->value(),
                uiList.horizontalSlider_r->value(),
                uiList.horizontalSlider_l->value(),
                uiList.horizontalSlider_n->value()
                );

    //obliczenia sily cisnienia gazow F_g
    calculations.calculate_gasPressureForce();

    //obliczenia sily bezwladnosci F_b
    calculations.calculate_inertialForce();

    //obliczenia kata pomiedzy korbowodem a osia przechodzaca przez srodek sworznia tlokowego i srodek czopa korbowego
    calculations.calculate_h();

    //obliczenia kata pomiedzy korbowodem a osia przechodzaca przez srodek sworznia tlokowego i srodek czopa korbowego
    calculations.calculate_beta();

    //obliczenia odleglosci (promienia), na ktorym dziala moment od sily P_k z pktu O wzgledem pktu B
    calculations.calculate_a();

    //obliczenia sily wypadkowej dzialajacej na tlok P_t
    calculations.calculate_pistonForce();

    //obliczenia skladowej prostopadlej do osi cylindra sily dzialajacej na tlok N
    calculations.calculate_pistonForce_N();

    //obliczenia skladowej wzdluznej do osi korbowodu sily dzialajacej na tlok P_k
    calculations.calculate_pistonForce_Pk();

    //obliczenia skladowej stycznej do okregu o promieniu r skladowej wzdluznej sily dzialajacej na tlok T
    calculations.calculate_pistonForce_Pk_tangencial();

    //obliczenia skladowej doosiowej (promieniowej) skladowej wzdluznej sily dzialajacej na tlok R
    calculations.calculate_pistonForce_Pk_centripetal();

    //obliczenia chwilowego momentu obrotowego na wale korbowym M
    calculations.calculate_torqueCrankshaft();

    //obliczenia momentu od sily P_k na ramieniu a
    calculations.calculate_torque_Pk();

    //obliczenia momentu reakcyjnego dzialajacego na kadlub silnika M_r
    calculations.calculate_torqueReactive();

    calculations.updateChart();

    double a = calculations.get_gasPressureForce();
    cout << endl << "a=" << a << endl;
}

MainWindow::~MainWindow()
{
    delete chart;
    delete list;
    delete horizontalLayout;
    delete central;
}

void MainWindow::connectSliders()
{
    //polaczenia miedzy zmiana slidera, a zmiana wartosci wyswietlanej w labelu
    connect(uiList.horizontalSlider_gasPressure, SIGNAL(valueChanged(int)), uiList.label_gasPressure, SLOT(setNum(int)));
    connect(uiList.horizontalSlider_d, SIGNAL(valueChanged(int)), uiList.label_d, SLOT(setNum(int)));
    connect(uiList.horizontalSlider_r, SIGNAL(valueChanged(int)), uiList.label_r, SLOT(setNum(int)));
    connect(uiList.horizontalSlider_l, SIGNAL(valueChanged(int)), uiList.label_l, SLOT(setNum(int)));
    connect(uiList.horizontalSlider_n, SIGNAL(valueChanged(int)), uiList.label_n, SLOT(setNum(int)));
    connect(uiList.horizontalSlider_massPiston, SIGNAL(valueChanged(int)), uiList.label_massPiston, SLOT(setNum(int)));
    connect(uiList.horizontalSlider_massCrankPin, SIGNAL(valueChanged(int)), uiList.label_massCrankPin, SLOT(setNum(int)));
    connect(uiList.horizontalSlider_massConnectingRod, SIGNAL(valueChanged(int)), uiList.label_massConnectingRod, SLOT(setNum(int)));
}
