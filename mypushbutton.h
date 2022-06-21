#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class myPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit myPushButton(QWidget *parent = nullptr);
    myPushButton(QString normalImg, QString pressImg = "");
    QString pressImgPath; //按下显示的图片
    QString normalImgPath; //正常显示的图片

    //弹跳特效
    void zoom1(); //up
    void zoom2(); //down

    //重写按钮 按下和释放事件
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
signals:

};

#endif // MYPUSHBUTTON_H
