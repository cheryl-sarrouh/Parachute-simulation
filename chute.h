#ifndef CHUTE_H
#define CHUTE_H

#include <QWidget>
#include<QTimer>

namespace Ui {
class chute;
}

class chute : public QWidget
{
    Q_OBJECT

public:
    explicit chute(double weight, double height, QWidget *parent = 0);
    ~chute();

private slots:
    void on_jump_clicked();
    void progres();

    void on_graphs_clicked();

private:
    Ui::chute *ui;
    double weight;

    double height;
    double position;
    double vitesse;
    double temps;
    double td;
    double k;
    double g;
    double dt;


    bool parachute;
    QTimer simulate;
    void paintEvent(QPaintEvent *e);

    QVector<double> tempsVec;
    QVector<double> vitesseVec;
    QVector<double> accelerationVec;
    QVector<double> RungeKutta;

    double fonctionv(double t, double x, double v);
    double fonctionx(double t, double x, double v);
    double k1x(double t, double x, double v);
    double k2x(double t, double x, double v);
    double k3x(double t, double x, double v);
    double k1v(double t, double x, double v);
    double k2v(double t, double x, double v);
    double k3v(double t, double x, double v);





    };

#endif // CHUTE_H
