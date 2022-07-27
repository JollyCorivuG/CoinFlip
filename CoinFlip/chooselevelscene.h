#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <playscene.h>
class ChooseLevelscene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelscene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    PlayScene *play = NULL;
signals:
    void choosesceneback();

public slots:
};

#endif // CHOOSELEVELSCENE_H
