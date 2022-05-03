#ifndef TEYVAT_H
#define TEYVAT_H

#include <QMainWindow>

namespace Ui {
class Teyvat;
}

class Teyvat : public QMainWindow
{
    Q_OBJECT

public:
    explicit Teyvat(QWidget *parent = 0);
    ~Teyvat();

private slots:

private:
    Ui::Teyvat *ui;
};

#endif // TEYVAT_H
