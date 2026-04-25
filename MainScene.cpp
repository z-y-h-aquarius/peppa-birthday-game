#include "MainScene.h"
#include "ui_MainScene.h"
#include "GraphicsImageButton.h"
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QFont>
#include <QMessageBox>

MainScene::MainScene(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    this->setFixedSize(1235,700);//固定窗口大小
    mGameView.setSceneRect(QRect(0,0,1235,700));//视图大小
    mScene.setSceneRect(QRect(0,0,1235,700));//场景大小

    QPixmap originalBg("://image/start_background.png");
    QPixmap originalPeppa("://image/peppa.png");

    //缩放图片
    QPixmap scaledBg = originalBg.scaled(1235,700,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    mBackGround1.setPixmap(scaledBg);

    QPixmap scaledPeppa = originalPeppa.scaled(220,275,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    mPeppa.setPixmap(scaledPeppa);
    mPeppa.setPos(100,520);

    //将图片添加到场景
    mScene.addItem(&mBackGround1);
    mScene.addItem(&mPeppa);


    mGameView.setScene(&mScene);//设置视图场景
    mGameView.setParent(this);//设置视图场景
    mGameView.setGeometry(0,0,1237,702);
    mGameView.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mGameView.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //创建按钮
    GraphicsImageButton * startBtn = new GraphicsImageButton("://image/start_button.png","开始游戏",187,67);
    GraphicsImageButton * infoBtn  = new GraphicsImageButton("://image/start_button.png","关于游戏",187,67);
    GraphicsImageButton * quitBtn  = new GraphicsImageButton("://image/start_button.png","结束游戏",187,67);
    //将按钮添加到场景
    mScene.addItem(startBtn);
    mScene.addItem(infoBtn);
    mScene.addItem(quitBtn);

    //按钮布局
    int marginRight = 40;
    int marginBottom = 67;
    int spacing = 27;
    int btnWidth = 187;
    int btnHeight = 67;

    int btnX = this->width() - marginRight - btnWidth;
    int topBtnY    = this->height() - marginBottom - 3*btnHeight - 2*spacing;
    int middleBtnY = topBtnY + btnHeight + spacing;
    int bottomBtnY = middleBtnY + btnHeight + spacing;

    startBtn->setPos(btnX, topBtnY);
    infoBtn->setPos(btnX, middleBtnY);
    quitBtn->setPos(btnX, bottomBtnY);

    // 开始游戏
    connect(startBtn, &GraphicsImageButton::clicked, this, &MainScene::startGame);

    //关于游戏
    connect(infoBtn, &GraphicsImageButton::clicked, this, [=]() {
        QMessageBox msgBox;
        msgBox.setWindowTitle("关于游戏");
        QString info = R"(
游戏名称：寻宝游戏小猪佩奇版之猪妈妈的生日惊喜

游戏简介：
    这是一款以小猪佩奇为主题的休闲解谜小游戏，玩家将跟随剧情指引，寻找道具、完成简单谜题，一步步完成蛋糕制作的全部流程,最终给猪妈妈准备一场温馨的生日惊喜。
    游戏画风轻松可爱，童趣柔和，操作简单易懂，最终见证完整生日蛋糕完成，收获满满的温馨与治愈感。

操作说明：
• 鼠标点击场景中的物品进行互动
• 收集关键道具解锁新剧情
• 根据提示完成小任务即可通关)";

        msgBox.setText(info);

        //给QMessageBox的文本控件手动设置左右边距
        QLabel *textLabel = msgBox.findChild<QLabel *>("qt_msgbox_label");
        if (textLabel) {
            textLabel->setContentsMargins(0,0,15,0); // 左、上、右、下
            textLabel->setWordWrap(true); // 强制自动换行
        }

        QFont font("微软雅黑",12);
        msgBox.setFont(font);
        msgBox.setMinimumWidth(740);
        msgBox.setMinimumHeight(510);
        msgBox.move(this->geometry().center() - msgBox.rect().center());

        msgBox.exec();
    });

    // 退出游戏
    connect(quitBtn, &GraphicsImageButton::clicked, this, [=]() {
        this->close();
    });

    mGameView.show();
}

MainScene::~MainScene()
{
    delete ui;
}

void MainScene::startGame()
{
    //关闭开始界面
    this->close();

    //打开游戏界面
    GameScene* game = new GameScene;
    game->show();
}
