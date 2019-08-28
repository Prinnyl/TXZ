#ifndef MAINBUTTON_H
#define MAINBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MainButton(QWidget *parent = nullptr);
    MyPushButton(QString imageA);
    MyPushButton(QString imageA, int B);
    //弹跳特效
    void zoom1();
    void zoom2();

signals:

public slots:
};

#endif // MAINBUTTON_H
