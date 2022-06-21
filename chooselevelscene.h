#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include "playscene.h"

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    ////游戏窗口指针
    PlayScene *play = NULL;
signals:
    void chooseBackCenario();
};

#endif // CHOOSELEVELSCENE_H
