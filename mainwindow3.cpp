#include "MainWindow3.h"
#include "ui_MainWindow3.h"
#include <QDebug>
#include <QAction>
#include <QMessageBox>
#include <QPainter>
#include <QLine>

#include"gamemodel3.h"

//const int kIconSize = 36;//图标大小
//const int kTopMargin = 70;//上边缘
//const int kLeftMargin = 50;//左边缘

//const QString kIconReleasedStyle = "";  //button被释放时
//const QString kIconClickedStyle = "background-color: rgba(255, 255, 12, 161)"; //button被点击时


//const int kGameTimeTotal = 5 * 60 * 1000; // 总时间
//const int kGameTimerInterval = 300;
//const int kLinkTimerDelay = 700;//连接两个图标的时间延迟

//游戏主界面
MainWindow3::MainWindow3(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow3),
    preIcon3(NULL),
    curIcon3(NULL)
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
    initGame3();
}

MainWindow3::~MainWindow3()
{
    if(game3)
        delete game3;

    delete ui;
}

bool MainWindow3::eventFilter3(QObject *watched, QEvent *event){
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
        for(int i=0;i<game3->paintPoints3.size();i++)
        {
            PaintPoint p=game3->paintPoints3[i];
            str += "x:" + QString::number(p.x) + "y+" + QString::number(p.y) + "->";
        }

        for(int i=0;i<int(game3->paintPoints3.size())-1;i++)
        {
            PaintPoint p1 = game3->paintPoints3[i];
            PaintPoint p2 = game3->paintPoints3[i+1];

            //拿到各button的坐标
            QPoint btn_pos1;
            QPoint btn_pos2;

            //p1
            if(p1.x == -1)
            {
                btn_pos1 = imageButton3[p1.y*MAX_COL + 0]->pos();
                btn_pos1 = QPoint(btn_pos1.x() - kIconSize, btn_pos1.y());
            }
            else if (p1.x == MAX_COL)
            {
                btn_pos1 = imageButton3[p1.y * MAX_COL + MAX_COL - 1]->pos();
                btn_pos1 = QPoint(btn_pos1.x() + kIconSize, btn_pos1.y());
            }
            else if (p1.y == -1)
            {
                btn_pos1 = imageButton3[0 + p1.x]->pos();
                btn_pos1 = QPoint(btn_pos1.x(), btn_pos1.y() - kIconSize);
            }
            else if (p1.y == MAX_ROW)
            {
                btn_pos1 = imageButton3[(MAX_ROW - 1) * MAX_COL + p1.x]->pos();
                btn_pos1 = QPoint(btn_pos1.x(), btn_pos1.y() + kIconSize);
            }
            else
                btn_pos1 = imageButton3[p1.y * MAX_COL + p1.x]->pos();

            //p2
            if (p2.x == -1)
            {
                btn_pos2 = imageButton3[p2.y * MAX_COL + 0]->pos();
                btn_pos2 = QPoint(btn_pos2.x() - kIconSize, btn_pos2.y());
            }
            else if (p2.x == MAX_COL)
            {
                btn_pos2 = imageButton3[p2.y * MAX_COL + MAX_COL - 1]->pos();
                btn_pos2 = QPoint(btn_pos2.x() + kIconSize, btn_pos2.y());
            }
            else if (p2.y == -1)
            {
                btn_pos2 = imageButton3[0 + p2.x]->pos();
                btn_pos2 = QPoint(btn_pos2.x(), btn_pos2.y() - kIconSize);
            }
            else if (p2.y == MAX_ROW)
            {
                btn_pos2 = imageButton3[(MAX_ROW - 1) * MAX_COL + p2.x]->pos();
                btn_pos2 = QPoint(btn_pos2.x(), btn_pos2.y() + kIconSize);
            }
            else
                btn_pos2 = imageButton3[p2.y * MAX_COL + p2.x]->pos();


            // 中心点
            QPoint pos1(btn_pos1.x() + kIconSize / 2, btn_pos1.y() + kIconSize / 2);
            QPoint pos2(btn_pos2.x() + kIconSize / 2, btn_pos2.y() + kIconSize / 2);

            painter.drawLine(pos1, pos2);

        }
        return true;
    }
    else
        return MainWindow3::eventFilter(watched, event);
}

void MainWindow3::onIconButtonPressed3()
{
    // 如果当前有方块在连接，不能点击方块


    // 记录当前点击的icon
    curIcon3 = dynamic_cast<IconButton *>(sender());

    if(!preIcon3)
    {

        // 如果单击一个icon
        curIcon3->setStyleSheet(kIconClickedStyle);
        preIcon3 = curIcon3;
    }
    else
    {
        if(curIcon3 != preIcon3)
        {
            // 如果不是同一个button就都标记,尝试连接
            curIcon3->setStyleSheet(kIconClickedStyle);
            if(game3->linkTwoTiles3(preIcon3->xID, preIcon3->yID, curIcon3->xID, curIcon3->yID))
            {
                // 锁住当前状态
                isLinking3 = true;


                // 重绘
                update();

                // 延迟后实现连接效果
                QTimer::singleShot(kLinkTimerDelay, this, SLOT(handleLinkEffect3()));

                // 检查是否胜利
                if (game3->isWin3())
                {
                    battlebgm3->stop();
//                    QMessageBox::information(this, "great", "you win");
                    QMessageBox message3(QMessageBox::NoIcon, "You win!", "\n\n原石++");
                    message3.setWindowIcon(QPixmap(":/images/image/icon.png"));
                    message3.setIconPixmap(QPixmap(":/images/image/yuanshi.png"));
                    message3.exec();
                    videoplay3();
                    timer3 = new QTimer;
                    timer3->setInterval(10);
                    timer3->start();
                    connect(timer3,SIGNAL(timeout()),this,SLOT(videofnsh3()));
                 }

                // 每次检查一下是否僵局
                if (game3->isFrozen3())
                {
                    battlebgm3->stop();
                    QMessageBox::information(this, "You lose!", "dead game");
                }

                int *hints = game3->getHint3();
            }
            else
            {

                // 消除失败，恢复
                preIcon3->setStyleSheet(kIconReleasedStyle);
                curIcon3->setStyleSheet(kIconReleasedStyle);

                // 指针置空，用于下次点击判断
                preIcon3 = NULL;
                curIcon3 = NULL;
            }
        }
        else if(curIcon3== preIcon3)
        {

            preIcon3->setStyleSheet(kIconReleasedStyle);
            curIcon3->setStyleSheet(kIconReleasedStyle);
            preIcon3 = NULL;
            curIcon3 = NULL;
        }
    }
}

void MainWindow3::handleLinkEffect3()
{
    // 消除成功，隐藏掉，并析构
    game3->paintPoints3.clear();
    preIcon3->hide();
    curIcon3->hide();

    preIcon3 = NULL;
    curIcon3 = NULL;

    // 重绘
    update();

    // 恢复状态
    isLinking3 = false;
}

void MainWindow3::initGame3()
{
    //启动游戏

    game3 = new gamemodel3;
    game3->startgame3();

    battlebgm3 = new QMediaPlayer;
    battlebgm3->setMedia(QUrl("qrc:/res/media/battlebg.mp3"));
    battlebgm3->setVolume(35);
    battlebgm3->play();

    //添加button
    for(int i=0;i<MAX_ROW*MAX_COL;i++)
    {
        imageButton3[i]=new IconButton(this);
        imageButton3[i]->setGeometry(kLeftMargin + (i % MAX_COL) * kIconSize, kTopMargin + (i / MAX_COL) * kIconSize, kIconSize, kIconSize);
        //设置索引
        imageButton3[i]->xID=i%MAX_COL;
        imageButton3[i]->yID=i/MAX_COL;

        imageButton3[i]->show();

        if(game3->getGameMap3()[i])
        {
            //有方块就设置图片
            QPixmap iconPix;
            QString fileString;
            fileString.sprintf(":/res/image/%d.png",game3->getGameMap3()[i]);
            iconPix.load(fileString);
            QIcon icon(iconPix);
            imageButton3[i]->setIcon(icon);
            imageButton3[i]->setIconSize(QSize(kIconSize,kIconSize));

            //添加按下的信号槽
            connect(imageButton3[i],SIGNAL(pressed()),this,SLOT(onIconButtonPressed3()));
        }
        else
            imageButton3[i]->hide();
    }

    //游戏计时器
    gameTimer3=new QTimer(this);
    connect(gameTimer3,SIGNAL(timeout()),this,SLOT(gameTimerEvent()));
    gameTimer3->start(kGameTimerInterval);

    //连接状态值
    isLinking3=false;

}

void MainWindow3::videoplay3()
{
    //视频播放
    widget3 = new QWidget;
    layout3 = new QVBoxLayout;
    video3 = new QMediaPlayer;
    videowidget3 = new QVideoWidget;

    videowidget3->setAspectRatioMode(Qt::IgnoreAspectRatio);
    videowidget3->setFullScreen(true);

    layout3->addWidget(videowidget3);
    widget3->setLayout(layout3);

    video3->setMedia(QUrl("qrc:/res/media/gold.mp4"));
    video3->setVolume(35);

    video3->setVideoOutput(videowidget3);

    widget3->showFullScreen();
    video3->play();
}

void MainWindow3::videofnsh3()
{
    status3 = video3->mediaStatus();
    if(status3==QMediaPlayer::EndOfMedia)
    {
        timer3->stop();
        widget3->close();
    }
}
