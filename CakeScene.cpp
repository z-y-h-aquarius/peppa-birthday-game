#include "CakeScene.h"
#include "PuzzleDialog.h"
#include <QGraphicsScene>
#include <QGraphicsDropShadowEffect>
#include <QTimer>
#include <QApplication>

CakeScene::CakeScene(GameScene *gameScene, QWidget *parent)
    : QWidget(parent),
    m_gameScene(gameScene)
{
    //待烤蛋糕
    m_unbakedCakeImg = new QGraphicsPixmapItem;
    QPixmap unbakedcakePix("://image/unbakedcake.png");
    unbakedcakePix = unbakedcakePix.scaled(382,300,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    m_unbakedCakeImg->setPixmap(unbakedcakePix);
    m_unbakedCakeImg->setPos(360,140);

    // 立体阴影
    QGraphicsDropShadowEffect* cakeShadow = new QGraphicsDropShadowEffect;
    cakeShadow->setBlurRadius(22);
    cakeShadow->setOffset(1,1);
    cakeShadow->setColor(QColor(0,0,0,180));
    m_unbakedCakeImg->setGraphicsEffect(cakeShadow);

    m_gameScene->m_scene.addItem(m_unbakedCakeImg);

    //佩奇提示框
    m_tipPeppa = new PeppaDialog;
    m_tipPeppa->setText("接下来把蛋糕放到烤箱里烤烤吧~");

    //加到GameScene的场景里
    m_gameScene->m_scene.addItem(m_tipPeppa);


    //蛋糕放入烤箱的图片
    m_cakeInOvenImg = new QGraphicsPixmapItem;
    QPixmap ovenPix("://image/cakeinoven.png");
    ovenPix = ovenPix.scaled(180,70,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    m_cakeInOvenImg->setPixmap(ovenPix);
    m_cakeInOvenImg->setPos(150,415);
    m_gameScene->m_scene.addItem(m_cakeInOvenImg);
    m_cakeInOvenImg->hide();

    //烤箱锁
    m_ovenLockBtn = new GraphicsImageButton("://image/ovenlock.png","",21,30);
    m_ovenLockBtn->setPos(150,410);
    m_ovenLockBtn->setZValue(112);
    m_gameScene->m_scene.addItem(m_ovenLockBtn);

    connect(m_ovenLockBtn, &GraphicsImageButton::clicked, this,&CakeScene::onOvenLockClicked);

    //烤好的蛋糕
    m_cakeImg = new QGraphicsPixmapItem;
    QPixmap cakePix("://image/cake.png");
    cakePix = cakePix.scaled(466,300,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    m_cakeImg->setPixmap(cakePix);
    m_cakeImg->setPos(400,200);
    m_gameScene->m_scene.addItem(m_cakeImg);
    m_cakeImg->hide();

    //蜡烛
    m_candlesBtn = new GraphicsImageButton("://image/candles.png","",43,85);
    m_candlesBtn->setPos(860,220);
    m_gameScene->m_scene.addItem(m_candlesBtn);
    connect(m_candlesBtn, &GraphicsImageButton::clicked, this,&CakeScene::onCandlesClicked);
    m_candlesBtn->hide();
    m_candlesBtn->setZValue(120);

    //蛋糕成品
    m_finalCakeImg = new QGraphicsPixmapItem;
    QPixmap finalCakePix("://image/finalcake.png");
    finalCakePix = finalCakePix.scaled(423,300,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    m_finalCakeImg->setPixmap(finalCakePix);
    m_finalCakeImg->setPos(400,200);
    m_gameScene->m_scene.addItem(m_finalCakeImg);
    m_finalCakeImg->hide();
}

//点击烤箱锁
void CakeScene::onOvenLockClicked()
{
    if(m_ovenlockSolved)
        return;

    //显示题目
    PuzzleDialog dlg("://image/ovenpuzzle.png","://image/oventip.png","waiter","://image/ovenanswer.png");

    if(dlg.exec() == QDialog::Accepted){
        m_ovenlockSolved = true;
        m_cakeInOvenImg->show();

        QTimer::singleShot(5000,this,[=]() {
            m_cakeInOvenImg->hide();
            m_cakeImg->show();
            m_candlesBtn->show();
            m_tipPeppa = new PeppaDialog;
            m_tipPeppa->setText("烤好啦，现在我们需要插上一些蜡烛~");
            m_gameScene->m_scene.addItem(m_tipPeppa);
        });
    }
}

//点击蜡烛
void CakeScene::onCandlesClicked()
{
    m_cakeImg->hide();
    m_candlesBtn->hide();
    m_finalCakeImg->show();
    //最终收尾提示
    m_tipPeppa = new PeppaDialog;
    m_tipPeppa->setText("蛋糕完成啦，我们一起去给猪妈妈过生日吧！");
    m_gameScene->m_scene.addItem(m_tipPeppa);

    //标记：现在是最后一步提示了
    m_isFinal = true;
}

//点击任意处继续
void CakeScene::mousePressEvent(QMouseEvent *event)
{
    if (m_tipPeppa) {
        //先从场景移除，再删除，否则会残留图形
        m_gameScene->m_scene.removeItem(m_tipPeppa);
        delete m_tipPeppa;
        m_tipPeppa = nullptr;

        //最后播放视频
        if(m_isFinal)
        {
            //播放结局视频前，关闭BGM
            m_gameScene->closeGameBGM();

            //播放结束视频，完成结束流程
            playVideo("endVideo.mp4", &CakeScene::EndVideoFinished);
        }
    }

    if(m_unbakedCakeImg){
        m_unbakedCakeImg->hide();
    }

    QWidget::mousePressEvent(event);
}

//播放结束视频
void CakeScene::playVideo(const QString &videoPath, void (CakeScene::*finishedSlot)())
{
    //创建场景视频图元
    m_videoItem = new QGraphicsVideoItem;
    //居中、全屏显示
    m_videoItem->setSize(QSizeF(m_gameScene->m_scene.width(), m_gameScene->m_scene.height()));
    m_videoItem->setScale(1.02);
    m_videoItem->setPos(-15,0);
    m_videoItem->setZValue(9999); // 层级设到最高，盖住所有游戏元素

    //绑定播放器
    m_player = new QMediaPlayer(this);
    m_audio = new QAudioOutput(this);
    m_player->setAudioOutput(m_audio);
    m_audio->setVolume(1.0);
    m_player->setVideoOutput(m_videoItem);

    //把视频图元加到场景里
    m_gameScene->m_scene.addItem(m_videoItem);

    //开始播放
    m_player->setSource(QUrl::fromLocalFile(videoPath));
    m_player->play();

    //视频结束自动清理+回调
    connect(m_player, &QMediaPlayer::mediaStatusChanged, this, [=](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia)
        {
            // 先暂停，锁住最后一帧
            m_player->pause();

            // 延迟 600ms 再销毁，补齐丢失的后半秒
            QTimer::singleShot(600, this, [=](){
                m_gameScene->m_scene.removeItem(m_videoItem);
                m_videoItem->deleteLater();
                m_player->deleteLater();
                m_audio->deleteLater();
                m_videoItem = nullptr;
                m_player = nullptr;
                m_audio = nullptr;

                (this->*finishedSlot)();
            });
        }
    });
}

void CakeScene::EndVideoFinished()
{
    showEndCoverPage();
}

void CakeScene::showEndCoverPage()
{
    m_endAudio = new QMediaPlayer(this);
    m_endAudioOut = new QAudioOutput(this);
    m_endAudio->setAudioOutput(m_endAudioOut);
    m_endAudio->setSource(QUrl::fromLocalFile("endBGM.mp3"));
    m_endAudioOut->setVolume(0.6);
    m_endAudio->play();
    connect(m_endAudio, &QMediaPlayer::mediaStatusChanged, this, [=](QMediaPlayer::MediaStatus st){
        if(st == QMediaPlayer::EndOfMedia)
            m_endAudio->stop();
    });

    //结束背景图
    m_endBgItem = new QGraphicsPixmapItem;
    QPixmap endBg("://image/end_background.png");
    endBg = endBg.scaled(m_gameScene->m_scene.width(), m_gameScene->m_scene.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    m_endBgItem->setPixmap(endBg);
    m_endBgItem->setPos(0,0);
    m_endBgItem->setZValue(999); //背景层级设为999

    //退出按钮
    m_endExitBtn = new GraphicsImageButton("://image/start_button.png","结束游戏",187,67);
    m_endExitBtn->setPos(1020,510);
    m_endExitBtn->setZValue(1001); //按钮层级最高，设为1001，确保能被点到

    //把所有图元加到场景里
    m_gameScene->m_scene.addItem(m_endBgItem);
    m_gameScene->m_scene.addItem(m_endExitBtn);

    //退出点击
    connect(m_endExitBtn, &GraphicsImageButton::clicked, this, [=](){
        if(m_endAudio)
        {
            m_endAudio->stop();
            m_endAudio->deleteLater();
            m_endAudioOut->deleteLater();
            m_endAudio = nullptr;
            m_endAudioOut = nullptr;
        }

        QApplication::quit();
    });
}
