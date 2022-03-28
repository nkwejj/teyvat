#ifndef MYSQL_H
#define MYSQL_H

#include <QMainWindow>

#include"QSqlDatabase"
#include<QDebug>
#include<QMessageBox>
#include<QSqlError>
#include<QSqlQuery>
#include<QSqlRecord>

class MySql
{
public:
    MySql(QWidget *parent = 0);

    bool Init();
    bool createConnection();
    bool query();


private:
    int i,j;

    QString dbname_init;//库名
    QStringList table_list_init;//表名
    QStringList head_list_init;//表头

    QSqlDatabase db;//要打开的数据库，不存在则创建
    QSqlQuery mquery;//库的检索类
    QSqlRecord mrecord;//数据记录

    QStringList tablelist;//库里的表列表

//    QStringListIterator *itr;//表名迭代器

//    QString         tableNm;         //迭代器用的暂存表名
//    QString         tableN;       //表名
//    QStringList     head_list;       //表头

};

#endif // MYSQL_H
