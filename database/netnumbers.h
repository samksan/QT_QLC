#ifndef NETNUMBERS_H
#define NETNUMBERS_H

#include <QObject>
#include <QtCore>
#include <QList>

class NetNumbers : public QObject
{
    Q_OBJECT
public:
    static void initQSQLDatabase();
    static void getHtml(QString url);
    static QList<QList<int>> getNumbers();
private:
    static void toDB(int number[100][7]);
    static void strToDB(QString str);
};

#endif // NETNUMBERS_H
