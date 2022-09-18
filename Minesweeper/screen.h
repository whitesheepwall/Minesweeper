#ifndef SCREEN_H
#define SCREEN_H

#include <QPushButton>
#include <QMouseEvent>

class Screen : public QPushButton
{
    Q_OBJECT
public:
    //explicit Screen(QWidget *parent = nullptr);
    Screen(QString normalImg);

    void mouseReleaseEvent(QMouseEvent*);

    QString normalImgPath;
    int posX;
    int posY;
    bool isTraveled = false;

signals:

};

#endif // SCREEN_H
