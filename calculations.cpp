#include "calculations.h"

Calculations::Calculations()
{
    for(int i=0; i<=360; i++)
    {
        alfa[i] = i * M_PI / 180;
    }
}

//pobranie wartosci zmiennych do obliczen sil z wartosci ustawionych sliderami
void Calculations::setDataValues(unsigned int gasPressure, unsigned int massPiston, unsigned int massCrankPin, unsigned int massConnectingRod, float d, float r, float l, float n)
{
    this->gasPressure = gasPressure * 1000;                     //konwersja [kPa] -> [Pa]
    this->massPiston = massPiston * 0.001;                      //konwersja [g]   -> [kg]
    this->massCrankPin = massCrankPin * 0.001;                  //konwersja [g]   -> [kg]
    this->massConnectingRod = massConnectingRod * 0.001;        //konwersja [g]   -> [kg]

    this->d = d;        //konwersja [cm] -> [m]
    this->r = r;        //konwersja [cm] -> [m]
    this->l = l;        //konwersja [cm] -> [m]
    this->n = n;        //[obr/min]

    //uklad dwoch mas zastepczych skupionych w srodku sworznia tlokowego oraz czopa korbowego
    massReciprocatingMotion = float(massPiston + 0.25 * massConnectingRod);     //[kg]
    massRotationalMotion = float(massCrankPin + 0.75 * massConnectingRod);      //[kg]

    lambda = r / l;             //[m]
    omega = M_PI * n / 30;      //konwersja [obr/min] -> [1/s]
}

//obliczenia sily cisnienia gazow
void Calculations::calculate_gasPressureForce()
{
    for(int i=0; i<=360; i++)
    {
        gasPressureForce[i] = M_PI * d * d / 4 * (gasPressure - atmosphericPressure);
    }
}

//obliczenia sily bezwladnosci
void Calculations::calculate_inertialForce()
{
    for(int i=0; i<=360; i++)
    {
        //sila bezwladnosci w ruchu posuwisto-zwrotnym - suma sil bezwladnosci pierwszego i drugiego rzedu
        reciprocatingInertialForce[i] = massReciprocatingMotion * omega * omega * (cos(alfa[i]) + lambda * cos(2 * alfa[i]));
        //sila bezwladnosci w ruchu obrotowym
        rotationalInertialForce[i] = massRotationalMotion * r * omega * omega;
        //calkowita sila bezwladnosci
        inertialForce[i] = reciprocatingInertialForce[i] + rotationalInertialForce[i];
    }
}

//obliczenia sily wypadkowej dzialajacej na tlok
void Calculations::calculate_pistonForce()
{
    for(int i=0; i<=360; i++)
    {
        //suma sily cisnienia gazow i bezwladnosci w ruchu posuwisto-zwrotnym
        pistonForce[i] = gasPressureForce[i] + reciprocatingInertialForce[i];
    }
}

void Calculations::updateChart()
{
    for(int i=0; i<=360; i++)
    {
        cout << i << " alfa[i]=" << alfa[i] << " gasPressureForce=" << gasPressureForce[i] << " inertialForce=" << inertialForce[i] << " pistonForce=" << pistonForce[i] << endl;
    }
}
