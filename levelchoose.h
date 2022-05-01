#ifndef LEVELCHOOSE_H
#define LEVELCHOOSE_H

#include <QWidget>
#include <QGraphicsView>//视图
#include <QGraphicsScene>//场景
#include<QGraphicsPixmapItem>//图形元素

#include"mainwindow.h"
#include"mainwindow2.h"
#include"mainwindow3.h"


namespace Ui {
class LevelChoose;
}

class LevelChoose : public QWidget
{
    Q_OBJECT

public:
    explicit LevelChoose(QWidget *parent = 0);
    ~LevelChoose();

    void LCinit();
    MainWindow mw;
    MainWindow2 mw2;
    MainWindow3 mw3;


private:
    Ui::LevelChoose *ui;

protected:
    QGraphicsView mLCView;
    QGraphicsScene mLCScence;
    QGraphicsPixmapItem mLCPItem;

};

#endif // LEVELCHOOSE_H
