#include "mypushbutton.h"
#include <QMessageBox>
#include <QPropertyAnimation>

//MainButton::MainButton(QWidget *parent) : QPushButton(parent)
//{

//}

//自定义按钮
MyPushButton::MyPushButton(QString imageA)
{
    QPixmap pixmapImage;
    bool ret = pixmapImage.load(imageA);
    if(ret == false)
    {
        QMessageBox::warning(this, "错误", "加载按钮图片出错");
        return;
    }
    this->setFixedSize(pixmapImage.width(), pixmapImage.height());
    this->setStyleSheet("QPushButton{border : 0px;}");
    this->setIcon(pixmapImage);
    this->setIconSize(QSize(pixmapImage.width(), pixmapImage.height()));
}

MyPushButton::MyPushButton(QString imageA, int B)
{
    QPixmap pixmapImage;
    bool ret = pixmapImage.load(imageA);
    if(ret == false)
    {
        QMessageBox::warning(this, "错误", "加载按钮图片出错");
        return;
    }
    this->setFixedSize(pixmapImage.width() *0.7, pixmapImage.height() *0.7);
    this->setStyleSheet("QPushButton{border : 0px;}");
    this->setIcon(pixmapImage);
    this->setIconSize(QSize(pixmapImage.width() *0.7, pixmapImage.height() *0.7));
}

//弹跳，下去
void MyPushButton::zoom1()
{
    QPropertyAnimation *myAnimation = new QPropertyAnimation(this, "geometry");
    myAnimation->setDuration(100);
    myAnimation->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    myAnimation->setEndValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));
    myAnimation->setEasingCurve(QEasingCurve::OutBounce);
    myAnimation->start();
}

//弹跳，回来
void MyPushButton::zoom2()
{
    QPropertyAnimation *myAnimation = new QPropertyAnimation(this, "geometry");
    myAnimation->setDuration(100);
    myAnimation->setStartValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));
    myAnimation->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));
    myAnimation->setEasingCurve(QEasingCurve::OutBounce);
    myAnimation->start();
}

