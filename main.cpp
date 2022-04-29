#include "teyvat.h"
#include"login.h"
#include"mainwindow.h"
#include"levelchoose.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login w;
    w.show();

    return a.exec();
}
