#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include <cmath>

#include <iostream>
using namespace std;

class Calculations
{
public:
    Calculations();

    void setDataValues(unsigned int gasPressure, unsigned int massPiston, unsigned int massCrankPin,
                       unsigned int massConnectingRod, double d, double r, double l, double n);

    void calculate_gasPressureForce();

    void calculate_inertialForce();

    void calculate_h();

    void calculate_beta();

    void calculate_a();

    void calculate_pistonForce();

    void calculate_pistonForce_N();

    void calculate_pistonForce_Pk();

    void calculate_pistonForce_Pk_tangencial();

    void calculate_pistonForce_Pk_centripetal();

    void calculate_torqueCrankshaft();

    void calculate_torque_Pk();

    void calculate_torqueReactive();

    void updateChart();

private:
    //stale cisneinei atmosferyczne P_atm [Pa]
    const unsigned int atmosphericPressure = 100000;

    //tablica katow od 0 do 360 stopni [rad]
    double alfa[361];

    //cisnienie gazu [Pa] p_g
    unsigned int gasPressure;

    //masa tloka m_t, masa czopu korbowego m_w, masa korbowodu m_k [kg]
    unsigned int massPiston, massCrankPin, massConnectingRod;

    //masa wykonujaca ruch postepowy m_p, masa wykonujaca ruch obrotowy m_o [kg]
    double massReciprocatingMotion, massRotationalMotion;

    //srednica cylindra, promien wykorbienia, dlugosc tloka [m]
    double d, r, l;

    //h to odleglosc midzy pktem A (srodkiem sworznia tlokowego), a pktem O (srodkiem czopa korbowego) [m]
    double h[361];

    //obliczenia odleglosci (promienia), na ktorym dziala moment od sily P_k z pktu O wzgledem pktu B [m]
    double a[361];

    //wspolczynnik korbowodu - stosunek r do l [-]
    double lambda;

    //predkosc obrotowa walu korbowego [obr/min]
    double n;

    //predkosc katowa walu korbowego [1/s]
    double omega;

    //tablica katow pomiedzy korbowodem a osia przechodzaca przez srodek sworznia tlokowego i srodek czopa korbowego
    double beta[361];

    //sila cisnienia gazu w cylindrze F_g
    double gasPressureForce[361];

    //sila bezwladnosci ruchu posuwisto-zwrotnego P_p, sila bezwladnosci ruchu obrotowego P_o, calkowita sila bezwladnosci F_b
    double reciprocatingInertialForce[361], rotationalInertialForce[361], inertialForce[361];

    //sila wypadkowa dzialajaca na tlok P_t
    double pistonForce[361];

    //skladowa prostopadla do osi cylindra sily dzialajacej na tlok N
    double pistonForce_N[361];

    //skladowa wzdluzna do osi korbowodu sily dzialajacej na tlok P_k
    double pistonForce_Pk[361];

    //skladowa styczna do okregu o promieniu r skladowej wzdluznej sily dzialajacej na tlok T
    double pistonForce_Pk_tangencial[361];

    //skladowa doosiowa (promieniowa) skladowej wzdluznej sily dzialajacej na tlok R
    double pistonForce_Pk_centripetal[361];

    //chwilowy moment obrotowy na wale korbowym M
    double torqueCrankshaft[361];

    //moment M_Pk
    double torque_Pk[361];

    //moment reakcyjny dzialajacy na kadlub silnika M_r
    double torqueReactive[361];
};

#endif // CALCULATIONS_H
