#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database/netnumbers.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionKaijianghaoma_triggered()
{
    QString data = NetNumbers::getHtml
            ("http://trend.caipiao.163.com/qlc/?periodNumber=100");

    NetNumbers::strToDB(data);
}

void MainWindow::on_actionView_triggered()
{
    QList<QList<int>> list = NetNumbers::getNumbers();

    foreach (QList<int> tempList, list) {
        qDebug() << tempList[0] << "," << tempList[1] << "," << tempList[2]
                                << ","<< tempList[3] << ","<< tempList[4]
                                << ","<< tempList[5] << ","<< tempList[6]
                                << ","<< tempList[7] << ","<< tempList[8] << endl;
    }
}
