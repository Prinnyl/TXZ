#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <QWidget>
#include <QLabel>
#include "mypushbutton.h"
#include "mydata.h"
#include <QPainter>
#include <QTimer>
#include <QMessageBox>
#include <QKeyEvent>

class GamePlay : public QWidget
{
    Q_OBJECT
public:
    //explicit GamePlay(QWidget *parent = nullptr);
    GamePlay(int level);
    void paintEvent(QPaintEvent *);//背景绘图
    void keyPressEvent(QKeyEvent *ev);//重写按下
    void PressUp();//上
    void PressDown();//下
    void PressLeft();//左
    void pressRight();//右
    void gameWin();//游戏胜利

signals:

public slots:
private:
    int myLevel;//当前关卡
    QLabel *lableGame;//初始化的背景
    GamePlay *myPlays;
    MyPushButton *buttonLast;//上一关
    MyPushButton *buttonNext;//下一关
    MyPushButton *buttonAgain;//重新开始
    MyPushButton *buttonClose;//退出按钮
    QLabel *lableTitle;//标题
    int gameArray[10][10];//保存用数组
    QLabel *lableWin;//胜利显示
    bool isWin = false;
    int mouseX;//计入人物X坐标
    int mouseY;//计入人物Y坐标
    QPainter *gamePainter;//游戏贴图
};

#endif // GAMEPLAY_H
