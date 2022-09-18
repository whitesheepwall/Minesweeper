#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QPaintEvent>
#include "mymap.h"
#include "screen.h"
#include <QQueue>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int x,int y, int n = 0);

    void paintEvent(QPaintEvent*);

    void generateMap();

    void screenClicked();

    int row;
    int col;
    int numMine; //地雷个数
    int cur = 0;  //当前翻开遮挡的数量
    bool isOver = false;

    QQueue<Screen *> q;
    QVector<QVector<MyMap*>> mineArea;
    QVector<QVector<Screen *>> screenArea;
    QVector<QVector<int>> temp;


signals:
    void playSceneClose();
    void restartGame();

};

#endif // PLAYSCENE_H
