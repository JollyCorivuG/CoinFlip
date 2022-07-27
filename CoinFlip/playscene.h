#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <mycoin.h>
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int levelnum);

    int levelindex;//记录是第几关
    void paintEvent(QPaintEvent *);
    int gameArray[4][4];
    MyCoin *coins[4][4];
    bool is_win;//是否胜利
signals:
    void playsceneback();

public slots:
};

#endif // PLAYSCENE_H
