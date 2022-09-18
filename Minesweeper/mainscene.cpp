#include "mainscene.h"
#include "ui_mainscene.h"
#include "mybtn.h"
#include "mylabel.h"
#include "playscene.h"
#include <QTimer>
#include <QLineEdit>
#include <QMessageBox>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //设置窗口图标
    setFixedSize(320,480);
    setWindowIcon(QIcon(":/res/mine.png"));
    setWindowTitle("选择难度");

    connect(ui->actionquit, &QAction::triggered,[=](){
        this->close();
    });

    MyLabel *label_10 = new MyLabel("初级：10 X 10");
    label_10->setParent(this);
    label_10->move(this->width()*0.1, -170);

    MyLabel *label_20 = new MyLabel("中级：20 X 20");
    label_20->setParent(this);
    label_20->move(this->width()*0.1, -90);

    MyLabel *label_50 = new MyLabel("高级：30 X 30");
    label_50->setParent(this);
    label_50->move(this->width()*0.1, -10);

    MyLabel *label_customize = new MyLabel("自定义：\n行数：\n列数：\n雷数：");
    label_customize->setParent(this);
    label_customize->move(this->width()*0.1, 115);

    QLineEdit *w = new QLineEdit;
    w->setParent(this);
    w->setFixedSize(70,20);
    w->move(this->width()*0.4, 330);
    QLineEdit *h = new QLineEdit;
    h->setParent(this);
    h->setFixedSize(70,20);
    h->move(this->width()*0.4, 365);
    QLineEdit *n = new QLineEdit;
    n->setParent(this);
    n->setFixedSize(70,20);
    n->move(this->width()*0.4, 400);

    MyBtn *startBtn_10 = new MyBtn(":/res/StartButton.png");
    startBtn_10->setParent(this);
    startBtn_10->move(this->width()*0.7, this->height()*0.1-5);

    MyBtn *startBtn_20 = new MyBtn(":/res/StartButton.png");
    startBtn_20->setParent(this);
    startBtn_20->move(this->width()*0.7, this->height()*0.3-20);

    MyBtn *startBtn_30 = new MyBtn(":/res/StartButton.png");
    startBtn_30->setParent(this);
    startBtn_30->move(this->width()*0.7, this->height()*0.5-35);

    MyBtn *startBtn_customize = new MyBtn(":/res/StartButton.png");
    startBtn_customize->setParent(this);
    startBtn_customize->move(this->width()*0.7, this->height()*0.7);

    connect(startBtn_10, &MyBtn::clicked,[=](){
        startBtn_10->zoom1();
        startBtn_10->zoom2();

        //延时进入
        QTimer::singleShot(230,this,[=](){
            PlayScene *play = new PlayScene(10,10);
            play->show();
            this->hide();
            connect(play,&PlayScene::playSceneClose,[=](){
                this->show();
            });
            connect(play,&PlayScene::restartGame,[=](){
                PlayScene *play = new PlayScene(10,10);
                play->show();
            });
        });
    });
    connect(startBtn_20, &MyBtn::clicked,[=](){
        startBtn_20->zoom1();
        startBtn_20->zoom2();

        //延时进入
        QTimer::singleShot(230,this,[=](){
            PlayScene *play = new PlayScene(20,20);
            play->show();
            this->hide();
            connect(play,&PlayScene::playSceneClose,[=](){
                this->show();
            });
            connect(play,&PlayScene::restartGame,[=](){
                PlayScene *play = new PlayScene(20,20);
                play->show();
            });
        });
    });
    connect(startBtn_30, &MyBtn::clicked,[=](){
        startBtn_30->zoom1();
        startBtn_30->zoom2();

        //延时进入
        QTimer::singleShot(230,this,[=](){
            PlayScene *play = new PlayScene(30,30);
            play->show();
            this->hide();
            connect(play,&PlayScene::playSceneClose,[=](){
                this->show();
            });
            connect(play,&PlayScene::restartGame,[=](){
                PlayScene *play = new PlayScene(30,30);
                play->show();
            });
        });
    });
    connect(startBtn_customize, &MyBtn::clicked,[=](){
        startBtn_customize->zoom1();
        startBtn_customize->zoom2();

        int row = w->text().toInt();
        int col = h->text().toInt();
        int num = n->text().toInt();
        if(num>=row * col){
            QMessageBox::information(this,"提示","雷太多了");
            return;
        }
        if(row>100 || col>100)
        {
            QMessageBox::information(this,"提示","地图太大了");
            return;
        }
        //延时进入
        QTimer::singleShot(230,this,[=](){
            PlayScene *play = new PlayScene(row, col, num);
            play->show();
            this->hide();
            connect(play,&PlayScene::playSceneClose,[=](){
                this->show();
            });
            connect(play,&PlayScene::restartGame,[=](){
                PlayScene *play = new PlayScene(row, col, num);
                play->show();
            });
        });
    });
}

MainScene::~MainScene()
{
    delete ui;
}

