#include "calculations.h"

Calculations::Calculations()
{
    for(int i=0; i<=360; i++)
    {
        alfa[i] = i * M_PI / 180;
        cout << "alfa[i]=" << alfa[i] << endl;
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
        cout << "gasPressureForce=" << gasPressureForce[i] << endl;
    }
}

//obliczenia sily bezwladnosci
void Calculations::calculate_inertialForce()
{
    for(int i=0; i<=360; i++)
    {
        //suma sil bezwladnosci pierwszego i drugiego rzedu w ruchu posuwisto-zwrotnym
        reciprocalInertialForce[i] = massReciprocatingMotion * omega * omega * (cos(alfa[i]) + lambda * cos(2 * alfa[i]));
        //sila bezwladnosci w ruchu obrotowym
        rotationalInertialForce[i] = massRotationalMotion * r * omega * omega;
        //calkowita sila bezwladnosci
        inertialForce[i] = reciprocalInertialForce[i] + rotationalInertialForce[i];

        cout << "inertialForce=" << inertialForce[i] << endl;
    }
}

void Calculations::updateChart()
{

}
