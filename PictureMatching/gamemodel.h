#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <vector>

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
const int kBasicNum=MAX_ROW*MAX_COL;


enum GameLevel
{
    BASIC
};


//用于绘制线段的连接点
struct PaintPoint
{
    PaintPoint(int _x, int _y) :
        x(_x), y (_y) {}
    int x;
    int y;
};



class gamemodel
{
public:
    gamemodel();
    ~gamemodel();

    void startgame();//开始游戏
    int *getGameMap();//获得地图
    GameStatus checkGameStatus();//判断获得游戏状态，是否输赢
    bool lintTwoTiles(int srcX, int srcY, int dstX,int dstY);//连接起点和终点方块，连接是否成功
    bool isFrozen();//判断是否已经成为了僵局
    bool isWin();//检查游戏是否结束
    std::vector<PaintPoint>paintPoints;//用于绘制的点

    GameStatus gameStatus;//游戏状态

private:
    int *gameMap;//游戏地图，存储方块，0表示消失，1-其他数字表示图片标号

    bool isCanLink(int srcX, int srcY, int dstX, int dstY);

    bool canLinkDirectly(int srcX, int srcY, int dstX, int dstY);
    bool canLinkWithOneCorner(int srcX, int srcY, int dstX, int dstY);
    bool canLinkWithTwoCorner(int srcX, int srcY, int dstX, int dstY);

};

#endif // GAMEMODEL_H
