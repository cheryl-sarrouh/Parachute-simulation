#include "chute.h"
#include "ui_chute.h"
#include<iostream>
#include<QPainter>
#include<QPen>
#include <QtMath>
#include<cmath>
#include"plot.h"

using namespace std;

chute::chute(double weight, double height, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chute)
{
    ui->setupUi(this);
    this->weight=weight;

    this->height=height; //position initiale
    this->vitesse=0; //vitesse initiale
    this->position=height;
    this->temps=-0.02; //comme ca on commence de 0 (en progres())
    this->td=((pow(10,-5)*pow(height,2))-(0.048*height)+83.8); //interpolation de td
    this->parachute=false; //le parachute ne parait pas avant temps=timedeployment
    this->g=9.8;
    this->k=(9.8*(weight)/(70*70)); //On considere vitesse limite de chute libre=70m/s
    this->dt=0.02; //pas de calcul

    QObject::connect(&simulate,SIGNAL(timeout()),this,SLOT(progres()));
    ui->vitesse->setText(QString("Speed: 0m/s"));
    ui->position->setText(QString("Position: "+QString::number(height)+" m"));


}

chute::~chute()
{
    delete ui;
}

void chute::paintEvent(QPaintEvent *e)
{

        QPainter painter(this);
        painter.fillRect(200,0,400,700,Qt::white);

        double center=50+((height-position)*700/height);

        if(parachute==true) // avec parachute
        {
            painter.drawEllipse(340,center-160,120,120);
            painter.fillRect(300,center-100,200,200,Qt::white);

            painter.drawLine(400,center-20,340,center-100);
            painter.drawLine(400,center-20,460,center-100);
            painter.drawLine(340,center-100,460,center-100);
        }

        painter.drawEllipse(390,center-60,20,20);
            painter.drawLine(400,center-40,400,center+40);
            painter.drawLine(400,center-20,380,center);
            painter.drawLine(400,center-20,420,center);
            painter.drawLine(400,center+40,380,center+60);
            painter.drawLine(400,center+40,420,center+60);
}

double chute::fonctionv(double t, double x, double v)
{
    return (g-((k/weight)*v*v)); // dv/dt=g-(k/m)*v*v
}

double chute::fonctionx(double t, double x, double v)
{
    return -v; // dx/dt=v (si on ne met pas -v, le parachutiste monte vers le haut)
}

double chute::k1x(double t, double x, double v)
{
    return fonctionx(t,x,v); // k1(fx)=v
}

double chute::k2x(double t, double x, double v)
{
    return fonctionx(t+(dt/2), x+((dt/2)*k1x(t,x,v)),v+((dt/2)*k1v(t,x,v)));
}

double chute::k3x(double t, double x, double v)
{
    return fonctionx(t+dt, x+(dt*k2x(t,x,v)), v+(dt*k2v(t,x,v)));
}

double chute::k1v(double t, double x, double v)
{
  return fonctionv(t,x,v); // k1(fv)=g-(k/m)vi*vi
}

double chute::k2v(double t, double x, double v)
{
    return fonctionv(t+(dt/2), x+((dt/2)*k1x(t,x,v)),v+((dt/2)*k1v(t,x,v)));
}

double chute::k3v(double t, double x, double v)
{
    return fonctionv(t+dt, x+(dt*k2x(t,x,v)), v+(dt*k2v(t,x,v)));
}



void chute::on_jump_clicked()
{
    RungeKutta.clear();
    vitesseVec.clear();
    accelerationVec.clear();
    tempsVec.clear();
    simulate.setInterval(10);
    simulate.start();
}
void chute::progres(){

    temps=temps+dt;


    if ( temps <= td) //chute libre
    {   k=(9.8*(weight)/(70*70)); //On considere vitesse limite de chute libre=70m/s
        vitesse=vitesse+((dt/6)*(k1v(temps,position,vitesse)+4*k2v(temps,position,vitesse)+k3v(temps,position,vitesse)));
        position=position+((dt/6)*(k1x(temps,position,vitesse)+4*k2x(temps,position,vitesse)+k3x(temps,position,vitesse)));
        //cout<<vitesse;
    }
    else if(temps>td){
       parachute=true;
       k=(9.8*weight)/(6*6); //on considere vitesse d'atterrissage = 6m/s
       vitesse=vitesse+((dt/6)*(k1v(temps,position,vitesse)+4*k2v(temps,position,vitesse)+k3v(temps,position,vitesse)));
       position=position+((dt/6)*(k1x(temps,position,vitesse)+4*k2x(temps,position,vitesse)+k3x(temps,position,vitesse)));}

    tempsVec.push_back(temps);
    vitesseVec.push_back(vitesse*100); // On a multiplier par 100 pour mieux visualiser la courbe de la vitesse
    RungeKutta.push_back(position);
    accelerationVec.push_back((g-((k/weight)*pow(vitesse,2.0)))*10); //a=dv/dt= g-(k/m)v^2 et on multiplie par 10 pour mieux visulaliser la courbe de l'acceleration

    repaint();
    ui->vitesse->setText("Speed: "+QString::number(vitesse)+" m/s");
    ui->position->setText("Position: "+QString::number(position)+" m");
    if(position<=0){  //arreter la simulation quand le parachutise atterit
        simulate.stop();
        position=height;
        parachute=false;
        vitesse=0;
        temps=0;

    }


}



void chute::on_graphs_clicked()
{
    plot *p = new plot();
        p->show();
        p->draw(tempsVec, RungeKutta, vitesseVec, accelerationVec);

}
