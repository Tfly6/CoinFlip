#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include "playscene.h"
#include "mypushbutton.h"

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void back(); //返回槽
    void todo(); //在界面上要的操作

    PlayScene *play = NULL;//游戏窗口指针
    myPushButton *backBtn = NULL; // 返回按钮

signals:
    void chooseBackCenario();
};

#endif // CHOOSELEVELSCENE_H
