#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include <QPixmap>
#include <mypushbutton.h>
#include <QTimer>
#include <QSound>
MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    //设置窗口的大小
    this->setFixedSize(320, 588);
    //设置图标
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("翻金币主场景");
    //退出按钮
    connect(ui->actionquit, &QAction::triggered,[=](){
        this->close();
    });
    //开始音效
    QSound *startsound = new QSound(":/res/TapButtonSound.wav", this);


    //开始按钮
    MyPushButton *startbtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startbtn->setParent(this);
    startbtn->move(this->width() * 0.5 - startbtn->width() * 0.5, this->height() * 0.65);

    //选择关卡窗口
    choosescene = new ChooseLevelscene;
    //将选择关卡的返回按钮与主场景的显示链接
    connect(choosescene, &ChooseLevelscene::choosesceneback, [=](){
        QTimer::singleShot(500, this, [=](){
            this->setGeometry(choosescene->geometry());
            choosescene->hide();
            this->show();
        });
    });
    //点击开始按钮
    connect(startbtn, &QPushButton::clicked, [=](){
        //播放开始音效
        startsound->play();
        //弹跳动画
        startbtn->up_zoom();
        startbtn->down_zoom();

        //原窗口隐藏，选择窗口弹出
        QTimer::singleShot(500, this, [=](){
            choosescene->setGeometry(this->geometry());
            this->hide();
            choosescene->show();
        });
    });


}

void MainScene:: paintEvent(QPaintEvent *) {
    QPainter painter(this);//设置画家
    QPixmap pix;//图片
    //背景图
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
    //背景图的标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width() * 0.7, pix.height() * 0.7);
    painter.drawPixmap(13, 30, pix);
}
MainScene::~MainScene()
{
    delete ui;
}

