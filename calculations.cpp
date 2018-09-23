#include "calculations.h"

Calculations::Calculations()
{
    for(int i=0; i <= SIZE; i++)
    {
        alfa.push_back(i * M_PI / 180);
    }
}

//pobranie wartosci zmiennych do obliczen sil z wartosci ustawionych sliderami na poczatku programu do poczatkowego ustaienia wartosci
void Calculations::setDataValues(unsigned int gasPressure, unsigned int massPiston, unsigned int massCrankPin, unsigned int massConnectingRod, double d, double r, double l, double n)
{
    this->gasPressure = gasPressure * 1000;                     //konwersja [kPa] -> [Pa]
    this->massPiston = massPiston * 0.001;                      //konwersja [g]   -> [kg]
    this->massCrankPin = massCrankPin * 0.001;                  //konwersja [g]   -> [kg]
    this->massConnectingRod = massConnectingRod * 0.001;        //konwersja [g]   -> [kg]

    this->d = d * 0.01;         //konwersja [cm] -> [m]
    this->r = r * 0.01;         //konwersja [cm] -> [m]
    this->l = l * 0.01;         //konwersja [cm] -> [m]
    this->n = n;                //[obr/min]

    //obliczenia innych pomocniczych zmiennych (dlugosci, katow, mas, itp.)
    calculate_otherValues();
}

void Calculations::set_gasPressure(int gasPressure)
{
    this->gasPressure = static_cast<unsigned int>(gasPressure) * 1000;

    emit changedValues();

//    cout << "gasPressure = " << this->gasPressure << "[Pa]" << endl;
}

void Calculations::set_d(int d)
{
    this->d = d * 0.01;

    emit changedValues();

//    cout << "d = " << this->d << "[m]" << endl;
}

void Calculations::set_r(int r)
{
    this->r = r * 0.01;

    emit changedValues();

//    cout << "r = " << this->r << "[m]" << endl;
}

void Calculations::set_l(int l)
{
    this->l = l * 0.01;

    emit changedValues();

//    cout << "l = " << this->l << "[m]" << endl;
}

void Calculations::set_n(int n)
{
    this->n = n;

    emit changedValues();

//    cout << "n = " << this->n << endl;
}

void Calculations::set_massPiston(int massPiston)
{
    this->massPiston = static_cast<double>(massPiston) * 0.001;

    emit changedValues();

//    cout << "massPiston = " << this->massPiston << endl;
}

void Calculations::set_massCrankPin(int massCrankPin)
{
    this->massCrankPin = static_cast<double>(massCrankPin) * 0.001;

    emit changedValues();

//    cout << "massCrankPin = " << this->massCrankPin << endl;
}

void Calculations::set_massConnectingRod(int massConnectingRod)
{
    this->massConnectingRod = static_cast<double>(massConnectingRod) * 0.001;

    emit changedValues();

//    cout << "massConnectingRod = " << this->massConnectingRod << endl;
}

//obliczenia innych pomocniczych zmiennych (dlugosci, katow, mas, itp.)
void Calculations::calculate_otherValues()
{
    //uklad dwoch mas zastepczych skupionych w srodku sworznia tlokowego oraz czopa korbowego
    massReciprocatingMotion = massPiston + 0.25 * massConnectingRod;     //[kg]
    massRotationalMotion = massCrankPin + 0.75 * massConnectingRod;      //[kg]

    lambda = r / l;             //[m]
    omega = M_PI * n / 30;      //konwersja [obr/min] -> [1/s]
}

//obliczenia wszystkich sil
void Calculations::calculate_forces()
{
    calculate_gasPressureForce();
    calculate_inertialForce();
    calculate_beta();
    calculate_h();
    calculate_a();
    calculate_pistonForce();
    calculate_pistonForce_N();
    calculate_pistonForce_Pk();
    calculate_pistonForce_Pk_tangencial();
    calculate_pistonForce_Pk_centripetal();
}

//obliczenia wszystkich momentow
void Calculations::calculate_torques()
{
    calculate_torqueCrankshaft();
    calculate_torque_Pk();
    calculate_torqueReactive();
}

//oblicz wszystko
void Calculations::calculate_all()
{
    //obliczenia innych pomocniczych zmiennych (dlugosci, katow, mas, itp.)
    calculate_otherValues();

    calculate_forces();
    calculate_torques();
}

//obliczenia sily cisnienia gazow F_g
void Calculations::calculate_gasPressureForce()
{
    gasPressureForce.clear();

    for(int i=0; i <= SIZE; i++)
    {
        gasPressureForce.push_back(M_PI * d * d / 4 * (gasPressure - ATMOSPHERIC_PRESSURE));
    }
}

//obliczenia sily bezwladnosci F_b
void Calculations::calculate_inertialForce()
{
    reciprocatingInertialForce.clear();
    rotationalInertialForce.clear();
    inertialForce.clear();

    for(int i=0; i <= SIZE; i++)
    {
        //sila bezwladnosci w ruchu posuwisto-zwrotnym - suma sil bezwladnosci pierwszego i drugiego rzedu P_p = P_p' + P_p''
        reciprocatingInertialForce.push_back(massReciprocatingMotion * omega * omega * (cos(alfa.at(i)) + lambda * cos(2 * alfa.at(i))));
        //sila bezwladnosci w ruchu obrotowym P_o
        rotationalInertialForce.push_back(massRotationalMotion * r * omega * omega);
        //calkowita sila bezwladnosci F_b = P_p + P_o
        inertialForce.push_back(reciprocatingInertialForce.at(i) + rotationalInertialForce.at(i));
    }
}

//obliczenia kata pomiedzy korbowodem a osia przechodzaca przez srodek sworznia tlokowego i srodek czopa korbowego
void Calculations::calculate_beta()
{
    beta.clear();

    for(int i=0; i <= SIZE; i++)
    {
        //wzor z zaleznosci geometrycznych
        beta.push_back(abs(asin(r * sin(alfa.at(i)) / l)));
    }
}

//obliczenia odleglosci miedzy pktem A (srodkiem sworznia tlokowego), a pktem O (srodkiem czopa korbowego) h
void Calculations::calculate_h()
{
    h.clear();

    for(int i=0; i <= SIZE; i++)
    {
        h.push_back(r * cos(alfa.at(i)) + l * cos(beta.at(i)));
    }
}

//obliczenia odleglosci (promienia), na ktorym dziala moment od sily P_k z pktu O wzgledem pktu B
void Calculations::calculate_a()
{
    a.clear();

    for(int i=0; i <= SIZE; i++)
    {
        a.push_back(h.at(i) * sin(beta.at(i)));
    }
}

//obliczenia sily wypadkowej dzialajacej na tlok P_t
void Calculations::calculate_pistonForce()
{
    pistonForce.clear();

    for(int i=0; i <= SIZE; i++)
    {
        //suma sily cisnienia gazow i bezwladnosci w ruchu posuwisto-zwrotnym P_t = F_g + P_p
        pistonForce.push_back(gasPressureForce.at(i) + reciprocatingInertialForce.at(i));
    }
}

//obliczenia skladowej prostopadlej do osi cylindra sily dzialajacej na tlok N
void Calculations::calculate_pistonForce_N()
{
    pistonForce_N.clear();

    for(int i=0; i <= SIZE; i++)
    {
        pistonForce_N.push_back(pistonForce.at(i) * tan(beta.at(i)));
    }
}

//obliczenia skladowej wzdluznej do osi korbowodu sily dzialajacej na tlok P_k
void Calculations::calculate_pistonForce_Pk()
{
    pistonForce_Pk.clear();

    for(int i=0; i <= SIZE; i++)
    {
        pistonForce_Pk.push_back(pistonForce.at(i) / cos(beta.at(i)));
    }
}

//obliczenia skladowej stycznej do okregu o promieniu r skladowej wzdluznej sily dzialajacej na tlok T
void Calculations::calculate_pistonForce_Pk_tangencial()
{
    pistonForce_Pk_tangencial.clear();

    for(int i=0; i <= SIZE; i++)
    {
        pistonForce_Pk_tangencial.push_back(pistonForce_Pk.at(i) * sin(alfa.at(i) + beta.at(i)));
    }
}

//obliczenia skladowej doosiowej (promieniowej) skladowej wzdluznej sily dzialajacej na tlok R
void Calculations::calculate_pistonForce_Pk_centripetal()
{
    pistonForce_Pk_centripetal.clear();

    for(int i=0; i <= SIZE; i++)
    {
        pistonForce_Pk_centripetal.push_back(pistonForce_Pk.at(i) * cos(alfa.at(i) + beta.at(i)));
    }
}

//obliczenia chwilowego momentu obrotowego na wale korbowym M
void Calculations::calculate_torqueCrankshaft()
{
    torqueCrankshaft.clear();

    for(int i=0; i <= SIZE; i++)
    {
        torqueCrankshaft.push_back(pistonForce_Pk_tangencial.at(i) * r);
    }
}

//obliczenia momentu od sily P_k na ramieniu a
void Calculations::calculate_torque_Pk()
{
    torque_Pk.clear();

    for(int i=0; i <= SIZE; i++)
    {
        //a to odleglosci (promienia), na ktorym dziala moment od sily P_k z pktu O wzgledem pktu B
        torque_Pk.push_back(pistonForce_Pk.at(i) * a.at(i));
    }
}

//obliczenia momentu reakcyjnego dzialajacego na kadlub silnika M_r
void Calculations::calculate_torqueReactive()
{
    torqueReactive.clear();

    for(int i=0; i <= SIZE; i++)
    {
        //h to odleglosc miedzy pktem A (srodkiem sworznia tlokowego), a pktem O (srodkiem czopa korbowego)
        torqueReactive.push_back(pistonForce_N.at(i) * h.at(i));
    }
}

QVector<double> *Calculations::get_alfa()
{
    return &alfa;
}

QVector<double> *Calculations::get_gasPressureForce()
{
    return &gasPressureForce;
}

QVector<double> *Calculations::get_inertialForce()
{
    return &inertialForce;
}

QVector<double> *Calculations::get_h()
{
    return &h;
}

QVector<double> *Calculations::get_beta()
{
    return &beta;
}

QVector<double> *Calculations::get_a()
{
    return &a;
}

QVector<double> *Calculations::get_pistonForce()
{
    return &pistonForce;
}

QVector<double> *Calculations::get_pistonForce_N()
{
    return &pistonForce_N;
}

QVector<double> *Calculations::get_pistonForce_Pk()
{
    return &pistonForce_Pk;
}

QVector<double> *Calculations::get_pistonForce_Pk_tangencial()
{
    return &pistonForce_Pk_tangencial;
}

QVector<double> *Calculations::get_pistonForce_Pk_centripetal()
{
    return &pistonForce_Pk_centripetal;
}

QVector<double> *Calculations::get_torqueCrankshaft()
{
    return &torqueCrankshaft;
}

QVector<double> *Calculations::get_torque_Pk()
{
    return &torque_Pk;
}

QVector<double> *Calculations::get_torqueReactive()
{
    return &torqueReactive;
}
