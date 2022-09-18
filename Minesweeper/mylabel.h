#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    //explicit MyLabel(QWidget *parent = nullptr);
    MyLabel(QString text);

signals:

};

#endif // MYLABEL_H
