#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("SIMWUTK");

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

    connectCalculations();

    connectCheckboxes();

    connectTabWidgets();

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

    calculations.calculate_all();

    createForcesSeries();
    createTorquesSeries();

    addForcesSeries();
    addTorquesSeries();

    chart->createChart();
}

MainWindow::~MainWindow()
{
    delete gasPressureForce;
    delete inertialForce;
    delete pistonForce;
    delete pistonForce_N;
    delete pistonForce_Pk;
    delete pistonForce_Pk_tangencial;
    delete pistonForce_Pk_centripetal;

    delete torque_Pk;
    delete torqueCrankshaft;
    delete torqueReactive;

    delete chart;

    delete list;
    delete horizontalLayout;
    delete central;
}

void MainWindow::createForcesSeries()
{
    //sily
    gasPressureForce = new Series(*calculations.get_alfa(), *calculations.get_gasPressureForce());
    inertialForce = new Series(*calculations.get_alfa(), *calculations.get_inertialForce());
    pistonForce = new Series(*calculations.get_alfa(), *calculations.get_pistonForce());
    pistonForce_N = new Series(*calculations.get_alfa(), *calculations.get_pistonForce_N());
    pistonForce_Pk = new Series(*calculations.get_alfa(), *calculations.get_pistonForce_Pk());
    pistonForce_Pk_tangencial = new Series(*calculations.get_alfa(), *calculations.get_pistonForce_Pk_tangencial());
    pistonForce_Pk_centripetal = new Series(*calculations.get_alfa(), *calculations.get_pistonForce_Pk_centripetal());
}

void MainWindow::updateForcesSeries()
{
    gasPressureForce->update(*calculations.get_alfa(), *calculations.get_gasPressureForce());
    inertialForce->update(*calculations.get_alfa(), *calculations.get_inertialForce());
    pistonForce->update(*calculations.get_alfa(), *calculations.get_pistonForce());
    pistonForce_N->update(*calculations.get_alfa(), *calculations.get_pistonForce_N());
    pistonForce_Pk->update(*calculations.get_alfa(), *calculations.get_pistonForce_Pk());
    pistonForce_Pk_tangencial->update(*calculations.get_alfa(), *calculations.get_pistonForce_Pk_tangencial());
    pistonForce_Pk_centripetal->update(*calculations.get_alfa(), *calculations.get_pistonForce_Pk_centripetal());
}

void MainWindow::createTorquesSeries()
{
    //momenty
    torque_Pk =  new Series(*calculations.get_alfa(), *calculations.get_torque_Pk());
    torqueCrankshaft =  new Series(*calculations.get_alfa(), *calculations.get_torqueCrankshaft());
    torqueReactive =  new Series(*calculations.get_alfa(), *calculations.get_torqueReactive());
}

void MainWindow::updateTorquesSeries()
{
    torque_Pk->update(*calculations.get_alfa(), *calculations.get_torque_Pk());
    torqueCrankshaft->update(*calculations.get_alfa(), *calculations.get_torqueCrankshaft());
    torqueReactive->update(*calculations.get_alfa(), *calculations.get_torqueReactive());
}

void MainWindow::addForcesSeries()
{
    if(uiList.checkBox_gasPressureForce->isChecked())
        chart->addSeries(*gasPressureForce);

    if(uiList.checkBox_inertialForce->isChecked())
        chart->addSeries(*inertialForce);

    if(uiList.checkBox_pistonForce->isChecked())
        chart->addSeries(*pistonForce);

    if(uiList.checkBox_pistonForce_N->isChecked())
        chart->addSeries(*pistonForce_N);

    if(uiList.checkBox_pistonForce_Pk->isChecked())
        chart->addSeries(*pistonForce_Pk);

    if(uiList.checkBox_pistonForce_Pk_tangencial->isChecked())
        chart->addSeries(*pistonForce_Pk_tangencial);

    if(uiList.checkBox_pistonForce_Pk_centripetal->isChecked())
        chart->addSeries(*pistonForce_Pk_centripetal);
}

void MainWindow::addTorquesSeries()
{
    if(uiList.checkBox_torqueCrankshaft->isChecked())
        chart->addSeries(*torqueCrankshaft);

    if(uiList.checkBox_torque_Pk->isChecked())
        chart->addSeries(*torque_Pk);

    if(uiList.checkBox_torqueReactive->isChecked())
        chart->addSeries(*torqueReactive);
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

    //polaczenia miedzy zmiana slidera, a zmiana wartosci w obliczeniach
    connect(uiList.horizontalSlider_gasPressure, &QSlider::valueChanged, &calculations, &Calculations::set_gasPressure);
    connect(uiList.horizontalSlider_d, &QSlider::valueChanged, &calculations, &Calculations::set_d);
    connect(uiList.horizontalSlider_r, &QSlider::valueChanged, &calculations, &Calculations::set_r);
    connect(uiList.horizontalSlider_l, &QSlider::valueChanged, &calculations, &Calculations::set_l);
    connect(uiList.horizontalSlider_n, &QSlider::valueChanged, &calculations, &Calculations::set_n);
    connect(uiList.horizontalSlider_massPiston, &QSlider::valueChanged, &calculations, &Calculations::set_massPiston);
    connect(uiList.horizontalSlider_massCrankPin, &QSlider::valueChanged, &calculations, &Calculations::set_massCrankPin);
    connect(uiList.horizontalSlider_massConnectingRod,&QSlider::valueChanged, &calculations, &Calculations::set_massConnectingRod);
}

void MainWindow::connectCalculations()
{
    //polaczenia miedzy emitowanym sygnalem o zmianie wartosci z funkcjami obliczen i wyswietlania na wykresie
    connect(&calculations, &Calculations::changedValues, &calculations, &Calculations::calculate_all);
    connect(&calculations, &Calculations::changedValues, this, &MainWindow::updateForcesSeries);
    connect(&calculations, &Calculations::changedValues, this, &MainWindow::updateTorquesSeries);
    connect(&calculations, &Calculations::changedValues, chart, &Chart::update);
}

void MainWindow::connectCheckboxes()
{
    //laczy checkboxy ze slotami, ktore beda odpowiadac za wyswietlanie lub ukrywanie serii na wykresie

    //sily
    connect(uiList.checkBox_gasPressureForce, &QCheckBox::clicked, this, &MainWindow::on_checkBox_gasPressureForce_clicked);
    connect(uiList.checkBox_inertialForce, &QCheckBox::clicked, this, &MainWindow::on_checkBox_inertialForce_clicked);
    connect(uiList.checkBox_pistonForce, &QCheckBox::clicked, this, &MainWindow::on_checkBox_pistonForce_clicked);
    connect(uiList.checkBox_pistonForce_N, &QCheckBox::clicked, this, &MainWindow::on_checkBox_pistonForce_N_clicked);
    connect(uiList.checkBox_pistonForce_Pk, &QCheckBox::clicked, this, &MainWindow::on_checkBox_pistonForce_Pk_clicked);
    connect(uiList.checkBox_pistonForce_Pk_tangencial, &QCheckBox::clicked, this, &MainWindow::on_checkBox_pistonForce_Pk_tangencial_clicked);
    connect(uiList.checkBox_pistonForce_Pk_centripetal, &QCheckBox::clicked, this, &MainWindow::on_checkBox_pistonForce_Pk_centripetal_clicked);

    //momenty
    connect(uiList.checkBox_torqueCrankshaft, &QCheckBox::clicked, this, &MainWindow::on_checkBox_torqueCrankshaft_clicked);
    connect(uiList.checkBox_torque_Pk, &QCheckBox::clicked, this, &MainWindow::on_checkBox_torque_Pk_clicked);
    connect(uiList.checkBox_torqueReactive, &QCheckBox::clicked, this, &MainWindow::on_checkBox_torqueReactive_clicked);
}

void MainWindow::connectTabWidgets()
{
    //laczy zmiane zakladek z checkboxami - wybor czy wyswietlac checkboxy sil czy momentow
    connect(uiList.tabWidget_parameters, &QTabWidget::currentChanged, this, &MainWindow::on_tabWidget_parameters_currentChanged);
}

void MainWindow::on_checkBox_gasPressureForce_clicked()
{
    if(uiList.checkBox_gasPressureForce->isChecked())
    {
        chart->addSeries(*gasPressureForce);
    }
    else
    {
        chart->removeSeries(*gasPressureForce);
    }

    chart->refreshAxes();
}

void MainWindow::on_checkBox_inertialForce_clicked()
{
    if(uiList.checkBox_inertialForce->isChecked())
    {
        chart->addSeries(*inertialForce);
    }
    else
    {
        chart->removeSeries(*inertialForce);
    }

    chart->refreshAxes();
}

void MainWindow::on_checkBox_pistonForce_clicked()
{
    if(uiList.checkBox_pistonForce->isChecked())
    {
        chart->addSeries(*pistonForce);
    }
    else
    {
        chart->removeSeries(*pistonForce);
    }

    chart->refreshAxes();
}

void MainWindow::on_checkBox_pistonForce_N_clicked()
{
    if(uiList.checkBox_pistonForce_N->isChecked())
    {
        chart->addSeries(*pistonForce_N);
    }
    else
    {
        chart->removeSeries(*pistonForce_N);
    }

    chart->refreshAxes();
}

void MainWindow::on_checkBox_pistonForce_Pk_clicked()
{
    if(uiList.checkBox_pistonForce_Pk->isChecked())
    {
        chart->addSeries(*pistonForce_Pk);
    }
    else
    {
        chart->removeSeries(*pistonForce_Pk);
    }

    chart->refreshAxes();
}

void MainWindow::on_checkBox_pistonForce_Pk_tangencial_clicked()
{
    if(uiList.checkBox_pistonForce_Pk_tangencial->isChecked())
    {
        chart->addSeries(*pistonForce_Pk_tangencial);
    }
    else
    {
        chart->removeSeries(*pistonForce_Pk_tangencial);
    }

    chart->refreshAxes();
}

void MainWindow::on_checkBox_pistonForce_Pk_centripetal_clicked()
{
    if(uiList.checkBox_pistonForce_Pk_centripetal->isChecked())
    {
        chart->addSeries(*pistonForce_Pk_centripetal);
    }
    else
    {
        chart->removeSeries(*pistonForce_Pk_centripetal);
    }

    chart->refreshAxes();
}

void MainWindow::on_checkBox_torqueCrankshaft_clicked()
{
    if(uiList.checkBox_torqueCrankshaft->isChecked())
    {
        chart->addSeries(*torqueCrankshaft);
    }
    else
    {
        chart->removeSeries(*torqueCrankshaft);
    }

    chart->refreshAxes();
}

void MainWindow::on_checkBox_torque_Pk_clicked()
{
    if(uiList.checkBox_torque_Pk->isChecked())
    {
        chart->addSeries(*torque_Pk);
    }
    else
    {
        chart->removeSeries(*torque_Pk);
    }

    chart->refreshAxes();
}

void MainWindow::on_checkBox_torqueReactive_clicked()
{
    if(uiList.checkBox_torqueReactive->isChecked())
    {
        chart->addSeries(*torqueReactive);
    }
    else
    {
        chart->removeSeries(*torqueReactive);
    }

    chart->refreshAxes();
}

void MainWindow::on_tabWidget_parameters_currentChanged(int index)
{
    //wyswietlaj checkboxy dla sil
    if(index == 0)
    {
        chart->changeTitle("Sily w układzie tłokowo-korbowym");
        chart->removeAllSeries();

        connect(&calculations, &Calculations::changedValues, this, &MainWindow::updateForcesSeries);
        disconnect(&calculations, &Calculations::changedValues, this, &MainWindow::updateTorquesSeries);

        createForcesSeries();
        addForcesSeries();
    }
    //wyswietlaj checkboxy dla momentow
    else
    {
        chart->changeTitle("Momenty w układzie tłokowo-korbowym");
        chart->removeAllSeries();

        disconnect(&calculations, &Calculations::changedValues, this, &MainWindow::updateForcesSeries);
        connect(&calculations, &Calculations::changedValues, this, &MainWindow::updateTorquesSeries);

        createTorquesSeries();
        addTorquesSeries();
    }

    chart->refreshAxes();
}
