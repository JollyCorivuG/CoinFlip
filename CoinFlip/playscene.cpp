#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include <QAction>
#include <QPainter>
#include <mypushbutton.h>
#include <QTimer>
#include <QRect>
#include <QString>
#include <QLabel>
#include <mycoin.h>
#include <dataconfig.h>
#include <QDebug>
#include <QPropertyAnimation>
#include <QSound>
PlayScene::PlayScene(int levelnum) {
    QString str = QString("进入了第%1关").arg(levelnum);
    qDebug() << str;
    this->levelindex = levelnum;
    //初始化关下场景
    this->setFixedSize(320, 588);
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    this->setWindowTitle("翻金币场景");
    //创建菜单栏
    QMenuBar *bar = menuBar();
    setMenuBar(bar);
    QMenu *startMenu = bar->addMenu("开始");
    QAction *quitaction = startMenu->addAction("退出");

    //点击退出，退出游戏
    connect(quitaction, &QAction::triggered, [=](){
        this->close();
    });
    QSound *backsound = new QSound(":/res/BackButtonSound.wav", this);//返回音效
    QSound *flipsound = new QSound(":/res/ConFlipSound.wav", this);//翻金币音效
    QSound *winsound = new QSound(":/res/LevelWinSound.wav", this);//胜利音效
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
            emit this->playsceneback();
        });
    });
    //显示当前的关卡数
    QLabel *label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(18);
    QString str1 = QString("Level:%1").arg(this->levelindex);
    label->setFont(font);
    label->setText(str1);
    label->setGeometry(QRect(30, this->height() - 50, 200, 50));

    //初始化每个关卡的二维数组
    dataConfig config;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->gameArray[i][j] = config.mData[this->levelindex][i][j];
        }
    }
    //胜利图片的设置
    QLabel *winlabel = new QLabel;
    QPixmap pix;
    pix.load(":res/LevelCompletedDialogBg");
    winlabel->setGeometry(0, 0, pix.width(), pix.height());
    winlabel->setPixmap(pix);
    winlabel->setParent(this);
    winlabel->move(this->width() * 0.5 - pix.width() * 0.5, -pix.height());


    //显示金币背景图案
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            QPixmap pix = QPixmap(":/res/BoardNode.png");
            QLabel *label = new QLabel;
            label->setGeometry(QRect(0, 0, pix.width(), pix.height()));
            label->setPixmap(pix);
            label->setParent(this);
            label->move(57 + i * 50 ,200 + j * 50);

            //根据二维数组的值判断金币还是银币
            QString str;
            if (this->gameArray[i][j] == 1) {
                str = ":/res/Coin0001.png";
            } else {
                str = ":/res/Coin0008.png";
            }
            MyCoin *coin = new MyCoin(str);
            coin->setParent(this);
            coin->move(59 + i * 50, 203 + j * 50);
            //初始化属性
            coin->posX = i;
            coin->posY = j;
            coin->fg = this->gameArray[i][j];//1是正面，0是反面
            //存入每个硬币
            this->coins[i][j] = coin;
            connect(coin, &MyCoin::clicked, [=](){
                //翻金币音效
                flipsound->play();
                //将所有的按钮都禁用
                for (int m = 0; m < 4; m++) {
                    for (int k = 0; k < 4; k++) {
                        coins[m][k]->is_win = true;
                    }
                }
                coin->changeFg();
                this->gameArray[i][j] = this->gameArray[i][j] == 1 ? 0 : 1;
                QTimer::singleShot(300, this, [=](){
                    //翻转周围的硬币
                    if (i + 1 <= 3) {
                       coins[i + 1][j]->changeFg();
                       this->gameArray[i + 1][j] = this->gameArray[i + 1][j] == 1 ? 0 : 1;
                    }
                    if (i - 1 >= 0) {
                        coins[i - 1][j]->changeFg();
                        this->gameArray[i - 1][j] = this->gameArray[i - 1][j] == 1 ? 0 : 1;
                    }
                    if (j + 1 <= 3) {
                        coins[i][j + 1]->changeFg();
                        this->gameArray[i][j + 1] = this->gameArray[i][j + 1] == 1 ? 0 : 1;
                    }
                    if (j - 1 >= 0) {
                        coins[i][j - 1]->changeFg();
                        this->gameArray[i][j - 1] = this->gameArray[i][j - 1] == 1 ? 0 : 1;
                    }
                    //当周围硬币翻完之后
                    for (int m = 0; m < 4; m++) {
                        for (int k = 0; k < 4; k++) {
                            coins[m][k]->is_win = false;
                        }
                    }
                    //判断是否胜利
                    this->is_win = true;
                    for (int m = 0; m < 4 && this->is_win; m++) {
                        for (int k = 0; k < 4 && this->is_win; k++) {
                            if (!coins[m][k]->fg) {
                                this->is_win = false;
                            }

                        }
                    }
                    if (this->is_win) {
                        //qDebug() << "胜利了!";
                        winsound->play();
                        for (int m = 0; m < 4 && this->is_win; m++) {
                            for (int k = 0; k < 4 && this->is_win; k++) {
                                coins[m][k]->is_win = true;
                            }
                        }
                        QPropertyAnimation *animation = new QPropertyAnimation(winlabel, "geometry");
                        animation->setDuration(1000);
                        animation->setStartValue(QRect(winlabel->x(), winlabel->y(), winlabel->width(), winlabel->height()));
                        animation->setEndValue(QRect(winlabel->x(), winlabel->y() + 114, winlabel->width(), winlabel->height()));
                        animation->start();
                    }

                });

            });
        }
    }
}
void PlayScene::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
    pix.load(":/res/Title.png");
    //pix = pix.scaled(pix.width() * 0.7, pix.height() * 0.7);
    painter.drawPixmap((this->width() - pix.width()) * 0.5, 30, pix.width(), pix.height(), pix);
}

