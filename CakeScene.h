#ifndef CAKESCENE_H
#define CAKESCENE_H

#include <QWidget>
#include <QMouseEvent>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QGraphicsVideoItem>
#include "GameScene.h"
#include "QGraphicsPixmapItem"
#include "GraphicsImageButton.h"
#include "PeppaDialog.h"

class CakeScene : public QWidget
{
    Q_OBJECT
public:
    // 构造和ItemManager几乎一样，只是固定传GameScene*
    explicit CakeScene(GameScene *gameScene, QWidget *parent = nullptr);

private:
    // 全局持有GameScene，用来addItem
    GameScene* m_gameScene = nullptr;

    //佩奇提示框
    PeppaDialog * m_tipPeppa = nullptr;

    QGraphicsPixmapItem* m_unbakedCakeImg = nullptr;
    QGraphicsPixmapItem* m_cakeInOvenImg = nullptr;
    QGraphicsPixmapItem* m_cakeImg= nullptr;
    QGraphicsPixmapItem* m_finalCakeImg= nullptr;
    QGraphicsPixmapItem* m_endBgItem;

    GraphicsImageButton* m_ovenLockBtn = nullptr;
    GraphicsImageButton* m_candlesBtn = nullptr;
    GraphicsImageButton* m_endExitBtn = nullptr;

    QMediaPlayer *m_player;
    QAudioOutput *m_audio;

    QGraphicsVideoItem *m_videoItem;

    QMediaPlayer* m_endAudio = nullptr;
    QAudioOutput* m_endAudioOut = nullptr;

    bool m_ovenlockSolved = false;
    bool m_isFinal = false;

    void onOvenLockClicked();
    void onCandlesClicked();
    void playVideo(const QString &videoPath,void(CakeScene::*finishSlot)());
    void EndVideoFinished();
    void showEndCoverPage();

protected:
    void mousePressEvent(QMouseEvent *event) override;

};

#endif // CAKESCENE_H
