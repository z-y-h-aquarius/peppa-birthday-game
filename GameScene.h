#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "PeppaDialog.h"

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QAudioOutput>
#include <QPushButton>
#include <QLabel>
#include <QDialog>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include "ItemManager.h"

class GameScene : public QWidget
{
    Q_OBJECT
public:
    explicit GameScene(QWidget *parent = nullptr);
    QGraphicsScene  m_scene;

    // 背景音乐
    QMediaPlayer* m_bgmPlayer = nullptr;
    QAudioOutput*  m_bgmAudio  = nullptr;

    void openGameBGM();
    void closeGameBGM();

public slots:
    //视频播完的槽函数
    void StartVideoFinished();
    //点击去厨房按钮
    void onGoToKitchenClicked();

private:
    QMediaPlayer *m_player;
    QVideoWidget *m_videoWidget;
    QAudioOutput *m_audio;

    QGraphicsView   m_gameView;

    //导引弹窗
    QDialog *m_storyDialog;

    //佩奇提示框
    PeppaDialog *m_tipDialog = nullptr;

    //道具管理器
    ItemManager *m_itemManager;

    //视频播放函数
    void playVideo(const QString &videoPath,void(GameScene::*finishSlot)());

    //显示提示框函数
    void showTipDialog(const QString &text);

    //点击关闭提示
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // GAMESCENE_H
