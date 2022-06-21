#include "chooselevelscene.h"
#include "mypushbutton.h"
#include <QMenuBar>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <QDebug>
#include <QSound>

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //固定宽高
    this->setFixedSize(320,588);
    //设置应用图片
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置窗口标题
    this->setWindowTitle("翻金币关卡选择");

    //无ui文件，自定义
    //创建菜单栏
    QMenuBar *bar = menuBar();
    setMenuBar(bar);
    //创建开始菜单
    QMenu *startMenu = bar->addMenu("开始");
    //创建退出菜单项
    QAction *quitAction = startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    myPushButton *backBtn = new myPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width() , this->height() - backBtn->height());
    connect(backBtn,&QPushButton::clicked,[=](){
        QSound * backSound = new QSound(":/res/TapButtonSound.wav",this);
        backSound->play();
        //告诉主场景返回信号，主场景监听信号
        QTimer::singleShot(100,[=](){
           //第一种解决方法，父类指针
           //this->hide();
           //m_parent->show();

           //第二种解决方法 使用信号和槽 发送信号
            emit this->chooseBackCenario();
         });
    });

    //创建关卡选择按钮
    for(int i = 0;i < 20;i++)
    {
        myPushButton *menuBtn = new myPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        //25是总体和窗口的间距 70是每个间距
        menuBtn->move(25 + i % 4 * 70 ,130 + i / 4 * 70);
        //在上面打上数字
       QLabel * label = new QLabel(this);
       label->setFixedSize(menuBtn->width(),menuBtn->height());
       label->setText(QString::number(i + 1));
       label->move(25 + i % 4 * 70 ,130 + i / 4 * 70);
       //垂直和水平居中
       label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

       //设置让鼠标进行穿透 51号属性
       label->setAttribute(Qt::WA_TransparentForMouseEvents);
        //监听按钮的点击 关卡选择界面
       connect(menuBtn,&QPushButton::clicked,[=](){
            QSound *chooseSound = new QSound(":/res/TapButtonSound.wav",this);
            chooseSound->play();
            qDebug() << QString("你选择的是第 %1 关").arg(i + 1);
            this->hide();
            play = new PlayScene(i+1);
            play->setGeometry(this->geometry());
            play->show();

            connect(play,&PlayScene::chooseBackCenario,[=](){
                play->hide();
                this->setGeometry(play->geometry());
                this->show();
                delete play;
                play = NULL;
            });
        });
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");//背景
    paint.drawPixmap(0,0,this->width(),this->height(),pix);

    //画背景上的图标
    pix.load(":/res/Title.png");
    paint.drawPixmap(this->width() * 0.5 - pix.width() * 0.5 ,30,pix.width() ,pix.height(),pix);
}
