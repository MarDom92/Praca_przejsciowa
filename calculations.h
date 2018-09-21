#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include <QObject>
#include <QVector>
#include <cmath>
#include <iostream>
using namespace std;


class Calculations : public QObject
{
    Q_OBJECT

public:
    Calculations();

public slots:
    void setDataValues(unsigned int gasPressure, unsigned int massPiston, unsigned int massCrankPin,
                       unsigned int massConnectingRod, double d, double r, double l, double n);

public slots:
    void set_gasPressure(int value);
    void set_d(int value);
    void set_r(int value);
    void set_l(int value);
    void set_n(int value);
    void set_massPiston(int value);
    void set_massCrankPin(int value);
    void set_massConnectingRod(int value);

public:
    void calculate_gasPressureForce();
    void calculate_inertialForce();
    void calculate_beta();
    void calculate_h();
    void calculate_a();
    void calculate_pistonForce();
    void calculate_pistonForce_N();
    void calculate_pistonForce_Pk();
    void calculate_pistonForce_Pk_tangencial();
    void calculate_pistonForce_Pk_centripetal();

    void calculate_torqueCrankshaft();
    void calculate_torque_Pk();
    void calculate_torqueReactive();

public:
    QVector<double> *get_alfa();
    QVector<double> *get_gasPressureForce();
    QVector<double> *get_inertialForce();
    QVector<double> *get_beta();
    QVector<double> *get_h();
    QVector<double> *get_a();
    QVector<double> *get_pistonForce();
    QVector<double> *get_pistonForce_N();
    QVector<double> *get_pistonForce_Pk();
    QVector<double> *get_pistonForce_Pk_tangencial();
    QVector<double> *get_pistonForce_Pk_centripetal();

    QVector<double> *get_torqueCrankshaft();
    QVector<double> *get_torque_Pk();
    QVector<double> *get_torqueReactive();

    void updateChart();

private:
    const int SIZE = 360;

    //stale cisnienie atmosferyczne P_atm [Pa]
    const unsigned int ATMOSPHERIC_PRESSURE = 100000;

    //tablica katow od 0 do 360 stopni [rad]
    QVector<double> alfa;

    //cisnienie gazu [Pa] p_g
    unsigned int gasPressure;

    //masa tloka m_t, masa czopu korbowego m_w, masa korbowodu m_k [kg]
    unsigned int massPiston, massCrankPin, massConnectingRod;

    //masa wykonujaca ruch postepowy m_p, masa wykonujaca ruch obrotowy m_o [kg]
    double massReciprocatingMotion, massRotationalMotion;

    //srednica cylindra, promien wykorbienia, dlugosc tloka [m]
    double d, r, l;

    //h to odleglosc midzy pktem A (srodkiem sworznia tlokowego), a pktem O (srodkiem czopa korbowego) [m]
    QVector<double> h;

    //obliczenia odleglosci (promienia), na ktorym dziala moment od sily P_k z pktu O wzgledem pktu B [m]
    QVector<double> a;

    //wspolczynnik korbowodu - stosunek r do l [-]
    double lambda;

    //predkosc obrotowa walu korbowego [obr/min]
    double n;

    //predkosc katowa walu korbowego [1/s]
    double omega;

    //tablica katow pomiedzy korbowodem a osia przechodzaca przez srodek sworznia tlokowego i srodek czopa korbowego
    QVector<double> beta;

    //sila cisnienia gazu w cylindrze F_g [N]
    QVector<double> gasPressureForce;

    //sila bezwladnosci ruchu posuwisto-zwrotnego P_p, sila bezwladnosci ruchu obrotowego P_o, calkowita sila bezwladnosci F_b [N]
    QVector<double> reciprocatingInertialForce, rotationalInertialForce, inertialForce;

    //sila wypadkowa dzialajaca na tlok P_t [N]
    QVector<double> pistonForce;

    //skladowa prostopadla do osi cylindra sily dzialajacej na tlok N [N]
    QVector<double> pistonForce_N;

    //skladowa wzdluzna do osi korbowodu sily dzialajacej na tlok P_k [N]
    QVector<double> pistonForce_Pk;

    //skladowa styczna do okregu o promieniu r skladowej wzdluznej sily dzialajacej na tlok T [N]
    QVector<double> pistonForce_Pk_tangencial;

    //skladowa doosiowa (promieniowa) skladowej wzdluznej sily dzialajacej na tlok R [N]
    QVector<double> pistonForce_Pk_centripetal;

    //chwilowy moment obrotowy na wale korbowym M [Nm]
    QVector<double> torqueCrankshaft;

    //moment M_Pk [Nm]
    QVector<double> torque_Pk;

    //moment reakcyjny dzialajacy na kadlub silnika M_r [Nm]
    QVector<double> torqueReactive;
};

#endif // CALCULATIONS_H
