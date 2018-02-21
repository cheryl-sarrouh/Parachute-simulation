#include "graphe.h"
#include "ui_graphe.h"

graphe::graphe(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::graphe)
{
    ui->setupUi(this);
}

graphe::~graphe()
{
    delete ui;
}
