#ifndef GRAPHE_H
#define GRAPHE_H

#include <QWidget>

namespace Ui {
class graphe;
}

class graphe : public QWidget
{
    Q_OBJECT

public:
    explicit graphe(QWidget *parent = 0);
    ~graphe();

private:
    Ui::graphe *ui;
};

#endif // GRAPHE_H
