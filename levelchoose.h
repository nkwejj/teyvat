#ifndef LEVELCHOOSE_H
#define LEVELCHOOSE_H

#include <QWidget>
#include"mainwindow.h"


//enum GameLevel
//{
//    BASIC,
//    MEDIUM,
//    HARD
//};

namespace Ui {
class LevelChoose;
}

class LevelChoose : public QWidget
{
    Q_OBJECT

public:
    explicit LevelChoose(QWidget *parent = 0);
    ~LevelChoose();
    MainWindow mw;


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::LevelChoose *ui;
};

#endif // LEVELCHOOSE_H
