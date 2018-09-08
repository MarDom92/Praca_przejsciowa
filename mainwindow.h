#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUiLoader>

#ifndef __ANDROID__
#include <QHBoxLayout>
#endif

#include "chart.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Chart *chart = new Chart(this);

    QWidget *list = new QWidget(this);

    QWidget central;

#ifndef __ANDROID__
    QHBoxLayout *horizontalLayout = new QHBoxLayout(this);
#endif

};

#endif // MAINWINDOW_H
