#ifndef MYBTN_H
#define MYBTN_H

#include <QPushButton>
#include <QMouseEvent>

class MyBtn : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyBtn(QWidget *parent = nullptr);
    MyBtn(QString normalImg, QString pressedImg = "");

    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void zoom1();
    void zoom2();

    QString normalImgPath;
    QString pressImgPath;

signals:

};

#endif // MYBTN_H
