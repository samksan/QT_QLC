#ifndef NETNUMBERS_H
#define NETNUMBERS_H

#include <QObject>
#include <QtCore>
#include <QList>

class NetNumbers : public QObject
{
    Q_OBJECT
public:
    static void getHtml(QString url);
    static void strToDB(QString str);
    static QList<QList<int>> getNumbers();
private:
    static void toDB(int number[100][9]);
};

#endif // NETNUMBERS_H
