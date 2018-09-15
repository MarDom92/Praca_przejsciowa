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

    void calculate_pistonForce();

    void calculate_beta();

    void updateChart();

private:
    //stale cisneinei atmosferyczne [Pa]
    const unsigned int atmosphericPressure = 100000;

    //tablica katow od 0 do 360 stopni [rad]
    double alfa[361];

    //cisnienie gazu [Pa]
    unsigned int gasPressure;

    //masa tloka, masa czopu korbowego, masa korbowodu [kg]
    unsigned int massPiston, massCrankPin, massConnectingRod;

    //masa wykonujaca ruch postepowy, masa wykonujaca ruch obrotowy [kg]
    double massReciprocatingMotion, massRotationalMotion;

    //srednica cylindra, promien wykorbienia, dlugosc tloka [m]
    double d, r, l;

    //wspolczynnik korbowodu - stosunek r do l [-]
    double lambda;

    //predkosc obrotowa walu korbowego [obr/min]
    double n, a;

    //predkosc katowa walu korbowego [1/s]
    double omega;

    //tablica katow pomiedzy korbowodem a osia przechodzaca przez srodek sworznia tlokowego i srodek czopa korbowego
    double beta[361];

    //sila cisnienia gazu w cylindrze
    double gasPressureForce[361];

    //sila bezwladnosci ruchu posuwisto-zwrotnego, sila bezwladnosci ruchu obrotowego, calkowita sila bezwladnosci
    double reciprocatingInertialForce[361], rotationalInertialForce[361], inertialForce[361];

    //sila wypadkowa dzialajaca na tlok
    double pistonForce[361];

};

#endif // CALCULATIONS_H
