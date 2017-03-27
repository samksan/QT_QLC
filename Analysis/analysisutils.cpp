#include "analysisutils.h"

AnalysisUtils::AnalysisUtils(QObject *parent) : QObject(parent)
{

}

/**
 * @brief AnalysisUtils::NumbersContrast 开奖号码和购买的方案的对比
 * @param text  QString 文本文件读取的内容
 * @return QList<QString> 中奖信息
 */
QList<QString> AnalysisUtils::NumbersContrast(QString text)
{
    QList<QString> list = text.split("\n");
    QList<QList<int>> buy_number;
    QList<int> temp;
    for (int var = 0; var < list.length(); ++var) {
        temp.append(list[var].mid(0,2).toInt());
        temp.append(list[var].mid(3,2).toInt());
        temp.append(list[var].mid(6,2).toInt());
        temp.append(list[var].mid(9,2).toInt());
        temp.append(list[var].mid(12,2).toInt());
        temp.append(list[var].mid(15,2).toInt());
        temp.append(list[var].mid(18,2).toInt());
        buy_number.append(temp);
        temp.clear();
    }

    // 开奖号码
    int r1 = buy_number[0].at(0);
    int r2 = buy_number[0].at(1);
    int r3 = buy_number[0].at(2);
    int r4 = buy_number[0].at(3);
    int r5 = buy_number[0].at(4);
    int r6 = buy_number[0].at(5);
    int num_blue = buy_number[0].at(6);

    // 一等奖 6+1
    // 二等奖 6+0
    // 三等奖 5+1                             3000
    // 四等奖 5+0 或 4+1                  200
    // 五等奖 4+0 或 3+1                  10
    // 六等奖 2+1 或 1+1 或 0+1        5
    // 号码对比函数, 从buy_number[1] 开始
    int red_count = 0;
    int blue_count = 0;
    int first,second,third,fourth,fifth,sixth;
    QList<int> red_number;

    // 返回的结果
    QList<QString> zz;
    for (int var = 1; var < buy_number.length(); ++var) {
        // 红球号码
        red_number << buy_number[var].at(0) << buy_number[var].at(1) << buy_number[var].at(2)
                   << buy_number[var].at(3) << buy_number[var].at(4) << buy_number[var].at(5);

        // 对比号码,得出 red_count,blue_count 红蓝球匹配个数
        if(red_number.contains(r1))
            red_count++;
        if(red_number.contains(r2))
            red_count++;
        if(red_number.contains(r3))
            red_count++;
        if(red_number.contains(r4))
            red_count++;
        if(red_number.contains(r5))
            red_count++;
        if(red_number.contains(r6))
            red_count++;
        if(buy_number[var].at(6) == num_blue)
            blue_count++;

        switch (red_count) {
        case 6:
            if(blue_count == 1){
                first++;                        // 一等奖 6+1
                zz << "一等奖" + QString::number(r1) + " " + QString::number(r2) + " " + QString::number(r3) + " " + QString::number(r4) + " " + QString::number(r5) + " " + QString::number(r6) + "-" + QString::number(num_blue);
            }else if (blue_count == 0) {
                second++;                   // 二等奖 6+0
                zz << "二等奖" + QString::number(r1) + " " + QString::number(r2) + " " + QString::number(r3) + " " + QString::number(r4) + " " + QString::number(r5) + " " + QString::number(r6) + "-" + QString::number(num_blue);
            }
            break;
        case 5:
            if(blue_count == 1){
                third++;                    // 三等奖 5+1                             3000
                zz << "三等奖" + QString::number(r1) + " " + QString::number(r2) + " " + QString::number(r3) + " " + QString::number(r4) + " " + QString::number(r5) + " " + QString::number(r6) + "-" + QString::number(num_blue);
            }else if (blue_count == 0) {
                fourth++;                   // 四等奖 5+0 或 4+1                  200
                zz << "四等奖" + QString::number(r1) + " " + QString::number(r2) + " " + QString::number(r3) + " " + QString::number(r4) + " " + QString::number(r5) + " " + QString::number(r6) + "-" + QString::number(num_blue);
            }
            break;
        case 4:
            if(blue_count == 1){
                fourth++;                   // 四等奖 5+0 或 4+1                  200
                zz << "四等奖" + QString::number(r1) + " " + QString::number(r2) + " " + QString::number(r3) + " " + QString::number(r4) + " " + QString::number(r5) + " " + QString::number(r6) + "-" + QString::number(num_blue);
            }else if (blue_count == 0) {
                fifth++;                    // 五等奖 4+0 或 3+1                  10
                zz << "五等奖" + QString::number(r1) + " " + QString::number(r2) + " " + QString::number(r3) + " " + QString::number(r4) + " " + QString::number(r5) + " " + QString::number(r6) + "-" + QString::number(num_blue);
            }
            break;
        case 3:
            if(blue_count == 1){
                fifth++;                    // 五等奖 4+0 或 3+1                  10
                zz << "五等奖" + QString::number(r1) + " " + QString::number(r2) + " " + QString::number(r3) + " " + QString::number(r4) + " " + QString::number(r5) + " " + QString::number(r6) + "-" + QString::number(num_blue);
            }
            break;
        default:
            if(blue_count == 1){
                sixth++;                    // 六等奖 2+1 或 1+1 或 0+1        5
                zz << "六等奖" + QString::number(r1) + " " + QString::number(r2) + " " + QString::number(r3) + " " + QString::number(r4) + " " + QString::number(r5) + " " + QString::number(r6) + "-" + QString::number(num_blue);
            }
            break;
        }
        // 清空临时变量的数据
        red_count = 0;
        blue_count = 0;

    }

    return zz;
}
