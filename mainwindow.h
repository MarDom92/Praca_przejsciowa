#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QUiLoader>

#include "ui_list.h"

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
    Chart *chart = new Chart();

    QWidget *list = new QWidget(this);

    QWidget *central = new QWidget(this);

#ifndef __ANDROID__
    QHBoxLayout *horizontalLayout = new QHBoxLayout(this);
#endif

};

#endif // MAINWINDOW_H
