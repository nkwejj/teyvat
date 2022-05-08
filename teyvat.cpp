//#include "mainwindow.h"
#include"teyvat.h"
#include "ui_teyvat.h"
#include <QDebug>
#include <QAction>
#include <QMessageBox>
#include <QPainter>
#include <QLine>

#include"gamemodel.h"

//const int kIconSize = 36;//图标大小
//const int kTopMargin = 70;//上边缘
//const int kLeftMargin = 50;//左边缘

//const QString kIconReleasedStyle = "";  //button被释放时
//const QString kIconClickedStyle = "background-color: rgba(255, 255, 12, 161)"; //button被点击时


//const int kGameTimeTotal = 5 * 60 * 1000; // 总时间
//const int kGameTimerInterval = 300;
//const int kLinkTimerDelay = 700;//连接两个图标的时间延迟

//游戏主界面
Teyvat::Teyvat(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Teyvat),
    preIcon(NULL),
    curIcon(NULL)
{
    ui->setupUi(this);
    ui->centralWidget->installEventFilter(this);

    QIcon icon = QIcon(":/images/image/icon.png");

    this->setWindowTitle("Genshin");
    this->setWindowIcon(icon);

    //设置背景图片
    QPixmap pixmap = QPixmap(":/images/image/background.png").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);


    //初始化游戏
    initGame();
}

Teyvat::~Teyvat()
{
    if(game)
        delete game;

    delete ui;
}

bool Teyvat::eventFilter(QObject *watched, QEvent *event){
    //重绘时会调用，可以手动调用
    if(event->type()==QEvent::Paint)
    {
        QPainter painter(ui->centralWidget);
        QPen pen;
        QColor color(rand()%256,rand()%256,rand()%256);
        pen.setColor(color);
        pen.setWidth(5);
        painter.setPen(pen);

        QString str;
        for(int i=0;i<game->paintPoints.size();i++)
        {
            PaintPoint p=game->paintPoints[i];
            str += "x:" + QString::number(p.x) + "y+" + QString::number(p.y) + "->";
        }

        for(int i=0;i<int(game->paintPoints.size())-1;i++)
        {
            PaintPoint p1 = game->paintPoints[i];
            PaintPoint p2 = game->paintPoints[i+1];

            //拿到各button的坐标
            QPoint btn_pos1;
            QPoint btn_pos2;

            //p1
            if(p1.x == -1)
            {
                btn_pos1 = imageButton[p1.y*MAX_COL + 0]->pos();
                btn_pos1 = QPoint(btn_pos1.x() - kIconSize, btn_pos1.y());
            }
            else if (p1.x == MAX_COL)
            {
                btn_pos1 = imageButton[p1.y * MAX_COL + MAX_COL - 1]->pos();
                btn_pos1 = QPoint(btn_pos1.x() + kIconSize, btn_pos1.y());
            }
            else if (p1.y == -1)
            {
                btn_pos1 = imageButton[0 + p1.x]->pos();
                btn_pos1 = QPoint(btn_pos1.x(), btn_pos1.y() - kIconSize);
            }
            else if (p1.y == MAX_ROW)
            {
                btn_pos1 = imageButton[(MAX_ROW - 1) * MAX_COL + p1.x]->pos();
                btn_pos1 = QPoint(btn_pos1.x(), btn_pos1.y() + kIconSize);
            }
            else
                btn_pos1 = imageButton[p1.y * MAX_COL + p1.x]->pos();

            //p2
            if (p2.x == -1)
            {
                btn_pos2 = imageButton[p2.y * MAX_COL + 0]->pos();
                btn_pos2 = QPoint(btn_pos2.x() - kIconSize, btn_pos2.y());
            }
            else if (p2.x == MAX_COL)
            {
                btn_pos2 = imageButton[p2.y * MAX_COL + MAX_COL - 1]->pos();
                btn_pos2 = QPoint(btn_pos2.x() + kIconSize, btn_pos2.y());
            }
            else if (p2.y == -1)
            {
                btn_pos2 = imageButton[0 + p2.x]->pos();
                btn_pos2 = QPoint(btn_pos2.x(), btn_pos2.y() - kIconSize);
            }
            else if (p2.y == MAX_ROW)
            {
                btn_pos2 = imageButton[(MAX_ROW - 1) * MAX_COL + p2.x]->pos();
                btn_pos2 = QPoint(btn_pos2.x(), btn_pos2.y() + kIconSize);
            }
            else
                btn_pos2 = imageButton[p2.y * MAX_COL + p2.x]->pos();


            // 中心点
            QPoint pos1(btn_pos1.x() + kIconSize / 2, btn_pos1.y() + kIconSize / 2);
            QPoint pos2(btn_pos2.x() + kIconSize / 2, btn_pos2.y() + kIconSize / 2);

            painter.drawLine(pos1, pos2);

        }
        return true;
    }
    else
        return QMainWindow::eventFilter(watched, event);
}

void Teyvat::onIconButtonPressed()
{
    // 如果当前有方块在连接，不能点击方块


    // 记录当前点击的icon
    curIcon = dynamic_cast<IconButton *>(sender());

    if(!preIcon)
    {

        // 如果单击一个icon
        curIcon->setStyleSheet(kIconClickedStyle);
        preIcon = curIcon;
    }
    else
    {
        if(curIcon != preIcon)
        {
            // 如果不是同一个button就都标记,尝试连接
            curIcon->setStyleSheet(kIconClickedStyle);
            if(game->linkTwoTiles(preIcon->xID, preIcon->yID, curIcon->xID, curIcon->yID))
            {
                // 锁住当前状态
                isLinking = true;


                // 重绘
                update();

                // 延迟后实现连接效果
                QTimer::singleShot(kLinkTimerDelay, this, SLOT(handleLinkEffect()));

                // 检查是否胜利
                if (game->isWin())
                {
                    battlebgm->stop();
//                    QMessageBox::information(this, "great", "you win");
                    QMessageBox message1(QMessageBox::NoIcon, "You win!", "\n\n原石++");
                    message1.setWindowIcon(QPixmap(":/images/image/icon.png"));
                    message1.setIconPixmap(QPixmap(":/images/image/yuanshi.png"));
                    message1.exec();
                    videoplay1();
                    timer1 = new QTimer;
                    timer1->setInterval(10);
                    timer1->start();
                    connect(timer1,SIGNAL(timeout()),this,SLOT(videofnsh1()));
                 }

                // 每次检查一下是否僵局
                if (game->isFrozen())
                {
                    battlebgm->stop();
                    QMessageBox::information(this, "You lose!", "dead game");
                }



                int *hints = game->getHint();
            }
            else
            {

                // 消除失败，恢复
                preIcon->setStyleSheet(kIconReleasedStyle);
                curIcon->setStyleSheet(kIconReleasedStyle);

                // 指针置空，用于下次点击判断
                preIcon = NULL;
                curIcon = NULL;
            }
        }
        else if(curIcon == preIcon)
        {

            preIcon->setStyleSheet(kIconReleasedStyle);
            curIcon->setStyleSheet(kIconReleasedStyle);
            preIcon = NULL;
            curIcon = NULL;
        }
    }
}

void Teyvat::handleLinkEffect()
{
    // 消除成功，隐藏掉，并析构
    game->paintPoints.clear();
    preIcon->hide();
    curIcon->hide();

    preIcon = NULL;
    curIcon = NULL;

    // 重绘
    update();

    // 恢复状态
    isLinking = false;
}

void Teyvat::initGame()
{
    //启动游戏

    game = new gamemodel;
    game->startgame();

    battlebgm = new QMediaPlayer;
    battlebgmlist = new QMediaPlaylist;
    battlebgmlist->addMedia(QUrl("qrc:/res/media/battlebg.mp3"));
    battlebgmlist->addMedia(QUrl("qrc:/res/media/battlebg.mp3"));
    battlebgmlist->addMedia(QUrl("qrc:/res/media/battlebg.mp3"));
    battlebgm->setPlaylist(battlebgmlist);
    battlebgm->setVolume(35);
    battlebgm->play();

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
            connect(imageButton[i],SIGNAL(pressed()),this,SLOT(onIconButtonPressed()));
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

void Teyvat::videoplay1()
{
    //视频播放
    widget1 = new QWidget;
    layout1 = new QVBoxLayout;
    video1 = new QMediaPlayer;
    videowidget1 = new QVideoWidget;

    videowidget1->setAspectRatioMode(Qt::IgnoreAspectRatio);
    videowidget1->setFullScreen(true);

    layout1->addWidget(videowidget1);
    widget1->setLayout(layout1);

    video1->setMedia(QUrl("qrc:/res/media/gold.mp4"));
    video1->setVolume(35);

    video1->setVideoOutput(videowidget1);

    widget1->showFullScreen();
    video1->play();
}

void Teyvat::videofnsh1()
{
    status1 = video1->mediaStatus();
    if(status1==QMediaPlayer::EndOfMedia)
    {
        timer1->stop();
        widget1->close();
    }
}
