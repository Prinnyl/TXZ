#include "gameplay.h"
#include <QDebug>


//GamePlay::GamePlay(QWidget *parent) : QWidget(parent)
//{

//}

GamePlay::GamePlay(int level)
{
    this->myLevel = level;

    //固定窗口大小
    this->setFixedSize(800, 450);

    //让上下左右能动,刚进入界面时需点击一下界面
    setFocusPolicy(Qt::StrongFocus);

    //初始化关卡
    MyData myGaneData;
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            this->gameArray[i][j] = myGaneData.dataSelect[level][i][j];
        }
    }

    //上一关
    buttonLast = new MyPushButton(":/pixmap/Image/last.png", 2);
    buttonLast->setParent(this);
    buttonLast->move(45, 100);
    //qDebug() << level;
    if(myLevel < 2)
    {
        buttonLast->setEnabled(false);
    }
    connect(buttonLast, &MyPushButton::clicked, [=](){
        buttonLast->zoom1();
        buttonLast->zoom2();
        QTimer::singleShot(200, this, [=](){
            myPlays = new GamePlay(myLevel - 1);
            myPlays->setGeometry(this->geometry());
            myPlays->show();
            delete this;
        });
    });

    //下一关
    buttonNext = new MyPushButton(":/pixmap/Image/next.png", 2);
    buttonNext->setParent(this);
    buttonNext->move(45, 200);
    //qDebug() << level;
    //buttonNext->setEnabled(false);
    connect(buttonNext, &MyPushButton::clicked, [=](){
        buttonNext->zoom1();
        buttonNext->zoom2();
        QTimer::singleShot(200, this, [=](){
            if(myLevel > 8)
            {
                QMessageBox::warning(this, "大佬！！！", "可以了，你已经很大佬了，已经很多人达不到你千分之一的水平了(没有了呢，就这么几关呢ˋ( ° ▽、° ) )");
                return;
            }
            myPlays = new GamePlay(myLevel + 1);
            myPlays->setGeometry(this->geometry());
            myPlays->show();
            delete this;
        });
    });
    buttonNext->hide();

    //重新开始
    buttonAgain = new MyPushButton(":/pixmap/Image/again.png", 2);
    buttonAgain->setParent(this);
    buttonAgain->move(45, 200);
    //qDebug() << level;
    connect(buttonAgain, &MyPushButton::clicked, [=](){
        buttonAgain->zoom1();
        buttonAgain->zoom2();
        QTimer::singleShot(200, this, [=](){
            MyData myGaneData;
            for(int i = 0; i < 10; i++)
            {
                for(int j = 0; j < 10; j++)
                {
                    this->gameArray[i][j] = myGaneData.dataSelect[level][i][j];
                }
            }
            update();
        });
    });
    //buttonAgain->hide();

    //退出游戏
    buttonClose = new MyPushButton(":/pixmap/Image/close.png", 2);
    buttonClose->setParent(this);
    buttonClose->move(45, 300);
    connect(buttonClose, &MyPushButton::clicked, this, [=](){
        buttonClose->zoom1();
        buttonClose->zoom2();
        QTimer::singleShot(200, this, [=](){
            this->close();
        });
    });

    //标题
    lableTitle = new QLabel(this);
    lableTitle->setText(QString("第%1关").arg(myLevel));
    lableTitle->setFixedSize(150, 38);
    lableTitle->move(75, 25);
    lableTitle->setStyleSheet("font-size : 38px;"
                              "font-family : 华文行楷;"
                              "color : rgba(234, 44, 235, 1);");
    lableTitle->setAlignment(Qt::AlignCenter);

    //胜利
    lableWin = new QLabel(this);
    lableWin->setText(QString("胜利啦！"));
    lableWin->setFixedSize(500, 200);
    lableWin->move(320, 140);
    lableWin->setStyleSheet("font-size : 128px;"
                              "font-family : 华文行楷;"
                              "color : rgba(0, 255, 0, 1);");
    lableWin->setAlignment(Qt::AlignCenter);
    lableWin->hide();

}

void GamePlay::paintEvent(QPaintEvent *)
{
    //背景
    QPainter groundPainter(this);
    groundPainter.drawPixmap(0, 0, QPixmap(":/pixmap/Image/ground.png"));


    //游戏
    gamePainter = new QPainter(this);
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            QString stringImage;
            //0空地,1墙,2人物,4箱子,7终点,9人物加终点,11箱子加终点
            if(this->gameArray[i][j] == 0)
            {
                stringImage = ":/pixmap/Image/sky.png";
            }
            else if(this->gameArray[i][j] == 1)
            {
                stringImage = ":/pixmap/Image/wall.png";
            }
            else if(this->gameArray[i][j] == 2)
            {
                stringImage = ":/pixmap/Image/people.png";
                mouseX = i;
                mouseY = j;
            }
            else if(this->gameArray[i][j] == 4)
            {
                stringImage = ":/pixmap/Image/case.png";
            }
            else if(this->gameArray[i][j] == 7)
            {
                stringImage = ":/pixmap/Image/end.png";
            }
            else if(this->gameArray[i][j] == 9)
            {
                stringImage = ":/pixmap/Image/peopleend.png";
            }
            else if(this->gameArray[i][j] == 11)
            {
                stringImage = ":/pixmap/Image/win.png";
            }
            gamePainter->drawPixmap(320 + i *40, 25 + j *40, QPixmap(stringImage));
        }
    }
    delete gamePainter;
}

void GamePlay::keyPressEvent(QKeyEvent *ev)
{
    if(isWin == true)
    {
        return;
    }
    switch(ev->key())
    {
    case Qt::Key_Up:
    case Qt::Key_W:
        PressUp();
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        PressDown();
        break;
    case Qt::Key_Left:
    case Qt::Key_A:
        PressLeft();
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        pressRight();
        break;
    }
//    qDebug() <<gameArray[mouseX][mouseY] <<gameArray[mouseX][mouseY + 1]
//               <<gameArray[mouseX][mouseY - 1] <<gameArray[mouseX + 1][mouseY]
//                 <<gameArray[mouseX - 1][mouseY];
    gameWin();
    update();
}

void GamePlay::PressUp()
{
    //人上空地,终点
    if(gameArray[mouseX][mouseY - 1] == 0 || gameArray[mouseX][mouseY - 1] == 7)
    {
        gameArray[mouseX][mouseY] = gameArray[mouseX][mouseY] - 2;
        gameArray[mouseX][mouseY - 1] = gameArray[mouseX][mouseY - 1] + 2;
        mouseY--;
    }
    //人上箱子,箱子上空地,终点
    else if(gameArray[mouseX][mouseY - 1] == 4 || gameArray[mouseX][mouseY - 1] == 11)
    {
        if(gameArray[mouseX][mouseY - 2] == 0 || gameArray[mouseX][mouseY - 2] == 7)
        {
            gameArray[mouseX][mouseY] = gameArray[mouseX][mouseY] - 2;
            gameArray[mouseX][mouseY - 1] = gameArray[mouseX][mouseY - 1] - 2;
            gameArray[mouseX][mouseY - 2] = gameArray[mouseX][mouseY - 2] + 4;
            mouseY--;
        }
    }
}

void GamePlay::PressDown()
{
    //人下空地,终点
    if(gameArray[mouseX][mouseY + 1] == 0 || gameArray[mouseX][mouseY + 1] == 7)
    {
        gameArray[mouseX][mouseY] = gameArray[mouseX][mouseY] - 2;
        gameArray[mouseX][mouseY + 1] = gameArray[mouseX][mouseY + 1] + 2;
        mouseY++;
    }
    //人下箱子,箱子下空地,终点
    else if(gameArray[mouseX][mouseY + 1] == 4 || gameArray[mouseX][mouseY + 1] == 11)
    {
        if(gameArray[mouseX][mouseY + 2] == 0 || gameArray[mouseX][mouseY + 2] == 7)
        {
            gameArray[mouseX][mouseY] = gameArray[mouseX][mouseY] - 2;
            gameArray[mouseX][mouseY + 1] = gameArray[mouseX][mouseY + 1] - 2;
            gameArray[mouseX][mouseY + 2] = gameArray[mouseX][mouseY + 2] + 4;
            mouseY++;
        }
    }
}

void GamePlay::PressLeft()
{
    //人左空地,终点
    if(gameArray[mouseX - 1][mouseY] == 0 || gameArray[mouseX - 1][mouseY] == 7)
    {
        gameArray[mouseX][mouseY] = gameArray[mouseX][mouseY] - 2;
        gameArray[mouseX - 1][mouseY] = gameArray[mouseX - 1][mouseY] + 2;
        mouseX--;
    }
    //人左箱子,箱子左空地,终点
    else if(gameArray[mouseX - 1][mouseY] == 4 || gameArray[mouseX - 1][mouseY] == 11)
    {
        if(gameArray[mouseX - 2][mouseY] == 0 || gameArray[mouseX - 2][mouseY] == 7)
        {
            gameArray[mouseX][mouseY] = gameArray[mouseX][mouseY] - 2;
            gameArray[mouseX - 1][mouseY] = gameArray[mouseX - 1][mouseY] - 2;
            gameArray[mouseX - 2][mouseY] = gameArray[mouseX - 2][mouseY] + 4;
            mouseX--;
        }
    }
}

void GamePlay::pressRight()
{
    //人右空地,终点
    if(gameArray[mouseX + 1][mouseY] == 0 || gameArray[mouseX + 1][mouseY] == 7)
    {
        gameArray[mouseX][mouseY] = gameArray[mouseX][mouseY] - 2;
        gameArray[mouseX + 1][mouseY] = gameArray[mouseX + 1][mouseY] + 2;
        mouseX++;
    }
    //人右箱子,箱子右空地,终点
    else if(gameArray[mouseX + 1][mouseY] == 4 || gameArray[mouseX + 1][mouseY] == 11)
    {
        if(gameArray[mouseX + 2][mouseY] == 0 || gameArray[mouseX + 2][mouseY] == 7)
        {
            gameArray[mouseX][mouseY] = gameArray[mouseX][mouseY] - 2;
            gameArray[mouseX + 1][mouseY] = gameArray[mouseX + 1][mouseY] - 2;
            gameArray[mouseX + 2][mouseY] = gameArray[mouseX + 2][mouseY] + 4;
            mouseX++;
        }
    }
}

//游戏胜利
void GamePlay::gameWin()
{
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if(this->gameArray[i][j] == 4)
            {
                return;
            }
        }
    }
    isWin = true;
    lableWin->show();
    buttonAgain->hide();
    buttonNext->show();
}
