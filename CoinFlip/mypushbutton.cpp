#include "mypushbutton.h"
#include <QPixmap>
#include <QPropertyAnimation>
#include <QRect>
#include <QPushButton>
MyPushButton::MyPushButton(QString normalImg, QString pressImg) {
    this->normalImgPath = normalImg;
    this->pressImgPath = pressImg;

    QPixmap pix;
    pix.load(normalImgPath);//加载图片

    //设置图片的固定大小
    this->setFixedSize(pix.width(), pix.height());
    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(pix.width(), pix.height()));
}

void MyPushButton::up_zoom() {
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(200);//间隔时间
    //设置起始位置
    animation->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    //设置结束位置
    animation->setEndValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行
    animation->start();
}

void MyPushButton::down_zoom() {
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(200);//间隔时间
    //设置起始位置
    animation->setStartValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));
    //设置结束位置
    animation->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行
    animation->start();
}
void MyPushButton::mousePressEvent(QMouseEvent *e) {
    if (this->pressImgPath != "") {
        QPixmap pix;
        pix.load(this->pressImgPath);//加载图片

        //设置图片的固定大小
        this->setFixedSize(pix.width(), pix.height());
        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(), pix.height()));
    }
    return QPushButton::mousePressEvent(e);
}
void MyPushButton::mouseReleaseEvent(QMouseEvent *e) {
    if (this->pressImgPath != "") {
        QPixmap pix;
        pix.load(this->normalImgPath);//加载图片

        //设置图片的固定大小
        this->setFixedSize(pix.width(), pix.height());
        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(), pix.height()));
    }
    return QPushButton::mouseReleaseEvent(e);
}
