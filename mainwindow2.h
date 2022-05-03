#ifndef MainWindow2_H
#define MainWindow2_H

#include <QMainWindow>
#include<QToolButton>
#include <QWidget>
#include <QTimer>
#include<QMediaPlayer>
#include<QVideoWidget>
#include<QMediaPlaylist>
#include<QVBoxLayout>

#include"gamemodel2.h"
#include"constcl.h"


namespace Ui {
class MainWindow2;
}

//// 继承自button，存储坐标值
//struct IconButton:QToolButton{
//public:
//    IconButton(QWidget*parent=Q_NULLPTR):
//        QToolButton(parent),xID(-1),yID(-1){}
//    int xID;//x坐标
//    int yID;//y坐标
//};

class MainWindow2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow2(QWidget *parent = 0);
    ~MainWindow2();

    bool eventFilter2(QObject *watched, QEvent *event);//事件过滤(显示连线)

private:
    Ui::MainWindow2 *ui;
    gamemodel2 *game2;//游戏模型
    IconButton *imageButton2[MAX_ROW*MAX_COL];//图片button数组
    QTimer *gameTimer2;//游戏计时器
    IconButton *preIcon2,*curIcon2;//记录点击的icon
    bool isLinking2;//维持一个连接状态的标志

    void initGame2();//初始化游戏

    QMediaPlayer *battlebgm2;

protected:
    QVideoWidget *videowidget2;
    QMediaPlayer *video2;
    QWidget *widget2;
    QVBoxLayout *layout2;
    QTimer *timer2;
    QMediaPlayer::MediaStatus status2;
    void videoplay2();

private slots:
    void onIconButtonPressed2();//icon点击到响应
    void handleLinkEffect2();//实现连接效果
    void videofnsh2();

};

#endif // MainWindow2_H
