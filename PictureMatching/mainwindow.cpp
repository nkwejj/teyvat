#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QAction>
#include <QMessageBox>
#include <QPainter>
#include <QLine>

const int kIconSize = 36;//图标大小
const int kTopMargin = 70;//上边缘
const int kLeftMargin = 50;//左边缘

const QString kIconReleasedStyle = "";
const QString kIconClickedStyle = "background-color: rgba(255, 255, 12, 161)";


const int kGameTimeTotal = 5 * 60 * 1000; // 总时间
const int kGameTimerInterval = 300;
const int kLinkTimerDelay = 700;//连接两个图标的时间延迟

//游戏主界面
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    preIcon(NULL),
    curIcon(NULL)
{
    ui->setupUi(this);
    ui->centralWidget->installEventFilter(this);

    //初始化游戏
    initGame();
}

MainWindow::~MainWindow()
{
    if(game)
        delete game;

    delete ui;
}

void MainWindow::initGame()
{
    //启动游戏

    game = new gamemodel;
    game->startgame();

    //添加button
    for(int i=0;i<MAX_ROW*MAX_COL;i++)
    {
        imageButton[i]=new IconButton(this);
        imageButton[i]->setGeometry(kLeftMargin + (i % MAX_COL) * kIconSize, kTopMargin + (i / MAX_COL) * kIconSize, kIconSize, kIconSize);
        //设置索引
        imageButton[i]->xID=i%MAX_COL;
        imageButton[i]->yID=i/MAX_COL;

        imageButton[i]->show();

        if(game->getGameMap()[i])
        {
            //有方块就设置图片
            QPixmap iconPix;
            QString fileString;
            fileString.sprintf(":/res/image/%d.png",game->getGameMap()[i]);
            iconPix.load(fileString);
            QIcon icon(iconPix);
            imageButton[i]->setIcon(icon);
            imageButton[i]->setIconSize(QSize(kIconSize,kIconSize));

            //添加按下的信号槽
            connect(imageButton[i],SIGNAL(pressed(),this,SLOT(onIconButtonPressed());
        }
        else
            imageButton[i]->hide();
    }

    //游戏计时器
    gameTimer=new QTimer(this);
    connect(gameTimer,SIGNAL(timeout()),this,SLOT(gameTimerEvent()));
    gameTimer->start(kGameTimerInterval);

    //连接状态值
    isLinking=false;

}



