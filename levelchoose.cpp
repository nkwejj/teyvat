#include "levelchoose.h"
#include "ui_levelchoose.h"

#include<QDebug>
#include<QToolButton>

//int gamelevel;

LevelChoose::LevelChoose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LevelChoose)
{
    ui->setupUi(this);

    this->setGeometry(QRect(300,150,600,400));
    QIcon icon = QIcon(":/images/image/icon.png");

    this->setWindowTitle("Genshin");
    this->setWindowIcon(icon);

    //设置背景图片
    QPixmap pixmap = QPixmap(":/images/image/enterbg.png").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);

    LCinit();
}

LevelChoose::~LevelChoose()
{
    delete ui;
}

void LevelChoose::LCinit()
{

    mLCView.setParent(this);
    mLCView.setSceneRect(QRect(20,40,600,450));

    mLCScence.setSceneRect(QRect(0,0,600,450));
    mLCScence.addPixmap(QPixmap(":/images/image/enterbg.png").scaled(650,450));

    mLCPItem.setPixmap(QPixmap(":/images/image/4.png").scaled(200,50));

    mLCScence.addItem(&mLCPItem);

    mLCPItem.setPos(0,50);
    mLCPItem.setOffset(200,50);

    mLCView.setScene(&mLCScence);
    mLCView.show();


     auto Btn1=new QToolButton();
     Btn1->setAutoRaise(true);          //设置按钮突出
     Btn1->setIcon(QIcon(QPixmap(":/images/image/1.png").scaled(200,50)));
     Btn1->setIconSize(QSize(200,50));
     Btn1->move(200,200);
     mLCScence.addWidget(Btn1);      //显示按钮
     connect(Btn1,&QToolButton::clicked,[this](){
         this->close();
         changeto1();
//         mw.show();
     });

     auto Btn2=new QToolButton();
     Btn2->setAutoRaise(true);          //设置按钮突出
     Btn2->setIcon(QIcon(QPixmap(":/images/image/2.png").scaled(200,50)));
     Btn2->setIconSize(QSize(200,50));
     Btn2->move(200,275);
     mLCScence.addWidget(Btn2);      //显示按钮
     connect(Btn2,&QToolButton::clicked,[this](){
         this->close();
         changeto2();
//         mw2.show();
     });

     auto Btn3=new QToolButton();
     Btn3->setAutoRaise(true);          //设置按钮突出
     Btn3->setIcon(QIcon(QPixmap(":/images/image/3.png").scaled(200,50)));
     Btn3->setIconSize(QSize(200,50));
     Btn3->move(200,350);
     mLCScence.addWidget(Btn3);      //显示按钮
     connect(Btn3,&QToolButton::clicked,[this](){
         this->close();
         changeto3();
//         mw3.show();
     });
}

void LevelChoose::videoplay()
{
        //视频播放
        widget = new QWidget;
        layout = new QVBoxLayout;
        video = new QMediaPlayer;
        videowidget = new QVideoWidget;

        videowidget->setAspectRatioMode(Qt::IgnoreAspectRatio);
        videowidget->setFullScreen(true);

        layout->addWidget(videowidget);
        widget->setLayout(layout);

        video->setMedia(QUrl("qrc:/res/media/entervideo.mp4"));

        video->setVideoOutput(videowidget);

        widget->showFullScreen();
        video->play();

}

void LevelChoose::getstatus1()
{
    status = video->mediaStatus();
    if(status==QMediaPlayer::EndOfMedia)
    {
        widget->close();
        mw.show();
    }
}

void LevelChoose::changeto1()
{
    videoplay();
    timer = new QTimer;
    timer->setInterval(10);
    timer->start();
    connect(timer,SIGNAL(timeout()),this,SLOT(getstatus1()));

}

void LevelChoose::getstatus2()
{
    status = video->mediaStatus();
    if(status==QMediaPlayer::EndOfMedia)
    {
        widget->close();
        mw2.show();
    }
}

void LevelChoose::changeto2()
{
    videoplay();
    timer = new QTimer;
    timer->setInterval(10);
    timer->start();
    connect(timer,SIGNAL(timeout()),this,SLOT(getstatus2()));

}

void LevelChoose::getstatus3()
{
    status = video->mediaStatus();
    if(status==QMediaPlayer::EndOfMedia)
    {
        widget->close();
        mw3.show();
    }
}

void LevelChoose::changeto3()
{
    videoplay();
    timer = new QTimer;
    timer->setInterval(10);
    timer->start();
    connect(timer,SIGNAL(timeout()),this,SLOT(getstatus3()));

}

