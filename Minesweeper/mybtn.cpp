#include "mybtn.h"
#include <QPropertyAnimation>

//MyBtn::MyBtn(QWidget *parent)
//    : QWidget{parent}
//{

//}

MyBtn::MyBtn(QString normalImg, QString pressedImg)
{
    normalImgPath = normalImg;
    pressImgPath = pressedImg;

    QPixmap pix;
    bool ret = pix.load(normalImg);
    if(!ret){
        qDebug()<<"普通按钮加载失败";
        return;
    }
    //设置按钮大小
    this->setFixedSize(pix.width()*0.5, pix.height()*0.5);
    //设置图片样式
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图片
    this->setIcon(pix);
    //设置图片大小
    this->setIconSize(QSize(pix.width()*0.5,pix.height()*0.5));
}

void MyBtn::zoom1()//向下跳
{
    //创建动画对象
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    //设置动画的时间间隔
    animation->setDuration(100);
    //起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}


void MyBtn::zoom2()//向上跳
{
    //创建动画对象
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    //设置动画的时间间隔
    animation->setDuration(100);
    //起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}

void MyBtn::mousePressEvent(QMouseEvent *e)
{
    if(this->pressImgPath!="") //传入按下图片不为空，说明需要切图
    {
        QPixmap pix;
        bool ret = pix.load(this->pressImgPath);
        if(!ret)
        {
            qDebug()<<"图片加载失败";
            return;
        }
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //让父类执行其他内容
    return QPushButton::mousePressEvent(e);
}

void MyBtn::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->pressImgPath!="") //传入按下图片不为空，说明需要切图
    {
        QPixmap pix;
        bool ret = pix.load(this->normalImgPath);
        if(!ret)
        {
            qDebug()<<"图片加载失败";
            return;
        }
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //让父类执行其他内容
    return QPushButton::mouseReleaseEvent(e);
}
