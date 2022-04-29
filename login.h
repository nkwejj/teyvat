#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>

#include <QGraphicsPixmapItem>//图形元素
#include <QGraphicsView>//视图
#include <QGraphicsScene>//场景

#include"levelchoose.h"
//#include"mainwindow.h"

class login:public QMainWindow
{
public:
    login(QWidget *parent=0);
    void start();
    static const int ScreenWidth = 600;
    static const int ScreenHeight = 400;
//    MainWindow mw;
    LevelChoose LC;

protected:
    QGraphicsView mGameView;
    QGraphicsScene mGameBeginScence;
    QGraphicsPixmapItem Instruction;

};

#endif // LOGIN_H
