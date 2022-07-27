#include "mycoin.h"
#include <QPixmap>
MyCoin::MyCoin(QString btnImg) {
    QPixmap pix;
    pix.load(btnImg);

    //基础设置
    this->setFixedSize(pix.width(), pix.height());;
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(), pix.height()));

    //初始化定时器的对象
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);
    connect(timer1, &QTimer::timeout, [=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->mn++);
        pix.load(str);
        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));
        //判断，如果翻完了，将mn置为1
        if (this->mn > this->mx) {
            this->mn = 1;
            this->isanimation = false;
            timer1->stop();
        }
    });
    connect(timer2, &QTimer::timeout, [=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->mx--);
        pix.load(str);
        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));
        //判断，如果翻完了，将mx置为1
        if (this->mx < this->mn) {
            this->mx = 8;
            this->isanimation = false;
            timer2->stop();
        }
    });
}
//改变金币的正方面的标志
void MyCoin::changeFg() {
    if (this->fg) {
        //正面翻反面的定时器
        timer1->start(30);
        this->isanimation = true;
        this->fg = 0;
    } else {
        timer2->start(30);
        this->isanimation = true;
        this->fg = 1;
    }
}
void MyCoin::mousePressEvent(QMouseEvent *e) {
    if (this->isanimation || this->is_win) {
        return;
    } else {
        return QPushButton::mousePressEvent(e);
    }

}
