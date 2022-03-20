#include "login.h"

#include<QToolButton>
#include<QPixmap>
#include<qrect.h>

#include<QDebug>

login::login(QWidget *parent) :
    QMainWindow(parent)
{
    this->setGeometry(QRect(300,150,ScreenWidth,ScreenHeight));
    start();
}

void login::start(){

    mGameView.setParent(this);
    mGameView.setSceneRect(QRect(20,40,ScreenWidth,ScreenHeight));

    mGameBeginScence.setSceneRect(QRect(0,0,ScreenWidth,ScreenHeight));
    mGameBeginScence.addPixmap(QPixmap(":/images/image/gate.jpg"));

    mGameView.setScene(&mGameBeginScence);
    mGameView.show();


     auto StartBtn=new QToolButton();
     StartBtn->setAutoRaise(true);          //设置按钮突出
     StartBtn->setIcon(QIcon(":/images/image/beginbtn.png"));
     StartBtn->setIconSize(QSize(200,50));
     StartBtn->move(200,300);
     mGameBeginScence.addWidget(StartBtn);      //显示按钮

//     connect(StartBtn,&QToolButton::clicked,[this](){
//         LoadStageScence();
//     });

//     connect(StartBtn,&QToolButton::clicked,this,&QWidget::close);
//       connect(StartBtn,SIGNAL(clicked(bool)),SLOT(nextstage()));

//     Instruction.setPixmap(QPixmap(":/new/prefix1/资源/操作提示1.jpg"));
//     connect(StartBtn1,&QToolButton::clicked,[=](){
//         mGameBeginScence.addItem(&Instruction);
//         mGameBeginScence.addWidget(StartBtn2);
//     });


//     s=new Snake;
     connect(StartBtn,&QToolButton::clicked,[this](){
//         qDebug()<<"点击了开始";
//         this->hide();
//         s->show();

         this->close();
     });
}
