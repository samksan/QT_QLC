#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database/netnumbers.h"

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QTableView>

#include "Analysis/analysiscontrol.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 初始化数据库连接
    NetNumbers::initQSQLDatabase();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 从网络获取开奖号码，并保存到数据库
void MainWindow::on_actionKaijianghaoma_triggered()
{
    NetNumbers::getHtml("http://trend.lecai.com/ssq/redBaseTrend.action?recentPhase=100&onlyBody=true");
}

// 连接数据库获取号码并利用 Qt 的 Model-View 显示开奖号码
void MainWindow::on_actionView_triggered()
{
    // 获取数据库连接，测试连接是否成功
    QSqlDatabase db = QSqlDatabase::database();
    bool ok = db.open();

    if(ok){
        qDebug() << "connect ok";
    }else{
        qDebug() << "connect failed";
    }

    // Qt Model-View 显示数据库
    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable("kjh");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("期号"));
    model->setHeaderData(1, Qt::Horizontal, tr("号码1"));
    model->setHeaderData(2, Qt::Horizontal, tr("号码2"));
    model->setHeaderData(3, Qt::Horizontal, tr("号码3"));
    model->setHeaderData(4, Qt::Horizontal, tr("号码4"));
    model->setHeaderData(5, Qt::Horizontal, tr("号码5"));
    model->setHeaderData(6, Qt::Horizontal, tr("号码6"));

    QTableView *table = new QTableView;
    table->setModel(model);
    table->resizeColumnsToContents();
    table->resizeRowsToContents();
    table->setGeometry(200,160,418,360);
    table->show();
}

// 分析历史号码
void MainWindow::on_btnAnalysis_clicked()
{
    // 控制分析过程
    AnalysisControl ana;
    ana.start();
}
