#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ui_list.h"
#include "chart.h"
#include "calculations.h"

#ifndef __ANDROID__
#include <QHBoxLayout>
#endif


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Chart *chart = new Chart();

    QWidget *list = new QWidget(this);

    QWidget *central = new QWidget(this);

    Ui::Form uiList;

    Calculations calculations;

#ifndef __ANDROID__
    QHBoxLayout *horizontalLayout = new QHBoxLayout(this);
#endif

    void connectSliders();

};

#endif // MAINWINDOW_H
