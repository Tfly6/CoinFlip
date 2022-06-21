#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mycoin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int levelNum);
    void paintEvent(QPaintEvent *);

    int levelIndex;
    //二维数组维护每关关卡的具体数据
    int gameArray[4][4];
    MyCoin * coinBtn[4][4];

    //判断是否胜利
    bool isWin=false;

signals:
    //写一个信号
    void chooseBackCenario();
};

#endif // PLAYSCENE_H
