#include "choix.h"
#include "ui_choix.h"
#include"chute.h"

choix::choix(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::choix)
{
    ui->setupUi(this);

}

choix::~choix()
{
    delete ui;
}



void choix::on_go_clicked()
{
    chute * ch= new chute((ui->Masse->value())+10,ui->x0->value()); //Masse du parachutiste +10 car la masse moyenne d'un parachute est de 9-11kg
    ch->show();
}

