#ifndef GAMEMODEL3_H
#define GAMEMODEL3_H

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



class gamemodel3
{
public:
    gamemodel3();
    ~gamemodel3();

    void startgame3();//开始游戏
    int *getGameMap3();//获得地图
    GameStatus checkGameStatus3();//判断获得游戏状态，是否输赢
    bool linkTwoTiles3(int srcX, int srcY, int dstX,int dstY);//连接起点和终点方块，连接是否成功
    bool isFrozen3();//判断是否已经成为了僵局
    bool isWin3();//检查游戏是否结束
    int *getHint3();//获得提示
    std::vector<PaintPoint>paintPoints3;//用于绘制的点

    GameStatus gameStatus3;//游戏状态
    GameLevel gamelevel3;//游戏难度
//    LevelChoose LC;

private:
    int *gameMap3;//游戏地图，存储方块，0表示消失，1-其他数字表示图片标号
    int *hintArray3;//游戏提示

    bool isCanLink3(int srcX, int srcY, int dstX, int dstY);

    bool canLinkDirectly3(int srcX, int srcY, int dstX, int dstY);
    bool canLinkWithOneCorner3(int srcX, int srcY, int dstX, int dstY);
    bool canLinkWithTwoCorner3(int srcX, int srcY, int dstX, int dstY);

    bool isFrozenMode3;//判断是否为僵局
};

#endif // GAMEMODEL3_H
