#include "mylabel.h"

//MyLabel::MyLabel(QWidget *parent)
//    : QWidget{parent}
//{

//}

MyLabel::MyLabel(QString text)
{
    QFont font;
    font.setPointSize(20);

    setFont(font);
    setText(text);
}
