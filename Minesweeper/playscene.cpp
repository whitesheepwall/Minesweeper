#include "playscene.h"
#include <QMenuBar>
#include <QPainter>
#include <QLabel>
#include <iostream>

using namespace std;
//PlayScene::PlayScene(QWidget *parent)
//    : QMainWindow{parent}
//{

//}

PlayScene::PlayScene(int x, int y, int n)
{
    srand(time(0));
    row = x;
    col = y;
    if(col==10 && n==0) numMine = 10;
    else if (col==20 && n==0) numMine = 50;
    else if (col==30 && n==0) numMine = 220;
    else numMine = n;
    //*****************初始化界面************************
    this->setFixedSize(25*col+50,25*row+50);
    this->setWindowIcon(QIcon(":/res/mine.png"));
    QString str = QString("扫雷 %1 * %2").arg(row).arg(col);
    this->setWindowTitle(str);

    //******************创建菜单栏***********************
    QMenuBar *bar = menuBar();
    setMenuBar(bar);
    QMenu *startMenu = bar->addMenu("开始");
    QAction *quitAction = startMenu->addAction("退出");
    QAction *returnAction = startMenu->addAction("返回");
    QAction *restartAction = startMenu->addAction("重新开始");
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });
    connect(returnAction,&QAction::triggered,[=](){
        emit playSceneClose();
        this->close();
    });
    connect(restartAction,&QAction::triggered,[=](){
        emit restartGame();
        this->close();
    });


    //********************生成雷区**********************

    this->generateMap();

    //********************显示网格**********************
    QPixmap pix = QPixmap(":/res/BoardNode.png");
    pix = pix.scaled(pix.width()*0.5, pix.height()*0.5);
    QVector<MyMap*> t;
    QVector<Screen*> t1;
    for(int i=1;i<row+1;i++)
    {
        for(int j=1;j<col+1;j++)
        {
            QLabel *label = new QLabel; //底层背景层
            label->setParent(this);
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(pix);
            label->move(25+(j-1)*25,25+(i-1)*25);

            MyMap *obj;
            if(temp[i][j]==-1){   //雷格子
                obj = new MyMap(":/res/mine.png");
                obj->posX = i-1;
                obj->posY = j-1;
                obj->type = -1;
            }
            else if(temp[i][j]==0){  //空格子
                obj = new MyMap(":/res/null.png");
                obj->posX = i-1;
                obj->posY = j-1;
                obj->type = 0;
            }
            else{     //数字格子
                obj = new MyMap(QString(":/res/number%1.png").arg(temp[i][j]));
                obj->posX = i-1;
                obj->posY = j-1;
                obj->type = temp[i][j];
            }
            obj->setParent(label);
            obj->hide();//信息层
            t.push_back(obj);

            //最顶层遮挡,点击可打开
            Screen *screen = new Screen(":/res/BoardNode.png");
            screen->setParent(label);
            screen->posX = i-1;
            screen->posY = j-1;
            connect(screen, &Screen::clicked, this, &PlayScene::screenClicked);
            t1.push_back(screen);
        }
        mineArea.push_back(t);
        screenArea.push_back(t1);
        t.clear();
        t1.clear();
    }
}

void PlayScene::paintEvent(QPaintEvent *e)
{
    QPixmap pix;
    QPainter painter(this);
    //背景
    bool ret = pix.load(":/res/window.png");
    if(!ret){
        qDebug()<<"游戏背景加载失败";
        return;
    }
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void PlayScene::generateMap()
{
    //随机生成地雷
    QVector<int> generation_mine;
    QVector<int> tmp;

    for(int i=0;i < row * col; i++){  //先统一生成地雷
        if(i<numMine)
            generation_mine.push_back(-1);
        else
            generation_mine.push_back(0);
    }

    //打乱地雷布局
    std::random_shuffle(generation_mine.begin(), generation_mine.end());

    //变成二维数组，外面包一层值为-5的占位数，方便统计
    int count=0;
    QVector<int> a(col+2, -5);
    temp.push_back(a);
    tmp.push_back(-5);
    for(int i=0;i<row * col;i++)
    {
        if(count==col)
        {
            count=0;
            tmp.push_back(-5);
            temp.push_back(tmp);
            tmp.clear();
            tmp.push_back(-5);
        }
        tmp.push_back(generation_mine[i]);
        count++;
    }
    tmp.push_back(-5);
    temp.push_back(tmp);
    tmp.clear();
    temp.push_back(a);

    //统计地雷
    for(int i=1;i<temp.size()-1;i++)
    {
        for(int j=1;j<temp[0].size()-1;j++)
        {
            if(temp[i][j]!=-1)
            {
                if(temp[i-1][j-1]==-1)temp[i][j]++;
                if(temp[i-1][j]==-1)temp[i][j]++;
                if(temp[i-1][j+1]==-1)temp[i][j]++;
                if(temp[i][j-1]==-1)temp[i][j]++;
                if(temp[i][j+1]==-1)temp[i][j]++;
                if(temp[i+1][j-1]==-1)temp[i][j]++;
                if(temp[i+1][j]==-1)temp[i][j]++;
                if(temp[i+1][j+1]==-1)temp[i][j]++;
            }
        }
    }
}

void PlayScene::screenClicked()
{
    if(isOver){//如果游戏结束就拦截信号
        return;
    }
    Screen *screen = qobject_cast<Screen *>(sender());  //获取发送信号的对象
    if(mineArea[screen->posX][screen->posY]->type==-1)  //踩雷
    {
        //打开全部遮挡，显示全部内容
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                mineArea[i][j]->show();
                screenArea[i][j]->hide();
            }
        }
        this->isOver = true;
        qDebug()<<"失败";
        //弹出失败画面
    }
    else if(mineArea[screen->posX][screen->posY]->type==0)  //选中的是空白
    {
        Screen *temp = NULL;
        q.push_back(screen);
        while(!q.isEmpty())  //BFS扩展显示
        {
            temp = q.dequeue();
            if(mineArea[temp->posX][temp->posY]->type>0){  //如果取出的是数字那就仅显示自身
                cur++;
                qDebug()<<cur;
                temp->hide();
                mineArea[temp->posX][temp->posY]->show();
                continue;
            }
            //如果取出的是空白
            temp->hide();
            mineArea[temp->posX][temp->posY]->show();
            cur++;
            //如果周围方格存在，是遮挡的，是没遍历过的，内容是空白，就放进队列里
            if(temp->posX-1>=0 && temp->posY-1>=0 && !screenArea[temp->posX-1][temp->posY-1]->isTraveled && screenArea[temp->posX-1][temp->posY-1]->isVisible() && mineArea[temp->posX-1][temp->posY-1]->type!=-1){
                q.push_back(screenArea[temp->posX-1][temp->posY-1]);
                screenArea[temp->posX-1][temp->posY-1]->isTraveled = true;

            }
            if(temp->posX-1>=0 && temp->posY>=0 && !screenArea[temp->posX-1][temp->posY]->isTraveled && screenArea[temp->posX-1][temp->posY]->isVisible() && mineArea[temp->posX-1][temp->posY]->type!=-1){
                q.push_back(screenArea[temp->posX-1][temp->posY]);
                screenArea[temp->posX-1][temp->posY]->isTraveled = true;
            }
            if(temp->posX-1>=0 && temp->posY+1<col && !screenArea[temp->posX-1][temp->posY+1]->isTraveled && screenArea[temp->posX-1][temp->posY+1]->isVisible() && mineArea[temp->posX-1][temp->posY+1]->type!=-1){
                q.push_back(screenArea[temp->posX-1][temp->posY+1]);
                screenArea[temp->posX-1][temp->posY+1]->isTraveled = true;
            }

            if(temp->posX>=0 && temp->posY-1>=0 && !screenArea[temp->posX][temp->posY-1]->isTraveled && screenArea[temp->posX][temp->posY-1]->isVisible() && mineArea[temp->posX][temp->posY-1]->type!=-1){
                q.push_back(screenArea[temp->posX][temp->posY-1]);
                screenArea[temp->posX][temp->posY-1]->isTraveled = true;
            }
            if(temp->posX>=0 && temp->posY+1<col && !screenArea[temp->posX][temp->posY+1]->isTraveled && screenArea[temp->posX][temp->posY+1]->isVisible() && mineArea[temp->posX][temp->posY+1]->type!=-1){
                q.push_back(screenArea[temp->posX][temp->posY+1]);
                screenArea[temp->posX][temp->posY+1]->isTraveled = true;
            }

            if(temp->posX+1<row && temp->posY-1>=0 && !screenArea[temp->posX+1][temp->posY-1]->isTraveled && screenArea[temp->posX+1][temp->posY-1]->isVisible() && mineArea[temp->posX+1][temp->posY-1]->type!=-1){
                q.push_back(screenArea[temp->posX+1][temp->posY-1]);
                screenArea[temp->posX+1][temp->posY-1]->isTraveled = true;
            }
            if(temp->posX+1<row && temp->posY>=0 && !screenArea[temp->posX+1][temp->posY]->isTraveled && screenArea[temp->posX+1][temp->posY]->isVisible() && mineArea[temp->posX+1][temp->posY]->type!=-1){
                q.push_back(screenArea[temp->posX+1][temp->posY]);
                screenArea[temp->posX+1][temp->posY]->isTraveled = true;
            }
            if(temp->posX+1<row && temp->posY+1<col && !screenArea[temp->posX+1][temp->posY+1]->isTraveled && screenArea[temp->posX+1][temp->posY+1]->isVisible() && mineArea[temp->posX+1][temp->posY+1]->type!=-1){
                q.push_back(screenArea[temp->posX+1][temp->posY+1]);
                screenArea[temp->posX+1][temp->posY+1]->isTraveled = true;
            }
        }
    }
    else{
        cur++;
        if(cur==row*col-numMine) //翻开的遮挡数量等于总格子减去雷数就胜利
        {
            //胜利画面
            this->isOver = true;
            qDebug()<<"胜利";
        }

        mineArea[screen->posX][screen->posY]->show(); //显示信息层
        screen->hide();  //隐藏遮挡层
    }
}


