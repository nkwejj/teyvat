#include "login.h"

#include<QToolButton>
#include<QPixmap>
#include<QRect>


#include<QDebug>


login::login(QWidget *parent) :
    QMainWindow(parent)
{
    this->setGeometry(QRect(300,150,ScreenWidth,ScreenHeight));
    QIcon icon = QIcon(":/images/image/icon.png");

    this->setWindowTitle("Genshin");
    this->setWindowIcon(icon);
    start();
}

void login::start(){

    mediaplayer = new QMediaPlayer(this);
    mediaplayerlist = new QMediaPlaylist;
    mediaplayerlist->addMedia(QUrl("qrc:/res/media/loginbg.mp3"));
    mediaplayerlist->addMedia(QUrl("qrc:/res/media/loginbg.mp3"));
    mediaplayerlist->addMedia(QUrl("qrc:/res/media/loginbg.mp3"));
    mediaplayer->setPlaylist(mediaplayerlist);
    mediaplayer->play();

    mGameView.setParent(this);
    mGameView.setSceneRect(QRect(20,40,ScreenWidth,ScreenHeight));
    mGameBeginScence.setSceneRect(QRect(0,0,ScreenWidth,ScreenHeight));
    if(hour>=6&&hour<=12){
        mGameBeginScence.addPixmap(QPixmap(":/images/image/morning.jpg"));
    }
    else if(hour>12&&hour<18){
        mGameBeginScence.addPixmap(QPixmap(":/images/image/gate.jpg"));
    }
    else{
        mGameBeginScence.addPixmap(QPixmap(":/images/image/night.jpg"));
    }
     mGameView.setScene(&mGameBeginScence);
     mGameView.show();


     auto StartBtn=new QToolButton();
     StartBtn->setAutoRaise(true);          //设置按钮突出
     if(hour>=6&&hour<=12){
         mGameBeginScence.addPixmap(QPixmap(":/images/image/morning.jpg"));
         StartBtn->setIcon(QIcon(":/images/image/beginbtnmn.png"));
     }
     else if(hour>12&&hour<18){
         mGameBeginScence.addPixmap(QPixmap(":/images/image/gate.jpg"));
         StartBtn->setIcon(QIcon(":/images/image/beginbt.png"));
     }
     else{
         mGameBeginScence.addPixmap(QPixmap(":/images/image/night.jpg"));
         StartBtn->setIcon(QIcon(":/images/image/beginbtnt.png"));
     }
     StartBtn->setIconSize(QSize(200,50));
     StartBtn->move(200,300);

     mGameBeginScence.addWidget(StartBtn);
     //显示按钮

//     connect(StartBtn,&QToolButton::clicked,this,&QWidget::close);
//       connect(StartBtn,SIGNAL(clicked(bool)),SLOT(nextstage()));

     connect(StartBtn,&QToolButton::clicked,[this](){
//         qDebug()<<"点击了开始";
//         this->close();

         this->hide();
         LC.show();
         mediaplayer->stop();
     });
}

