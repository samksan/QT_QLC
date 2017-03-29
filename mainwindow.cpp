#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database/netnumbers.h"

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QTableView>

#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

#include "Analysis/analysiscontrol.h"
#include "Analysis/analysisutils.h"

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
    table->setGeometry(200,160,756,500);
    table->horizontalHeader()->adjustSize();
    table->show();
}

// 分析历史号码
void MainWindow::on_btnAnalysis_clicked()
{
    // 控制分析过程
    AnalysisControl ana;
    ana.start();
}

void MainWindow::on_actionCompare_triggered()
{
    // 选择文件的对话框
    QString file = QFileDialog::getOpenFileName(this,tr("选择文件"),"D:/",tr("文本文件(*.txt)"));
    qDebug() << "选择的文件为:" << file;

    // 读取选择文件,文件格式固定
    // 文件按行记录购买的号码 04 07 08 19 32 33-13 , 其中第一行是官方开奖号码,第二行开始是购买的号码
    QFile number_file(file);
    if(!number_file.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "打开文件失败!";
        return;
    }

    QTextStream read_text(&number_file);
    QString text = read_text.readAll();
    // 关闭文件
    number_file.close();

    QVector<QString> zz = AnalysisUtils::NumbersCompare(text);
    QString result;
    foreach (QString str, zz) {
        result += str;
        result += "\n";
    }

    QMessageBox::information(NULL,tr("开奖结果对比"),result,QMessageBox::Ok);
    qDebug() << result;
}

void MainWindow::on_actionCompare_hovered()
{
    ui->statusBar->showMessage(tr("txt格式:xx xx xx xx xx xx-xx 第一行为开奖号码,之后是购买的号码"),3000);
}
