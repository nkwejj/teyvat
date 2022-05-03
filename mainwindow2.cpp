#include "MainWindow2.h"
#include "ui_MainWindow2.h"
#include <QDebug>
#include <QAction>
#include <QMessageBox>
#include <QPainter>
#include <QLine>

#include"gamemodel2.h"

//const int kIconSize = 36;//图标大小
//const int kTopMargin = 70;//上边缘
//const int kLeftMargin = 50;//左边缘

//const QString kIconReleasedStyle = "";  //button被释放时
//const QString kIconClickedStyle = "background-color: rgba(255, 255, 12, 161)"; //button被点击时


//const int kGameTimeTotal = 5 * 60 * 1000; // 总时间
//const int kGameTimerInterval = 300;
//const int kLinkTimerDelay = 700;//连接两个图标的时间延迟

//游戏主界面
MainWindow2::MainWindow2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow2),
    preIcon2(NULL),
    curIcon2(NULL)
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
    initGame2();
}

MainWindow2::~MainWindow2()
{
    if(game2)
        delete game2;

    delete ui;
}

bool MainWindow2::eventFilter2(QObject *watched, QEvent *event){
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
        for(int i=0;i<game2->paintPoints2.size();i++)
        {
            PaintPoint p=game2->paintPoints2[i];
            str += "x:" + QString::number(p.x) + "y+" + QString::number(p.y) + "->";
        }

        for(int i=0;i<int(game2->paintPoints2.size())-1;i++)
        {
            PaintPoint p1 = game2->paintPoints2[i];
            PaintPoint p2 = game2->paintPoints2[i+1];

            //拿到各button的坐标
            QPoint btn_pos1;
            QPoint btn_pos2;

            //p1
            if(p1.x == -1)
            {
                btn_pos1 = imageButton2[p1.y*MAX_COL + 0]->pos();
                btn_pos1 = QPoint(btn_pos1.x() - kIconSize, btn_pos1.y());
            }
            else if (p1.x == MAX_COL)
            {
                btn_pos1 = imageButton2[p1.y * MAX_COL + MAX_COL - 1]->pos();
                btn_pos1 = QPoint(btn_pos1.x() + kIconSize, btn_pos1.y());
            }
            else if (p1.y == -1)
            {
                btn_pos1 = imageButton2[0 + p1.x]->pos();
                btn_pos1 = QPoint(btn_pos1.x(), btn_pos1.y() - kIconSize);
            }
            else if (p1.y == MAX_ROW)
            {
                btn_pos1 = imageButton2[(MAX_ROW - 1) * MAX_COL + p1.x]->pos();
                btn_pos1 = QPoint(btn_pos1.x(), btn_pos1.y() + kIconSize);
            }
            else
                btn_pos1 = imageButton2[p1.y * MAX_COL + p1.x]->pos();

            //p2
            if (p2.x == -1)
            {
                btn_pos2 = imageButton2[p2.y * MAX_COL + 0]->pos();
                btn_pos2 = QPoint(btn_pos2.x() - kIconSize, btn_pos2.y());
            }
            else if (p2.x == MAX_COL)
            {
                btn_pos2 = imageButton2[p2.y * MAX_COL + MAX_COL - 1]->pos();
                btn_pos2 = QPoint(btn_pos2.x() + kIconSize, btn_pos2.y());
            }
            else if (p2.y == -1)
            {
                btn_pos2 = imageButton2[0 + p2.x]->pos();
                btn_pos2 = QPoint(btn_pos2.x(), btn_pos2.y() - kIconSize);
            }
            else if (p2.y == MAX_ROW)
            {
                btn_pos2 = imageButton2[(MAX_ROW - 1) * MAX_COL + p2.x]->pos();
                btn_pos2 = QPoint(btn_pos2.x(), btn_pos2.y() + kIconSize);
            }
            else
                btn_pos2 = imageButton2[p2.y * MAX_COL + p2.x]->pos();


            // 中心点
            QPoint pos1(btn_pos1.x() + kIconSize / 2, btn_pos1.y() + kIconSize / 2);
            QPoint pos2(btn_pos2.x() + kIconSize / 2, btn_pos2.y() + kIconSize / 2);

            painter.drawLine(pos1, pos2);

        }
        return true;
    }
    else
        return MainWindow2::eventFilter(watched, event);
}

void MainWindow2::onIconButtonPressed2()
{
    // 如果当前有方块在连接，不能点击方块


    // 记录当前点击的icon
    curIcon2 = dynamic_cast<IconButton *>(sender());

    if(!preIcon2)
    {

        // 如果单击一个icon
        curIcon2->setStyleSheet(kIconClickedStyle);
        preIcon2 = curIcon2;
    }
    else
    {
        if(curIcon2 != preIcon2)
        {
            // 如果不是同一个button就都标记,尝试连接
            curIcon2->setStyleSheet(kIconClickedStyle);
            if(game2->linkTwoTiles2(preIcon2->xID, preIcon2->yID, curIcon2->xID, curIcon2->yID))
            {
                // 锁住当前状态
                isLinking2 = true;


                // 重绘
                update();

                // 延迟后实现连接效果
                QTimer::singleShot(kLinkTimerDelay, this, SLOT(handleLinkEffect2()));

                // 检查是否胜利
                if (game2->isWin2())
                {
                    battlebgm2->stop();
//                    QMessageBox::information(this, "great", "you win");
                    QMessageBox message2(QMessageBox::NoIcon, "You win!", "\n\n原石++");
                    message2.setWindowIcon(QPixmap(":/images/image/icon.png"));
                    message2.setIconPixmap(QPixmap(":/images/image/yuanshi.png"));
                    message2.exec();
                    videoplay2();
                    timer2 = new QTimer;
                    timer2->setInterval(10);
                    timer2->start();
                    connect(timer2,SIGNAL(timeout()),this,SLOT(videofnsh2()));
                 }

                // 每次检查一下是否僵局
                if (game2->isFrozen2())
                {
                    battlebgm2->stop();
                    QMessageBox::information(this, "You lose!", "dead game");
                }

                int *hints = game2->getHint2();
            }
            else
            {

                // 消除失败，恢复
                preIcon2->setStyleSheet(kIconReleasedStyle);
                curIcon2->setStyleSheet(kIconReleasedStyle);

                // 指针置空，用于下次点击判断
                preIcon2 = NULL;
                curIcon2 = NULL;
            }
        }
        else if(curIcon2 == preIcon2)
        {

            preIcon2->setStyleSheet(kIconReleasedStyle);
            curIcon2->setStyleSheet(kIconReleasedStyle);
            preIcon2 = NULL;
            curIcon2 = NULL;
        }
    }
}

void MainWindow2::handleLinkEffect2()
{
    // 消除成功，隐藏掉，并析构
    game2->paintPoints2.clear();
    preIcon2->hide();
    curIcon2->hide();

    preIcon2 = NULL;
    curIcon2 = NULL;

    // 重绘
    update();

    // 恢复状态
    isLinking2 = false;
}

void MainWindow2::initGame2()
{
    //启动游戏

    game2 = new gamemodel2;
    game2->startgame2();

    battlebgm2 = new QMediaPlayer;
    battlebgm2->setMedia(QUrl("qrc:/res/media/battlebg.mp3"));
    battlebgm2->setVolume(40);
    battlebgm2->play();


    //添加button
    for(int i=0;i<MAX_ROW*MAX_COL;i++)
    {
        imageButton2[i]=new IconButton(this);
        imageButton2[i]->setGeometry(kLeftMargin + (i % MAX_COL) * kIconSize, kTopMargin + (i / MAX_COL) * kIconSize, kIconSize, kIconSize);
        //设置索引
        imageButton2[i]->xID=i%MAX_COL;
        imageButton2[i]->yID=i/MAX_COL;

        imageButton2[i]->show();

        if(game2->getGameMap2()[i])
        {
            //有方块就设置图片
            QPixmap iconPix;
            QString fileString;
            fileString.sprintf(":/res/image/%d.png",game2->getGameMap2()[i]);
            iconPix.load(fileString);
            QIcon icon(iconPix);
            imageButton2[i]->setIcon(icon);
            imageButton2[i]->setIconSize(QSize(kIconSize,kIconSize));

            //添加按下的信号槽
            connect(imageButton2[i],SIGNAL(pressed()),this,SLOT(onIconButtonPressed2()));
        }
        else
            imageButton2[i]->hide();
    }

    //游戏计时器
    gameTimer2=new QTimer(this);
    connect(gameTimer2,SIGNAL(timeout()),this,SLOT(gameTimerEvent()));
    gameTimer2->start(kGameTimerInterval);

    //连接状态值
    isLinking2=false;

}

void MainWindow2::videoplay2()
{
    //视频播放
    widget2 = new QWidget;
    layout2 = new QVBoxLayout;
    video2 = new QMediaPlayer;
    videowidget2 = new QVideoWidget;

    videowidget2->setAspectRatioMode(Qt::IgnoreAspectRatio);
    videowidget2->setFullScreen(true);

    layout2->addWidget(videowidget2);
    widget2->setLayout(layout2);

    video2->setMedia(QUrl("qrc:/res/media/gold.mp4"));

    video2->setVideoOutput(videowidget2);

    widget2->showFullScreen();
    video2->play();
}

void MainWindow2::videofnsh2()
{
    status2 = video2->mediaStatus();
    if(status2==QMediaPlayer::EndOfMedia)
    {
        timer2->stop();
        widget2->close();
    }
}
