#include "levelchoose.h"
#include "ui_levelchoose.h"


LevelChoose::LevelChoose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LevelChoose)
{
    ui->setupUi(this);

    this->setGeometry(QRect(300,150,600,400));
    QIcon icon = QIcon(":/images/image/icon.png");

    this->setWindowTitle("Genshin");
    this->setWindowIcon(icon);
}

LevelChoose::~LevelChoose()
{
    delete ui;
}

void LevelChoose::on_pushButton_clicked()
{
//    gameLevel = BASIC;
    this->hide();
    mw.show();
}

void LevelChoose::on_pushButton_2_clicked()
{
//    gameLevel = MEDIUM;
    this->hide();
    mw.show();
}

void LevelChoose::on_pushButton_3_clicked()
{
//    gameLevel = HARD;
    this->hide();
    mw.show();
}
