#include "playscene.h"
#include <QMenuBar>
#include <QAction>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <QDebug>
#include <QPropertyAnimation>
#include <QSound>
#include "mypushbutton.h"
#include "mycoin.h"
#include "dataconfig.h"

//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}

PlayScene::PlayScene(int levelNum)
{
    this->levelIndex = levelNum;

    //固定宽高
    this->setFixedSize(320,588);
    //设置应用图片
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置窗口标题
    this->setWindowTitle("翻金币");

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
        //告诉选择场景返回信号，选择场景监听信号
        QTimer::singleShot(50,[=](){
            emit this->chooseBackCenario();
         });
    });

    //显示当前关卡数
    QLabel * label = new QLabel(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    label->setFont(font);
    //设置位置和大小
    label->setGeometry(30, this->height()-50, 150, 50);
    label->setText(QString("Level：%1").arg(levelNum));

    //胜利图片显示 默认在背景外
    QLabel * winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width() - tmpPix.width()) * 0.5, -400);

    //初始化每个关卡的二维数组
    dataConfig config;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            this->gameArray[i][j]=config.mData[this->levelIndex][i][j];
        }
    }

    //金币
    for(int i=0;i<4;i++)
    {
       for(int j=0;j<4;j++)
       {
           //绘制背景图片
           QPixmap pix=QPixmap(":/res/BoardNode.png");
           QLabel *label=new QLabel;
           label->setGeometry(0,0,50,50);
           label->setPixmap(pix);
           label->setParent(this);
           label->move(57+i*50,200+j*50);

           //判断是金币还是银币
           QString str;
           if(this->gameArray[i][j]==1)
           {
               str=":/res/Coin0001.png";
           }
           else
           {
               str=":/res/Coin0008.png";
           }
           //创建金币
           MyCoin *coin=new MyCoin(str);
           coin->setParent(this);
           coin->move(59+i*50,204+j*50);

           //设置金币属性
           coin->posX=i;
           coin->posY=j;
           coin->flag=this->gameArray[i][j]; //  1正面 0反面

           //将金币放入到金币的二维数组里面
           this->coinBtn[i][j] = coin;

           //点击金币进行翻转
           connect(coin,&QPushButton::clicked,[=](){
               QSound * coinsoud = new QSound(":/res/ConFlipSound.wav",this);
               coinsoud->play();
               //在翻转金币的时候禁用其他按钮
               for(int i = 0 ; i < 4; i++)
               {
                   for(int j = 0 ; j < 4 ; j++)
                   {
                       this->coinBtn[i][j]->isWin = true;
                   }
               }

               coin->changeFlag();
               this->gameArray[i][j] = this->gameArray[i][j]==0?1:0;

                // 翻转周围硬币的操作，延时翻转
               QTimer::singleShot(100,this,[=](){
                  if(coin->posX+1 <= 3) // 周围的下侧硬币翻转的条件
                  {
                      this->coinBtn[coin->posX+1][coin->posY]->changeFlag();
                      this->gameArray[coin->posX+1][coin->posY]=this->gameArray[coin->posX+1][coin->posY]==0?1:0;
                  }
                  if(coin->posX-1>=0) // 周围硬币的上侧翻转条件
                  {
                      this->coinBtn[coin->posX-1][coin->posY]->changeFlag();
                      this->gameArray[coin->posX-1][coin->posY]=this->gameArray[coin->posX-1][coin->posY]==0?1:0;
                  }
                  if(coin->posY+1<=3) // 周围左侧硬币的翻转条件
                  {
                      this->coinBtn[coin->posX][coin->posY+1]->changeFlag();
                      this->gameArray[coin->posX][coin->posY+1]=this->gameArray[coin->posX][coin->posY+1]==0?1:0;
                  }
                  if(coin->posY-1>=0) // 周围硬币的右侧翻转条件
                  {
                      this->coinBtn[coin->posX][coin->posY-1]->changeFlag();
                      this->gameArray[coin->posX][coin->posY-1]=this->gameArray[coin->posX][coin->posY-1]==0?1:0;
                  }

                  //在翻转完金币的时候释放其他按钮
                  for(int i = 0 ; i < 4; i++)
                  {
                      for(int j = 0 ; j < 4 ; j++)
                      {
                          this->coinBtn[i][j]->isWin = false;
                      }
                  }

                  //判断是否胜利
                 this->isWin=true;
                 for(int i=0;i<4;i++)
                 {
                     for(int j=0;j<4;j++){
                         if(coinBtn[i][j]->flag==false){
                             this->isWin=false;
                             break;
                         }
                     }
                 }
                 if(this->isWin==true){
                     //this->backBtn->m_flag = true;
                     //胜利了
                     qDebug() << "胜利了";
                     //将所有按钮胜利的标志改为 true,如果再次点击按钮直接return
                     for(int i=0;i<4;i++)
                     {
                         for(int j=0;j<4;j++){
                             coinBtn[i][j]->isWin=true;
                         }
                     }
                     //将胜利图片砸下来
                     QPropertyAnimation * an = new QPropertyAnimation(winLabel,"geometry");
                     an->setDuration(1000);
                     an->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                     an->setEndValue(QRect(winLabel->x(),winLabel->y() + 300,winLabel->width(),winLabel->height()));
                     an->setEasingCurve(QEasingCurve::OutBounce);
                     an->start();

                     QSound * winsoud = new QSound(":/res/LevelWinSound.wav",this);
                     winsoud->play();
                 }



               });
           });
       }
    }
}

void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");//背景
    paint.drawPixmap(0,0,this->width(),this->height(),pix);

    //画背景上的图标
    pix.load(":/res/Title.png");
    paint.drawPixmap(this->width() * 0.5 - pix.width() * 0.5 ,30,pix.width() ,pix.height(),pix);
}
