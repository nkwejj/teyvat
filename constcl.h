#ifndef CONSTCL_H
#define CONSTCL_H

#include<QToolButton>

//最大行和列数
const int MAX_ROW=15;
const int MAX_COL=20;
//游戏可玩图片数量
const int MAX_ICON=25;
//游戏状态
enum GameStatus
{
    PLAYING,
    PAUSE,
    WIN,
    OVER
};
//方块数
const int kBasicNum=MAX_ROW*MAX_COL*0.3;
const int kMediumNum=MAX_ROW*MAX_COL*0.7;
const int kHardNum=MAX_ROW*MAX_COL;

enum GameLevel
{
    BASIC,
    MEDIUM,
    HARD
};

//用于绘制线段的连接点
struct PaintPoint
{
    PaintPoint(int _x, int _y) :
        x(_x), y (_y) {}
    int x;
    int y;
};








// 继承自button，存储坐标值
struct IconButton:QToolButton{
public:
    IconButton(QWidget*parent=Q_NULLPTR):
        QToolButton(parent),xID(-1),yID(-1){}
    int xID;//x坐标
    int yID;//y坐标
};





const int kIconSize = 36;//图标大小
const int kTopMargin = 70;//上边缘
const int kLeftMargin = 50;//左边缘

const QString kIconReleasedStyle = "";  //button被释放时
const QString kIconClickedStyle = "background-color: rgba(255, 255, 12, 161)"; //button被点击时


const int kGameTimeTotal = 5 * 60 * 1000; // 总时间
const int kGameTimerInterval = 300;
const int kLinkTimerDelay = 700;//连接两个图标的时间延迟






class constcl
{
public:
    constcl();

    static int gamelevelnum;
};

#endif // CONSTCL_H
