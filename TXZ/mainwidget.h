#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "mypushbutton.h"
#include "gameplay.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    void paintEvent(QPaintEvent *);

private:
    Ui::MainWidget *ui;
    MyPushButton *buttonStart;//开始游戏按钮
    MyPushButton *buttonClose;//退出游戏按钮
    GamePlay *myPlays;//关卡
};

#endif // MAINWIDGET_H
