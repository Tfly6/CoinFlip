#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>
class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //参数代表传入的是金币还是银币路径
    MyCoin(QString btnImg);

    //改变标志的方法
    void changeFlag();

    //重写按下
    void mousePressEvent(QMouseEvent *e);

    //金币的属性
    int posX;//x 坐标
    int posY;//y 坐标
    bool flag;// 正反提示
    int min=1;
    int max=8;

    //执行动画的标志,优化多次点击
    bool isAnimation=false;
    //胜利后的失败
    bool isWin=false;

    QTimer *time1;//正面翻反面的定时器
    QTimer *time2;//反面翻正面的定时器
signals:

};

#endif // MYCOIN_H
