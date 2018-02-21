#ifndef CHOIX_H
#define CHOIX_H

#include <QWidget>

namespace Ui {
class choix;
}

class choix : public QWidget
{
    Q_OBJECT

public:
    explicit choix(QWidget *parent = 0);
    ~choix();

private slots:
    void on_chute_clicked();

    void on_go_clicked();

private:
    Ui::choix *ui;
};

#endif // CHOIX_H
