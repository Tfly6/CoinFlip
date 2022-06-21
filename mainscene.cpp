#include "mainscene.h"
#include "ui_mainscene.h"
#include "mypushbutton.h"
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QSound>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //固定宽高
    setFixedSize(320,588);
    //设置应用图片
    setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置窗口标题
    setWindowTitle("翻金币");

    //退出按钮实现
    connect(ui->actionquit,&QAction::triggered,[=](){
       this->close();
    });
    chooseScence = new ChooseLevelScene(); // 选择场景

    //准备开始按钮音效
    QSound *startSound = new QSound(":/res/TapButtonSound.wav",this);

    //开始按钮
    myPushButton *startBtn = new myPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width() * 0.5 - startBtn->width() * 0.5, this->height() * 0.7);

    connect(startBtn,&QPushButton::clicked,[=](){
        chooseScence->setGeometry(this->geometry()); //避免进入下一个场景位置发生变化
        qDebug()<<"start";
        //播放开始音效
        startSound->play();

        startBtn->zoom1();
        startBtn->zoom2();
        //加个延时
        QTimer::singleShot(150,this,[=](){
            //隐藏自己 显示关卡页面
            this->hide();
            chooseScence->show();
        });
    });

    //关卡界面发送退出信号，主函数响应
    connect(this->chooseScence,&ChooseLevelScene::chooseBackCenario,[=](){
        this->setGeometry(chooseScence->geometry());
        this->chooseScence->hide();
        this->show();
    });
}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");//背景
    //pix = pix.scaled(this->width(),this->height());
    paint.drawPixmap(0,0,this->width(),this->height(),pix);

    //画背景上的图标
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    paint.drawPixmap(10,30,pix);
}
MainScene::~MainScene()
{
    delete ui;
}

