#include "screen.h"

//Screen::Screen(QWidget *parent)
//    : QWidget{parent}
//{

//}

Screen::Screen(QString normalImg)
{
    normalImgPath = normalImg;

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

void Screen::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::RightButton)
    {
        QPixmap pix;
        bool ret;
        if(this->normalImgPath == ":/res/BoardNode.png")
        {
            ret = pix.load(":/res/flag.png");
            if(!ret)
            {
                qDebug()<<"小旗子加载失败";
                return;
            }
            qDebug()<<"变成旗子";
            this->normalImgPath = ":/res/flag.png";
            this->setFixedSize(pix.width()*0.5,pix.height()*0.5);
            this->setStyleSheet("QPushButton{border:0px}");
            this->setIcon(pix);
            this->setIconSize(QSize(pix.width()*0.5,pix.height()*0.5));
        }
        else if (this->normalImgPath == ":/res/flag.png")
        {
            ret = pix.load(":/res/question.png");
            if(!ret)
            {
                qDebug()<<"问号加载失败";
                return;
            }
            qDebug()<<"变成问号";
            this->normalImgPath = ":/res/question.png";
            this->setFixedSize(pix.width()*0.5,pix.height()*0.5);
            this->setStyleSheet("QPushButton{border:0px}");
            this->setIcon(pix);
            this->setIconSize(QSize(pix.width()*0.5,pix.height()*0.5));
        }
        else if (this->normalImgPath == ":/res/question.png")
        {
            ret = pix.load(":/res/BoardNode.png");
            if(!ret)
            {
                qDebug()<<"遮挡物加载失败";
                return;
            }
            qDebug()<<"变成遮挡";
            this->normalImgPath = ":/res/BoardNode.png";
            this->setFixedSize(pix.width()*0.5,pix.height()*0.5);
            this->setStyleSheet("QPushButton{border:0px}");
            this->setIcon(pix);
            this->setIconSize(QSize(pix.width()*0.5,pix.height()*0.5));
        }
    }
    return QPushButton::mouseReleaseEvent(e);
}
