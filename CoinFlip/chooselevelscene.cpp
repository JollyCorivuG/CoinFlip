#include "chooselevelscene.h"
#include <QMenuBar>
#include <mypushbutton.h>
#include <QDebug>
#include <QLabel>
#include <QTimer>
#include <QSound>
ChooseLevelscene::ChooseLevelscene(QWidget *parent) : QMainWindow(parent) {
    //配置选择关卡场景
    this->setFixedSize(320, 588);
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    this->setWindowTitle("选择关卡场景");

    //创建菜单栏
    QMenuBar *bar = menuBar();
    setMenuBar(bar);
    QMenu *startMenu = bar->addMenu("开始");
    QAction *quitaction = startMenu->addAction("退出");

    //点击退出，退出游戏
    connect(quitaction, &QAction::triggered, [=](){
        this->close();
    });

    QSound *choosesound = new QSound(":/res/TapButtonSound.wav", this);//选择关卡音效
    QSound *backsound = new QSound(":/res/BackButtonSound.wav", this);//返回音效

    //返回按钮
    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height());

    //点击返回按钮
    connect(backBtn, &MyPushButton::clicked, [=](){
        //播放返回音效
        backsound->play();
        //qDebug() << "点击了返回按钮";
        QTimer::singleShot(500, this, [=](){
            emit this->choosesceneback();
        });
    });

    //创建关卡的按钮
    for (int i = 0; i < 20; i++) {
        MyPushButton *menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        //点击关卡按钮
        connect(menuBtn, &MyPushButton::clicked, [=](){
            //播放音效
            choosesound->play();

            play = new PlayScene(i + 1);
            //让关卡的窗口显示
            play->setGeometry(this->geometry());
            play->show();
            //原窗口隐藏
            this->hide();
            connect(play, &PlayScene::playsceneback, [=](){
                this->setGeometry(play->geometry());
                this->show();
                delete play;
                play = NULL;
            });
        });
        //移动关卡的位置
        menuBtn->move(25 + i % 4 * 70, 130 + i / 4 * 70);
        QLabel *num = new QLabel;
        num->setParent(this);
        num->setFixedSize(menuBtn->width(), menuBtn->height());
        num->setText(QString::number(i + 1));
        num->move(25 + i % 4 * 70, 130 + i / 4 * 70);
        //设置水平居中和垂直居中
        num->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //设置穿透属性
        num->setAttribute(Qt::WA_TransparentForMouseEvents);

    }

}

void ChooseLevelscene::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width() - pix.width()) * 0.5, 30, pix.width(), pix.height(), pix);
}
