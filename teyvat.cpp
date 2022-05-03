#include "teyvat.h"
#include "ui_teyvat.h"



Teyvat::Teyvat(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Teyvat)
{
    ui->setupUi(this);
}

Teyvat::~Teyvat()
{
    delete ui;
}


