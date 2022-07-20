#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include "chooselevelscene.h"
#include "mypushbutton.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();
    /*
     * 对于绘图事件，只需要在相应的位置进行重写即可
     * 如果不对paintEvent重写，其实现为空
     * 不需要主动调用，Qt事件循环会自动处理绘图事件，并根据重写的内容做出响应。
     */
    void paintEvent(QPaintEvent *);

    void start(); //开始槽

    ChooseLevelScene *chooseScence = NULL;//关卡选择页面
    myPushButton *startBtn = NULL;// 开始按钮
private:
    Ui::MainScene *ui;
};
#endif // MAINSCENE_H
