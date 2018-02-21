#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"choix.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//   QPixmap bg("/Users/Cherryl/Desktop/try/got1.png");
//   bg=bg.scaled(this->size(), Qt::IgnoreAspectRatio);
//   QPalette palette;
//   palette.setBrush(QPalette::Background,bg);
//   this->setPalette(palette);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_SimulationStart_clicked()
{
    choix* c= new choix();
    c->show();

}
