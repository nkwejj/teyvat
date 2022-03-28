#include "mysql.h"

MySql::MySql()
{
}
MySql::~MySql(){

}

bool MySql::Init(){
    qDebug()<<"start";

    this->setFixedSize(800,600);

    i = 0,j = 0;

    dbname_init="MySql.db";
    table_list_init.append("admin");
    table_list_init.append("staff");
    qDebug()<<table_list_init;

    head_list_init.append("ID");
    head_list_init.append("Name");
    head_list_init.append("Age");
    qDebug()<< head_list_init;

    qDebug() << "variable init success..................";

    createConnection();

    qDebug() << "addDatabase success..............";

    tablelist=db.tables();//获取库中的表

    mquery=QSqlQuery(db);//设置要操作的库

    if(tablelist.count()==0){
        mquery.exec(QString("create table %1(%2,%3,%4);")\
                    .arg(table_list_init.at(0))\
                    .arg(head_list_init.at(0))\
                    .arg(head_list_init.at(1))\
                    .arg(head_list_init.at(2)));

    }

    qDebug() << "创建了表" << db.tables().count();

//    itr=new QStringListIterator(tablelist);//迭代器

//    while(itr->hasNext()){
//        i=0;
//        tableNm=itr->next();
//        qDebug()<<tableNm;

//        QString str = "pragma table_info(" + tableNm + ")";

//        QSqlQuery query;
//        query.prepare(str);
//        if (query.exec())
//        {
//            while (query.next())
//            {
//                qDebug() << query.value(0).toString() << query.value(1).toString();     //字段编号 + 表头
//                head_list.insert(i, query.value(1).toString());
//                i++;
//            }
//        }
//        qDebug() << "db.tables(); >> " <<head_list;             //打印获得的表头
//    }

//    tableN = tablelist.at(0);
//    qDebug() <<  "db.tables(); >> " << tableN;                   //打印获得的表名

}

bool MainWindow::createConnection(){
    db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("MySql");
    db.setUserName("root");
    db.setPassword("Aa412113");
    bool ok = db.open();
    if (ok){
        QMessageBox::information(this, "infor", "success");
    }
    else {
        QMessageBox::information(this, "infor", "open failed");
        qDebug()<<"error open database because"<<db.lastError().text();
    }
}

bool MainWindow::query(){
    //查询数据库中所有表的名称
    foreach(QString table, tablelist)
        qDebug()<<table;

    //ODBC查询数据
    QSqlQuery result = db.exec(" select * from users");
    while(result.next()){
        qDebug()<<"ID:"<<result.value("ID").toInt();
        qDebug()<<"name:"<<result.value("name").toString();
        qDebug()<<"age:"<<result.value("age").toString();
    }

}
