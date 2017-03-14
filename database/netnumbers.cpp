#include "NetNumbers.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QDebug>

/**
 * @brief NetNumbers::getNumbers 从数据库中获取开奖号码
 * @return QList<QList<int>> 返回开奖号码
 */
QList<QList<int>> NetNumbers::getNumbers()
{
    // 获取数据库连接
    QSqlDatabase db = QSqlDatabase::database();

    // 获取数据库内容，把内容放进 QList 容器，并返回
    QSqlQuery query;
    query.exec("SELECT * FROM kjh");

    QList<QList<int>> list;
    while(query.next())
    {
       QList<int> temp;
       temp.append(query.value(0).toInt());
       temp.append(query.value(1).toInt());
       temp.append(query.value(2).toInt());
       temp.append(query.value(3).toInt());
       temp.append(query.value(4).toInt());
       temp.append(query.value(5).toInt());
       temp.append(query.value(6).toInt());
       list.append(temp);
    }

    db.close();
    return list;
}

/**
 * @brief NetNumbers::toDB 把从网络获取的二维数组（开奖号码）保存到数据库
 * @param number 从网络得到的开奖号码
 */
void NetNumbers::toDB(int number[100][7])
{
    // 获取数据库连接
    QSqlDatabase db = QSqlDatabase::database();

    // 格式化数据表，保存开奖号
    QSqlQuery query;
    query.exec("create table kjh(sn int primarykey,n1 int,n2 int,n3 int,n4 int,n5 int,n6 int)");
    query.exec("DELETE FROM kjh");

    query.prepare("INSERT INTO kjh VALUES(?,?,?,?,?,?,?)");
    for (int var = 0; var < 100; ++var) {
        query.bindValue(0,number[var][0]);
        query.bindValue(1,number[var][1]);
        query.bindValue(2,number[var][2]);
        query.bindValue(3,number[var][3]);
        query.bindValue(4,number[var][4]);
        query.bindValue(5,number[var][5]);
        query.bindValue(6,number[var][6]);
        query.exec();
    }

    query.exec("select * from kjh");

    int total = 0;
    while (query.next()) {
        total++;
    }
    if(total == 100)
        qDebug() << "数据更新成功" << endl;
    else
        qDebug() << "数据更新失败" << endl;

    db.close();
}

/**
 * @brief NetNumbers::initQSQLDatabase 初始化数据库连接，在任意位置都可以获取到数据库连接实例
 */
void NetNumbers::initQSQLDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName("kjhdb.db");
}

/**
 * @brief NetNumbers::getHtml 通过网站过滤得到开奖号码
 * @param url 获取开奖号码的网址
 */
void NetNumbers::getHtml(QString url)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(url)));
    QByteArray responseData;
    QEventLoop eventLoop;
    connect(manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    eventLoop.exec();       //block until finish
    responseData = reply->readAll();
    strToDB(responseData);
}

/**
 * @brief NetNumbers::strToDB 处理从网络获取到的字符串，调用函数生成开奖号保存到数据库
 * @param str 从网络获取到的字符串
 */
void NetNumbers::strToDB(QString str)
{
    QStringList list;
    QString temp = "chart_table_td chart_table_td_phase";

    // 分隔成101个字符串（1 - 100）包含开奖号码，0是网站的信息头
    list = str.split(temp);
    list.removeFirst();

    QString sn,s1,s2,s3,s4,s5,s6;
    int result[100][7];

    for (int var = 0; var < list.size(); ++var) {

        // 临时 QStringList
        QStringList tempList;

        // 分割字符串所需的字符串
        QString splitString = "chart_table_td omission_entry omission_hit red_ball background_color_";

        // 当前期号的整体字符串
        QString stringTemp = list[var];

        tempList = stringTemp.split(splitString);

        sn = tempList[0].mid(2,5);
        s1 = tempList[1].mid(8,2);
        s2 = tempList[2].mid(8,2);
        s3 = tempList[3].mid(8,2);
        s4 = tempList[4].mid(8,2);
        s5 = tempList[5].mid(8,2);
        s6 = tempList[6].mid(8,2);
        result[var][0] = sn.toInt();
        result[var][1] = s1.toInt();
        result[var][2] = s2.toInt();
        result[var][3] = s3.toInt();
        result[var][4] = s4.toInt();
        result[var][5] = s5.toInt();
        result[var][6] = s6.toInt();
    }
    NetNumbers::toDB(result);

}




