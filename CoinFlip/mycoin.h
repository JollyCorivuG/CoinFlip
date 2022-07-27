#ifndef MYCOIN_H
#define MYCOIN_H

#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QTimer>
class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString btnImg);
    //金币的属性
    int posX;
    int posY;
    bool fg;
    //改变标志
    void changeFg();
    QTimer *timer1;//正面翻反面的定时器
    QTimer *timer2;//反面翻正面的定时器
    int mn = 1;
    int mx = 8;

    //执行动画的标志
    bool isanimation = false;

    void mousePressEvent(QMouseEvent *e);

    bool is_win = false;
signals:

public slots:
};

#endif // MYCOIN_H
