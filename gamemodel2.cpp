#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

#include<QMessageBox>
#include<QIcon>
#include "gamemodel2.h"


extern int gamelevel;

gamemodel2::gamemodel2():
    gameStatus2(PLAYING),
    gamelevel2(MEDIUM)
{

}
gamemodel2::~gamemodel2()
{
    if(gameMap2)
    {
        free(gameMap2);
        free(hintArray2);
        gameMap2 = NULL;
    }
}



void gamemodel2::startgame2()
{
    gameMap2=new int[MAX_ROW * MAX_COL];

    for(int i=0;i<MAX_ROW * MAX_COL;i++)
        gameMap2[i]=0;

    hintArray2 = (int *)malloc(sizeof(int) * 4);
    memset(hintArray2, 0, 4);
    for (int i = 0; i < 4; i++)
        hintArray2[i] = -1;

    gameStatus2=PLAYING;

    int gamelevelnum = kMediumNum;
//    switch (gamelevel) {
//    case 1:
//        gamelevelnum = kBasicNum;
//        break;
//    case 2:
//        gamelevelnum = kMediumNum;
//        break;
//    case 3:
//        gamelevelnum = kHardNum;
//    default:
//        break;
//    }

    int iconID = 0;
    for(int i=0;i<gamelevelnum;i+=2)
    {
        //每次填充连着的两个，图片用尽了就循环
        gameMap2[i]=iconID%MAX_ICON+1;
        gameMap2[i+1]=iconID%MAX_ICON+1;
        iconID++;
    }

    //打乱方块
    srand((unsigned)time(0));
    for(int i=0;i<MAX_COL*MAX_ROW;i++)
    {
        int randomID = rand()%(MAX_COL*MAX_ROW);
        std::swap(gameMap2[i],gameMap2[randomID]);
    }

    // 初始化判断模式
    isFrozenMode2 = false;

    //初始化绘制点
    paintPoints2.clear();
}

bool gamemodel2::linkTwoTiles2(int srcX, int srcY, int dstX,int dstY)
{
    // 成功连接就返回true否则false用于GUI里面判断
    if(isCanLink2(srcX, srcY, dstX, dstY))
    {
        // 值重置
        gameMap2[MAX_COL * srcY + srcX] = 0;
        gameMap2[MAX_COL * dstY + dstX] = 0;
        return true;
    }

    QMessageBox message(QMessageBox::NoIcon, "Warning", "Can`t be linked");
    message.setWindowIcon(QPixmap(":/images/image/icon.png"));
    message.setIconPixmap(QPixmap(":/images/image/yuanshi.png"));
    message.exec();
//    QMessageBox::information(NULL,"Warning", "Can`t be linked");

    return false;
}

bool gamemodel2::isFrozen2()
{
    if(gameStatus2 == WIN)
        return false;

    else{
    // 暴力法，所有方块两两判断是否可以连接
    // 每次消除后做一次判断
    // 其实在这个过程中记录提示

    for (int i = 0; i < MAX_ROW * MAX_COL - 1; i++)
        for( int j = i + 1; j < MAX_ROW * MAX_COL; j++)
        {
            int srcX = i % MAX_COL;
            int srcY = i / MAX_COL;
            int dstX = j % MAX_COL;
            int dstY = j / MAX_COL;

            // 只要能找到可以连接的就不为僵局
            isFrozenMode2 = true;
            if (isCanLink2(srcX, srcY, dstX, dstY))
            {
                // 记录第一个可以连接的hint
                hintArray2[0] = srcX;
                hintArray2[1] = srcY;
                hintArray2[2] = dstX;
                hintArray2[3] = dstY;

                isFrozenMode2 = false;

                return false;
            }
        }
    isFrozenMode2 = false;

    return true;
    }
}

bool gamemodel2::isWin2()
{
    for (int i = 0; i < MAX_ROW * MAX_COL; i++)
    {
        if (gameMap2[i])
            return false;
    }
    gameStatus2 = WIN;
    return true;
}

bool gamemodel2::isCanLink2(int srcX, int srcY, int dstX, int dstY)
{
    // 首先判断点击的两个方块不是同一个不是空，且方块相同
    // 判断方块是否可以连，可用于实际的连接消除和提示消除
    // x表示横向索引，y表示纵向索引，从0开始
    // 分3种情况往下找，每一种都可以用前面简单情况组合找到一种情况可以连通就返回true，并选用这种连接情况

    if (gameMap2[srcY * MAX_COL + srcX] == 0 || gameMap2[dstY * MAX_COL + dstX] == 0)
        return false;

    if (srcX == dstX && srcY == dstY)
        return false;

    if(gameMap2[MAX_COL * srcY + srcX] != gameMap2[MAX_COL * dstY + dstX])
        return false;

    // 情况1：横向或者竖向可以直线连通
    if (canLinkDirectly2(srcX, srcY, dstX, dstY))
        return true;

    // 情况2：一次拐弯可以连通
    if (canLinkWithOneCorner2(srcX, srcY, dstX, dstY))
        return true;

    // 情况3：两次拐弯可以连通
    if (canLinkWithTwoCorner2(srcX, srcY, dstX, dstY))
        return true;


    return false;
}

bool gamemodel2::canLinkDirectly2(int srcX, int srcY, int dstX, int dstY)
{
    // 竖线
    if (srcX == dstX)
    {
        if (srcY > dstY)
            std::swap(srcY, dstY);
        for (int y = srcY + 1; y < dstY; y++)
            if (gameMap2[MAX_COL * y + srcX])
                return false;

        if (!isFrozenMode2) // 这里有坑，注意了
        {
            // 记录点和路线
            PaintPoint p1(srcX, srcY), p2(dstX, dstY);
            paintPoints2.clear();
            paintPoints2.push_back(p1);
            paintPoints2.push_back(p2);
        }

        return true;
    }

    // 横线
    if (srcY == dstY)
    {
        if (srcX > dstX)
            std::swap(srcX, dstX);
        for (int x = srcX + 1; x < dstX; x++)
            if (gameMap2[MAX_COL * srcY + x])
                return false;

        if (!isFrozenMode2)
        {
            PaintPoint p1(srcX, srcY), p2(dstX, dstY);
            paintPoints2.clear();
            paintPoints2.push_back(p1);
            paintPoints2.push_back(p2);
        }

        return true;
    }

    return false;
}

bool gamemodel2::canLinkWithOneCorner2(int srcX, int srcY, int dstX, int dstY)
{
    if (srcX > dstX)
    {
        // 统一化，方便后续处理
        std::swap(srcX, dstX);
        std::swap(srcY, dstY);
    }

    // 先确定拐点，再确定直连线路,2种情况，4个点，每种情况逐个试，所以多个if顺序执行
    if (dstY > srcY)
    {

        if (gameMap2[srcY * MAX_COL + dstX] == 0)
        {
            // 右上角
            if (canLinkDirectly2(srcX, srcY, dstX, srcY) && canLinkDirectly2(dstX, srcY, dstX, dstY))
            {
                // 只有连接模式才记录点
                if (!isFrozenMode2)
                {
                    PaintPoint p1(srcX, srcY), p2(dstX, srcY), p3(dstX, dstY);
                    paintPoints2.clear();
                    paintPoints2.push_back(p1);
                    paintPoints2.push_back(p2);
                    paintPoints2.push_back(p3);
                }

                return true;
            }

        }
        if (gameMap2[dstY * MAX_COL + srcX] == 0)
        {
            // 左下角
            if (canLinkDirectly2(srcX, srcY, srcX, dstY) && canLinkDirectly2(srcX, dstY, dstX, dstY))
            {
                if (!isFrozenMode2)
                {
                    PaintPoint p1(srcX, srcY), p2(srcX, dstY), p3(dstX, dstY);
                    paintPoints2.clear();
                    paintPoints2.push_back(p1);
                    paintPoints2.push_back(p2);
                    paintPoints2.push_back(p3);
                }

                return true;
            }

        }
    }
    else
    {
        if (gameMap2[dstY * MAX_COL + srcX] == 0)
        {
            // 左上角
            if (canLinkDirectly2(srcX, srcY, srcX, dstY) && canLinkDirectly2(srcX, dstY, dstX, dstY))
            {
                if (!isFrozenMode2)
                {
                    PaintPoint p1(srcX, srcY), p2(srcX, dstY), p3(dstX, dstY);
                    paintPoints2.clear();
                    paintPoints2.push_back(p1);
                    paintPoints2.push_back(p2);
                    paintPoints2.push_back(p3);
                }

                return true;
            }

        }
        if (gameMap2[srcY * MAX_COL + dstX] == 0)
        {
            // 右下角
            if (canLinkDirectly2(srcX, srcY, dstX, srcY) && canLinkDirectly2(dstX, srcY, dstX, dstY))
            {
                if (!isFrozenMode2)
                {
                    PaintPoint p1(srcX, srcY), p2(dstX, srcY), p3(dstX, dstY);
                    paintPoints2.clear();
                    paintPoints2.push_back(p1);
                    paintPoints2.push_back(p2);
                    paintPoints2.push_back(p3);
                }

                return true;
            }

        }
    }

    return false;
}

bool gamemodel2::canLinkWithTwoCorner2(int srcX, int srcY, int dstX, int dstY)
{
    if (srcX > dstX)
    {
        // 统一化，方便后续处理
        std::swap(srcX, dstX);
        std::swap(srcY, dstY);
    }

    // 两种情况，横向垂线和竖向垂线，以src点作为基准遍历，双折线由直线和一个拐点的折线构成
    // 常规情况
    for (int y = 0; y < MAX_ROW; y++)
    {
        if (y != srcY && y != dstY)
        {
            if (gameMap2[y * MAX_COL + srcX] == 0
                    && canLinkDirectly2(srcX, srcY, srcX, y)
                    && canLinkWithOneCorner2(srcX, y, dstX, dstY))
            {
                if (!isFrozenMode2)
                {
                    PaintPoint p1(srcX, srcY), p2(srcX, y), p3(dstX, y), p4(dstX, dstY);
                    paintPoints2.clear();
                    paintPoints2.push_back(p1);
                    paintPoints2.push_back(p2);
                    paintPoints2.push_back(p3);
                    paintPoints2.push_back(p4);
                }

                return true;
            }

        }
    }

    for (int x = 0; x < MAX_COL; x++)
    {
        if (x != srcX && x != dstX)
        {
            if (gameMap2[srcY * MAX_COL + x] == 0
                    && canLinkDirectly2(srcX, srcY, x, srcY)
                    && canLinkWithOneCorner2(x, srcY, dstX, dstY))
            {
                if (!isFrozenMode2)
                {
                    PaintPoint p1(srcX, srcY), p2(x, srcY), p3(x, dstY), p4(dstX, dstY);
                    paintPoints2.clear();
                    paintPoints2.push_back(p1);
                    paintPoints2.push_back(p2);
                    paintPoints2.push_back(p3);
                    paintPoints2.push_back(p4);

                }
                return true;
            }

        }
    }

    // 边缘情况，从外边缘连接，注意方块不一定在边缘,（分开写便于记录路径)
    if ((srcX == 0 || gameMap2[srcY * MAX_COL + 0] == 0 && canLinkDirectly2(srcX, srcY, 0, srcY))
            && (dstX == 0 || gameMap2[dstY * MAX_COL + 0] == 0 && canLinkDirectly2(0, dstY, dstX, dstY)))
    {
        // 左
        if (!isFrozenMode2)
        {
            PaintPoint p1(srcX, srcY), p2(-1, srcY), p3(-1, dstY), p4(dstX, dstY);
            paintPoints2.clear();
            paintPoints2.push_back(p1);
            paintPoints2.push_back(p2);
            paintPoints2.push_back(p3);
            paintPoints2.push_back(p4);

        }

        return true;
    }

    if ((srcX == MAX_COL - 1 || gameMap2[srcY * MAX_COL + MAX_COL - 1] == 0 && canLinkDirectly2(srcX, srcY, MAX_COL - 1, srcY))
            && (dstX == MAX_COL - 1 || gameMap2[dstY * MAX_COL + MAX_COL - 1] == 0 && canLinkDirectly2(MAX_COL - 1, dstY, dstX, dstY)))
    {
        // 右
        if (!isFrozenMode2)
        {
            PaintPoint p1(srcX, srcY), p2(MAX_COL, srcY), p3(MAX_COL, dstY), p4(dstX, dstY);
            paintPoints2.clear();
            paintPoints2.push_back(p1);
            paintPoints2.push_back(p2);
            paintPoints2.push_back(p3);
            paintPoints2.push_back(p4);

        }
        return true;
    }
    if ((srcY == 0 || gameMap2[srcX] == 0 && canLinkDirectly2(srcX, srcY, srcX, 0))
            && (dstY == 0 || gameMap2[dstX] == 0 && canLinkDirectly2(dstX, 0, dstX, dstY)))
    {
        // 上
        if (!isFrozenMode2)
        {
            PaintPoint p1(srcX, srcY), p2(srcX, -1), p3(dstX, -1), p4(dstX, dstY);
            paintPoints2.clear();
            paintPoints2.push_back(p1);
            paintPoints2.push_back(p2);
            paintPoints2.push_back(p3);
            paintPoints2.push_back(p4);

        }
        return true;
    }
    if ((srcY == MAX_ROW - 1 || gameMap2[(MAX_ROW - 1) * MAX_COL + srcX] == 0 && canLinkDirectly2(srcX, srcY, srcX, MAX_ROW - 1))
            && (dstY == MAX_ROW - 1 || gameMap2[(MAX_ROW - 1) * MAX_COL + dstX] == 0 && canLinkDirectly2(dstX, MAX_ROW - 1, dstX, dstY)))
    {
        // 下
        if (!isFrozenMode2)
        {
            PaintPoint p1(srcX, srcY), p2(srcX, MAX_ROW), p3(dstX, MAX_ROW), p4(dstX, dstY);
            paintPoints2.clear();
            paintPoints2.push_back(p1);
            paintPoints2.push_back(p2);
            paintPoints2.push_back(p3);
            paintPoints2.push_back(p4);

        }
        return true;
    }

    return false;
}

int *gamemodel2::getHint2()
{
    return hintArray2;
}

int *gamemodel2::getGameMap2()
{

    return gameMap2;
}

