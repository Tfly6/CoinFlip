#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include <QTimer> //定时器
//#include <QTime> 计时器
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
    //退出
    connect(ui->actionquit,&QAction::triggered,[=](){
       this->close();
    });


    //开始按钮
    startBtn = new myPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width() * 0.5 - startBtn->width() * 0.5, this->height() * 0.7);
    connect(startBtn,&QPushButton::clicked,this,&MainScene::start);

    //关卡选择界面发送退出信号，主函数响应
    chooseScence = new ChooseLevelScene(); // 选择场景
    connect(this->chooseScence,&ChooseLevelScene::chooseBackCenario,[=](){
        this->setGeometry(chooseScence->geometry());
        this->show();
        QTimer::singleShot(300,this,[=](){
            this->chooseScence->hide();
        });
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

void MainScene::start()
{
    //准备开始按钮音效
    QSound *startSound = new QSound(":/res/TapButtonSound.wav",this);
    chooseScence->setGeometry(this->geometry()); //避免进入下一个场景位置发生变化
    //qDebug()<<"start";
    //播放开始音效
    startSound->play();

    startBtn->zoom1();
    startBtn->zoom2();
    //加个延时
    QTimer::singleShot(300,this,[=](){
        //隐藏自己 显示关卡页面
        /*
         * 为了消除界面切换的闪烁
         * 先显示子页面再隐藏父页面,而隐藏父界面的操作比显示子页面的操作快得多
         * 所以可以在这个过程中间加一个延时
         */
        chooseScence->show();
//        QTime dieTime = QTime::currentTime().addMSecs(300);//延时300毫秒
//               while (QTime::currentTime() < dieTime)
//                       QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        QTimer::singleShot(300,this,[=](){
            this->hide();
        });
    });
}
MainScene::~MainScene()
{
    delete ui;
}

