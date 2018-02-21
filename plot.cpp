#include "plot.h"
#include "ui_plot.h"
#include<iostream>

using namespace std;

plot::plot(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::plot)
{
    ui->setupUi(this);
}

plot::~plot()
{
    delete ui;
}
void plot::draw(QVector<double> temps, QVector<double> x, QVector<double> v, QVector<double> a) {
    cout <<"Temps: "<<temps.length()<<endl;
    cout <<"X: "<<x.length()<<endl;

    ui->plotting->addGraph(); //C'est le graphe de la position
    ui->plotting->graph(0)->setPen(QPen(Qt::blue));

    ui->plotting->addGraph(); //C'est le graphe de la vitesse
    ui->plotting->graph(1)->setPen(QPen(Qt::green));

    ui->plotting->addGraph(); //C'est le graphe de l'acceleration
    ui->plotting->graph(2)->setPen(QPen(Qt::red));



    ui->plotting->xAxis2->setVisible(true);
    ui->plotting->xAxis2->setTickLabels(false);

    ui->plotting->yAxis2->setVisible(true);
    ui->plotting->yAxis2->setTickLabels(false);

    connect(ui->plotting->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotting->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->plotting->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotting->yAxis2, SLOT(setRange(QCPRange)));

    ui->plotting->graph(0)->setData(temps, x);
    ui->plotting->graph(1)->setData(temps, v);
    ui->plotting->graph(2)->setData(temps, a);

    ui->plotting->graph(0)->rescaleAxes(true);
    ui->plotting->graph(1)->rescaleAxes(true);
    ui->plotting->graph(2)->rescaleAxes(true);

    ui->plotting->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->plotting->rescaleAxes();
}

