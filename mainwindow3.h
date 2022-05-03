#ifndef MainWindow3_H
#define MainWindow3_H

#include <QMainWindow>
#include<QToolButton>
#include <QWidget>
#include <QTimer>
#include<QMediaPlayer>
#include<QVideoWidget>
#include<QMediaPlaylist>
#include<QVBoxLayout>

#include"gamemodel3.h"
#include"constcl.h"


namespace Ui {
class MainWindow3;
}

//// 继承自button，存储坐标值
//struct IconButton:QToolButton{
//public:
//    IconButton(QWidget*parent=Q_NULLPTR):
//        QToolButton(parent),xID(-1),yID(-1){}
//    int xID;//x坐标
//    int yID;//y坐标
//};

class MainWindow3 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow3(QWidget *parent = 0);
    ~MainWindow3();

    bool eventFilter3(QObject *watched, QEvent *event);//事件过滤(显示连线)

private:
    Ui::MainWindow3 *ui;
    gamemodel3 *game3;//游戏模型
    IconButton *imageButton3[MAX_ROW*MAX_COL];//图片button数组
    QTimer *gameTimer3;//游戏计时器
    IconButton *preIcon3,*curIcon3;//记录点击的icon
    bool isLinking3;//维持一个连接状态的标志

    void initGame3();//初始化游戏

    QMediaPlayer *battlebgm3;

protected:
    QVideoWidget *videowidget3;
    QMediaPlayer *video3;
    QWidget *widget3;
    QVBoxLayout *layout3;
    QTimer *timer3;
    QMediaPlayer::MediaStatus status3;
    void videoplay3();

private slots:
    void onIconButtonPressed3();//icon点击到响应
    void handleLinkEffect3();//实现连接效果
    void videofnsh3();//游戏胜利播放动画

};

#endif // MainWindow3_H
