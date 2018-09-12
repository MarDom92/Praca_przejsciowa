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
                       unsigned int massConnectingRod, float d, float r, float l, float n);

    void calculate_gasPressureForce();

    void calculate_inertialForce();

    void updateChart();

private:
    //stale cisneinei atmosferyczne [Pa]
    const unsigned int atmosphericPressure = 100000;

    //tablica katow od 0 do 360 stopni [rad]
    float alfa[361];

    //cisnienie gazu [Pa]
    unsigned int gasPressure;

    //masa tloka, masa czopu korbowego, masa korbowodu [kg]
    unsigned int massPiston, massCrankPin, massConnectingRod;

    //masa wykonujaca ruch postepowy, masa wykonujaca ruch obrotowy [kg]
    float massReciprocatingMotion, massRotationalMotion;

    //srednica cylindra, promien wykorbienia, dlugosc tloka [m]
    float d, r, l;

    //wspolczynnik korbowodu - stosunek r do l [-]
    float lambda;

    //predkosc obrotowa walu korbowego [obr/min]
    float n;

    //predkosc katowa walu korbowego [1/s]
    float omega;

    //sila cisnienia gazu w cylindrze
    float gasPressureForce[361];

    //sila bezwladnosci ruchu posuwisto-zwrotnego, sila bezwladnosci ruchu obrotowego, calkowita sila bezwladnosci
    float reciprocatingInertialForce[361], rotationalInertialForce[361], inertialForce[361];


};

#endif // CALCULATIONS_H
