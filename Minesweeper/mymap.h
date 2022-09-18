#ifndef MYMAP_H
#define MYMAP_H

#include <QPushButton>

class MyMap : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyMap(QWidget *parent = nullptr);
    MyMap(QString btnImg);

    int posX;
    int posY;
    int type;
    void changeState();

signals:

};

#endif // MYMAP_H
