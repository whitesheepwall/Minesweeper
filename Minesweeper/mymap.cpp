#include "mymap.h"

//MyMap::MyMap(QWidget *parent)
//    : QWidget{parent}
//{

//}

MyMap::MyMap(QString btnImg)
{
    QPixmap pix;
    bool ret = pix.load(btnImg);
    if(!ret){
        qDebug()<<"地图内容加载失败";
        return;
    }
    this->setFixedSize(pix.width()*0.5,pix.height()*0.5);
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width()*0.5, pix.height()*0.5));
}

void MyMap::changeState()
{

}
