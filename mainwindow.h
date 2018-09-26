#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QTabWidget>

#include "ui_list.h"
#include "calculations.h"
#include "chart.h"
#include "series.h"

#ifndef __ANDROID__
#include <QHBoxLayout>
#endif

using namespace std;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void createForcesSeries();
    void updateForcesSeries();

    void createTorquesSeries();
    void updateTorquesSeries();

    void addForcesSeries();
    void addTorquesSeries();

private slots:
    void on_checkBox_gasPressureForce_clicked();
    void on_checkBox_inertialForce_clicked();
    void on_checkBox_pistonForce_clicked();
    void on_checkBox_pistonForce_N_clicked();
    void on_checkBox_pistonForce_Pk_clicked();
    void on_checkBox_pistonForce_Pk_tangencial_clicked();
    void on_checkBox_pistonForce_Pk_centripetal_clicked();
    void on_checkBox_torqueCrankshaft_clicked();
    void on_checkBox_torque_Pk_clicked();
    void on_checkBox_torqueReactive_clicked();
    void on_tabWidget_parameters_currentChanged(int index);

    //sygnaly zmieniajace wartosc tekstu w labelach, wywolywane po zmianie wartosci sliderow
    void setNum_label_gasPressure();
    void setNum_label_n();
    void setNum_label_massPiston();
    void setNum_label_massCrankPin();
    void setNum_label_massConnectingRod();

private:
    void connectSliders();

    void connectCalculations();

    void connectCheckboxes();

    void connectTabWidgets();

    Chart *chart = new Chart();

    QWidget *list = new QWidget(this);

    QWidget *central = new QWidget(this);

    Ui::Form uiList;

    Calculations calculations;

    //serie danych sil
    Series *gasPressureForce;
    Series *inertialForce;
    Series *pistonForce;
    Series *pistonForce_N;
    Series *pistonForce_Pk;
    Series *pistonForce_Pk_tangencial;
    Series *pistonForce_Pk_centripetal;

    //serie danych momentow sil
    Series *torque_Pk;
    Series *torqueCrankshaft;
    Series *torqueReactive;

#ifndef __ANDROID__
    QHBoxLayout *horizontalLayout = new QHBoxLayout();
#endif

};

#endif // MAINWINDOW_H
