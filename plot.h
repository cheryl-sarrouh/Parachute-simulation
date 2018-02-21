#ifndef PLOT_H
#define PLOT_H

#include <QMainWindow>

namespace Ui {
class plot;
}

class plot : public QMainWindow
{
    Q_OBJECT

public:
    explicit plot(QWidget *parent = 0);
    void draw(QVector<double> temps, QVector<double> x, QVector<double> v, QVector<double> a);
    ~plot();

private:
    Ui::plot *ui;
};

#endif // PLOT_H
