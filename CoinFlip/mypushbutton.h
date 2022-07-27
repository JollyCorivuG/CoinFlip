#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QString>
class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = nullptr);
    MyPushButton(QString normalImg, QString pressImg = "");//第一个参数为默认的图片，第二个参数为按下时的图片
    QString normalImgPath;//默认图片的路径
    QString pressImgPath;//按下图片的路径

    //弹起动画
    void up_zoom();//向上弹起
    void down_zoom();//向下弹起

    //重写按钮的按下和释放事件
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:

public slots:
};

#endif // MYPUSHBUTTON_H
