#ifndef LEVELCHOOSE_H
#define LEVELCHOOSE_H

#include <QWidget>

#include <QGraphicsView>//视图
#include <QGraphicsScene>//场景
#include<QGraphicsPixmapItem>//图形元素

#include<QMediaPlayer>
#include<QVideoWidget>
#include<QMediaPlaylist>
#include<QVBoxLayout>
#include<QTimer>
//#include<QMediaPlaylist>

#include"mainwindow.h"
//#include"mainwindow2.h"
//#include"mainwindow3.h"


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
    MainWindow *mw;
//    MainWindow2 *mw2;
//    MainWindow3 *mw3;

    constcl con;



private:
    Ui::LevelChoose *ui;

protected:
    QGraphicsView mLCView;
    QGraphicsScene mLCScence;
    QGraphicsPixmapItem mLCPItem;

    QVideoWidget *videowidget;
    QMediaPlayer *video;
    QWidget *widget;
    QVBoxLayout *layout;
    QTimer *timer;
    QMediaPlayer::MediaStatus status;
//    QMediaPlaylist *playlist;

    void videoplay();
    void changeto1();
    void changeto2();
    void changeto3();

private slots:
    void getstatus1();
    void getstatus2();
    void getstatus3();

};

#endif // LEVELCHOOSE_H
