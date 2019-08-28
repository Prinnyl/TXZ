#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QPainter>
#include <QTimer>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    //固定窗口大小
    this->setFixedSize(800, 450);

    //开始游戏
    buttonStart = new MyPushButton(":/pixmap/Image/start.png");
    buttonStart->setParent(this);
    buttonStart->move(this->width() * 0.5 - buttonStart->width() * 0.5, 120);
    connect(buttonStart, &MyPushButton::clicked, [=](){
        buttonStart->zoom1();
        buttonStart->zoom2();
        QTimer::singleShot(200, this, [=](){
            this->hide();
            myPlays = new GamePlay(1);
            myPlays->setGeometry(this->geometry());
            myPlays->show();
        });
    });

    //离开游戏
    buttonClose = new MyPushButton(":/pixmap/Image/close.png");
    buttonClose->setParent(this);
    buttonClose->move(this->width() * 0.5 - buttonStart->width() * 0.5, 250);
    connect(buttonClose, &MyPushButton::clicked, [=](){
        buttonClose->zoom1();
        buttonClose->zoom2();
        QTimer::singleShot(200, this, [=](){
            this->close();
        });
    });

}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::paintEvent(QPaintEvent *)
{
    //背景
    QPainter groundPainter(this);
    groundPainter.drawPixmap(0, 0, QPixmap(":/pixmap/Image/ground.png"));
}
