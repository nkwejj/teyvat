#ifndef GAMEMODEL2_H
#define GAMEMODEL2_H

#include <vector>

#include"constcl.h"


////最大行和列数
//const int MAX_ROW=15;
//const int MAX_COL=20;
////游戏可玩图片数量
//const int MAX_ICON=25;
////游戏状态
//enum GameStatus
//{
//    PLAYING,
//    PAUSE,
//    WIN,
//    OVER
//};
////方块数
//const int kBasicNum=MAX_ROW*MAX_COL*0.3;
//const int kMediumNum=MAX_ROW*MAX_COL*0.7;
//const int kHardNum=MAX_ROW*MAX_COL;

//enum GameLevel
//{
//    BASIC,
//    MEDIUM,
//    HARD
//};


////用于绘制线段的连接点
//struct PaintPoint
//{
//    PaintPoint(int _x, int _y) :
//        x(_x), y (_y) {}
//    int x;
//    int y;
//};



class gamemodel2
{
public:
    gamemodel2();
    ~gamemodel2();

    void startgame2();//开始游戏
    int *getGameMap2();//获得地图
    GameStatus checkGameStatus2();//判断获得游戏状态，是否输赢
    bool linkTwoTiles2(int srcX, int srcY, int dstX,int dstY);//连接起点和终点方块，连接是否成功
    bool isFrozen2();//判断是否已经成为了僵局
    bool isWin2();//检查游戏是否结束
    int *getHint2();//获得提示
    std::vector<PaintPoint>paintPoints2;//用于绘制的点

    GameStatus gameStatus2;//游戏状态
    GameLevel gamelevel2;//游戏难度
//    LevelChoose LC;

private:
    int *gameMap2;//游戏地图，存储方块，0表示消失，1-其他数字表示图片标号
    int *hintArray2;//游戏提示

    bool isCanLink2(int srcX, int srcY, int dstX, int dstY);

    bool canLinkDirectly2(int srcX, int srcY, int dstX, int dstY);
    bool canLinkWithOneCorner2(int srcX, int srcY, int dstX, int dstY);
    bool canLinkWithTwoCorner2(int srcX, int srcY, int dstX, int dstY);

    bool isFrozenMode2;//判断是否为僵局
};

#endif // GAMEMODEL2_H
