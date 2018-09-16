#include "calculations.h"

Calculations::Calculations()
{
    cout << "konstruktor poczatek" << endl;
    for(int i=0; i<=360; i++)
    {
        alfa[i] = i * M_PI / 180;
    }
    for(int i=0; i<=360; i++)
    {
        cout << i << " alfa[i]=" << alfa[i] << endl;
    }
    cout << "konstruktor koniec" << endl;
}

//pobranie wartosci zmiennych do obliczen sil z wartosci ustawionych sliderami
void Calculations::setDataValues(unsigned int gasPressure, unsigned int massPiston, unsigned int massCrankPin, unsigned int massConnectingRod, double d, double r, double l, double n)
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
    massReciprocatingMotion = massPiston + 0.25 * massConnectingRod;     //[kg]
    massRotationalMotion = massCrankPin + 0.75 * massConnectingRod;      //[kg]

    lambda = r / l;             //[m]
    omega = M_PI * n / 30;      //konwersja [obr/min] -> [1/s]
}

//obliczenia sily cisnienia gazow F_g
void Calculations::calculate_gasPressureForce()
{
    for(int i=0; i<=360; i++)
    {
        gasPressureForce[i] = M_PI * d * d / 4 * (gasPressure - atmosphericPressure);
    }
}

//obliczenia sily bezwladnosci F_b
void Calculations::calculate_inertialForce()
{
    for(int i=0; i<=360; i++)
    {
        //sila bezwladnosci w ruchu posuwisto-zwrotnym - suma sil bezwladnosci pierwszego i drugiego rzedu P_p = P_p' + P_p''
        reciprocatingInertialForce[i] = massReciprocatingMotion * omega * omega * (cos(alfa[i]) + lambda * cos(2 * alfa[i]));
        //sila bezwladnosci w ruchu obrotowym P_o
        rotationalInertialForce[i] = massRotationalMotion * r * omega * omega;
        //calkowita sila bezwladnosci F_b = P_p + P_o
        inertialForce[i] = reciprocatingInertialForce[i] + rotationalInertialForce[i];
    }
}

//obliczenia kata pomiedzy korbowodem a osia przechodzaca przez srodek sworznia tlokowego i srodek czopa korbowego
void Calculations::calculate_beta()
{
    for(int i=0; i<=360; i++)
    {
        //wzor z zaleznosci geometrycznych
        beta[i] = abs(asin(r * sin(alfa[i]) / l));
    }
}

//obliczenia sily wypadkowej dzialajacej na tlok P_t
void Calculations::calculate_pistonForce()
{
    for(int i=0; i<=360; i++)
    {
        //suma sily cisnienia gazow i bezwladnosci w ruchu posuwisto-zwrotnym P_t = F_g + P_p
        pistonForce[i] = gasPressureForce[i] + reciprocatingInertialForce[i];
    }
}

//obliczenia skladowej prostopadlej do osi cylindra sily dzialajacej na tlok N
void Calculations::calculate_pistonForce_N()
{
    for(int i=0; i<=360; i++)
    {
        pistonForce_N[i] = pistonForce[i] * tan(beta[i]);
    }
}

//obliczenia skladowej wzdluznej do osi korbowodu sily dzialajacej na tlok P_k
void Calculations::calculate_pistonForce_Pk()
{
    for(int i=0; i<=360; i++)
    {
        pistonForce_Pk[i] = pistonForce[i] / cos(beta[i]);
    }
}

//obliczenia skladowej stycznej do okregu o promieniu r skladowej wzdluznej sily dzialajacej na tlok T
void Calculations::calculate_pistonForce_Pk_tangencial()
{
    for(int i=0; i<=360; i++)
    {
        pistonForce_Pk_tangencial[i] = pistonForce_Pk[i] * sin(alfa[i] + beta[i]);
    }
}

//obliczenia skladowej doosiowej (promieniowej) skladowej wzdluznej sily dzialajacej na tlok R
void Calculations::calculate_pistonForce_Pk_centripetal()
{
    for(int i=0; i<=360; i++)
    {
        pistonForce_Pk_centripetal[i] = pistonForce_Pk[i] * cos(alfa[i] + beta[i]);
    }
}

void Calculations::updateChart()
{
    for(int i=0; i<=360; i++)
    {
        cout << endl;
        cout << i << " alfa[i]=" << alfa[i] << " gasPressureForce=" << gasPressureForce[i] << " inertialForce=" << inertialForce[i] << " pistonForce=" << pistonForce[i] << endl;
        cout << i << " alfa[i]=" << alfa[i] << " beta=" << beta[i] << endl;
        cout << i << " alfa[i]=" << alfa[i] << " pistonForce[i]=" << pistonForce[i] << " pistonForce_N[i]=" << pistonForce_N[i] << " pistonForce_Pk[i]=" << pistonForce_Pk[i] << endl;
        cout << i << " alfa[i]=" << alfa[i] << " alfa[i] + beta[i]=" << alfa[i] + beta[i] << " sin(alfa[i] + beta[i])=" << sin(alfa[i] + beta[i]) << endl;
        cout << i << " alfa[i]=" << alfa[i] << " pistonForce_Pk_tangencial[i]=" << pistonForce_Pk_tangencial[i] << " pistonForce_Pk_centripetal[i]=" << pistonForce_Pk_centripetal[i] << endl;
    }
}
