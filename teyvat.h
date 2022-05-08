#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QToolButton>
#include <QWidget>
#include <QTimer>
#include<QMediaPlayer>
#include<QVideoWidget>
#include<QMediaPlaylist>
#include<QVBoxLayout>

#include"gamemodel.h"
#include"constcl.h"


namespace Ui {
class Teyvat;
}

//// 继承自button，存储坐标值
//struct IconButton:QToolButton{
//public:
//    IconButton(QWidget*parent=Q_NULLPTR):
//        QToolButton(parent),xID(-1),yID(-1){}
//    int xID;//x坐标
//    int yID;//y坐标
//};

class Teyvat : public QMainWindow
{
    Q_OBJECT

public:
    explicit Teyvat(QWidget *parent = 0);
    ~Teyvat();

    bool eventFilter(QObject *watched, QEvent *event);//事件过滤(显示连线)

private:
    Ui::Teyvat *ui;
    gamemodel *game;//游戏模型
    IconButton *imageButton[MAX_ROW*MAX_COL];//图片button数组
    QTimer *gameTimer;//游戏计时器
    IconButton *preIcon,*curIcon;//记录点击的icon
    bool isLinking;//维持一个连接状态的标志

    void initGame();//初始化游戏

    QMediaPlayer *battlebgm;

protected:
    QVideoWidget *videowidget1;
    QMediaPlayer *video1;
    QWidget *widget1;
    QVBoxLayout *layout1;
    QTimer *timer1;
    QMediaPlayer::MediaStatus status1;
    void videoplay1();

private slots:
    void onIconButtonPressed();//icon点击到响应
    void handleLinkEffect();//实现连接效果
    void videofnsh1();//游戏胜利播放动画

};

#endif // MAINWINDOW_H
