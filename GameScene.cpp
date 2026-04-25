#include "GameScene.h"
#include <QVBoxLayout>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <utility>

GameScene::GameScene(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(1235,700);
    setWindowTitle("猪妈妈的生日惊喜");

    //播放开始视频
    playVideo("startVideo.mp4", &GameScene::StartVideoFinished);
}

//视频播放函数
void GameScene::playVideo(const QString &videoPath, void (GameScene::*finishedSlot)())
{
    // 新建播放器和视频窗口
    m_videoWidget = new QVideoWidget(this);
    m_player = new QMediaPlayer(this);
    m_audio = new QAudioOutput(this);

    m_player->setVideoOutput(m_videoWidget);
    m_player->setAudioOutput(m_audio);
    m_audio->setVolume(1.0);
    m_videoWidget->setAspectRatioMode(Qt::KeepAspectRatioByExpanding);

    // 铺满窗口
    delete layout();
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_videoWidget);
    layout->setContentsMargins(0,0,0,0);
    setLayout(layout);

    // 开始播放
    m_player->setSource(QUrl::fromLocalFile(videoPath));
    m_player->play();

    // 绑定视频结束信号
    connect(m_player, &QMediaPlayer::mediaStatusChanged, this, [=](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) {
            (this->*finishedSlot)();
        }
    });
}

//开启游戏BGM（开场视频结束调用）
void GameScene::openGameBGM()
{
    if(m_bgmPlayer) return;

    m_bgmPlayer = new QMediaPlayer(this);
    m_bgmAudio = new QAudioOutput(this);
    m_bgmPlayer->setAudioOutput(m_bgmAudio);
    m_bgmAudio->setVolume(0.22);

    //你的bgm资源路径
    m_bgmPlayer->setSource(QUrl::fromLocalFile("bgm.mp3"));

    //无限循环
    connect(m_bgmPlayer, &QMediaPlayer::mediaStatusChanged, this,[=]{
        if(m_bgmPlayer->mediaStatus() == QMediaPlayer::EndOfMedia)
        {
            m_bgmPlayer->setPosition(0);
            m_bgmPlayer->play();
        }
    });

    m_bgmPlayer->play();
}

//关闭游戏BGM（结局视频播放前调用）
void GameScene::closeGameBGM()
{
    if(m_bgmPlayer)
    {
        m_bgmPlayer->stop();
        m_bgmPlayer->deleteLater();
        m_bgmPlayer = nullptr;
    }
}

//开始视频播完
void GameScene::StartVideoFinished()
{
    // 清理视频资源
    m_videoWidget->deleteLater();
    m_player->deleteLater();
    m_audio->deleteLater();

    //开场视频播完，开启全程背景音乐
    openGameBGM();

    // 显示游戏基础界面
    delete layout();
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(&m_gameView);
    setLayout(mainLayout);

    m_scene.setSceneRect(0,0,1235,700);
    m_gameView.setScene(&m_scene);
    m_gameView.setStyleSheet("border:none;");//去掉边框
    //关闭滚动条
    m_gameView.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_gameView.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // 加卧室背景图
    QPixmap bgPix("://image/bedroom.png");
    bgPix = bgPix.scaled(1235,700,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    m_scene.addPixmap(bgPix);

    //弹出导引对话框
    m_storyDialog = new QDialog(this);
    m_storyDialog->setWindowTitle("导引");
    m_storyDialog->setFixedSize(550,230);
    m_storyDialog->setModal(true); //模态弹窗，不点按钮不能点后面

    m_storyDialog->move(850,150);

    //弹窗布局
    QVBoxLayout *dialogLayout = new QVBoxLayout(m_storyDialog);
    dialogLayout->setSpacing(27);
    dialogLayout->setContentsMargins(40,40,40,40);

    //导引文字
    QLabel *text = new QLabel("今天是猪妈妈的生日!\n快来和佩奇乔治一起给猪妈妈准备惊喜吧~");
    text->setFont(QFont("微软雅黑",16));
    text->setAlignment(Qt::AlignCenter);

    //去厨房按钮
    QPushButton *goBtn = new QPushButton("去厨房");
    goBtn->setFont(QFont("微软雅黑",12));
    goBtn->setFixedHeight(40);
    connect(goBtn, &QPushButton::clicked, this, &GameScene::onGoToKitchenClicked);

    //把控件加到弹窗
    dialogLayout->addWidget(text);
    dialogLayout->addStretch(); //加弹簧，把按钮顶到下面
    dialogLayout->addWidget(goBtn);

    //显示弹窗
    m_storyDialog->show();
}

//点击去厨房按钮
void GameScene::onGoToKitchenClicked()
{
    //关闭导引弹窗
    m_storyDialog->close();
    m_storyDialog->deleteLater();

    //清空当前场景
    m_scene.clear();

    //换上厨房背景
    QPixmap kitchenBg("://image/kitchen.png");
    kitchenBg = kitchenBg.scaled(1070,700,Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation);
    m_scene.addPixmap(kitchenBg);

    // 右边背包栏背景
    QGraphicsRectItem* bagBg = new QGraphicsRectItem(1070,0,165,700);
    bagBg->setBrush(QColor(245,222,179)); // 浅暖木色
    bagBg->setPen(Qt::NoPen);
    m_scene.addItem(bagBg);

    //延迟一秒，弹出提示框
    QTimer::singleShot(1000,this,[=]() {
        showTipDialog("我们到厨房啦，快来找材料做蛋糕！");
    });

    //道具管理器
    m_itemManager = new ItemManager(this,nullptr);
    m_itemManager->setGeometry(0,0,1235,700);
    m_itemManager->setStyleSheet("background:transparent;");//透明背景，不挡住游戏
    m_scene.addWidget(m_itemManager);

    //循环添加所有道具
    QList<GraphicsImageButton*> allItems = m_itemManager->createAllPuzzleItems();
    for (auto item : std::as_const(allItems)) {
        m_scene.addItem(item);
    }
}

//显示提示框函数
void GameScene::showTipDialog(const QString &text)
{
    m_tipDialog = new PeppaDialog;
    m_tipDialog->setText(text);
    m_scene.addItem(m_tipDialog);
}

void GameScene::mousePressEvent(QMouseEvent *)
{
    // 如果有对话，点击就删掉
    if (m_tipDialog) {
        m_scene.removeItem(m_tipDialog);
        delete m_tipDialog;
        m_tipDialog = nullptr;
        return; // 这次点击只用来关对话，不触发别的
    }
}
