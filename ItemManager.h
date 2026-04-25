#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include <QObject>
#include <QList>
#include "GraphicsImageButton.h"
#include "PeppaDialog.h"
#include <QMouseEvent>
#include <QWidget>

//前向声明，解决循环依赖问题
class GameScene;
class ItemManager : public QWidget
{
    Q_OBJECT
public:
    explicit ItemManager(GameScene *gameScene,QWidget *parent = nullptr);

    //创建所有房间里的可点击物品
    QList<GraphicsImageButton*> createAllPuzzleItems();

private slots:
    //收集类道具
    void onEggClicked();
    void onMilkClicked();
    void onEnvelopeClicked();
    void onButterClicked();
    void onChocolateClicked();
    void onFlourClicked();
    void onRecipeClicked();

    //锁
    void onEggLockClicked();
    void onButterLockClicked();
    void onChocolateLockClicked();
    void onMilkLockClicked();
    void onFlourLockClicked();

    //判断是否开始做蛋糕
    void ifMakeCake();

private:
    QGraphicsRectItem *m_darkBg;
    GraphicsImageButton *m_eggBtn;
    GraphicsImageButton *m_egglockBtn;
    GraphicsImageButton *m_butterBtn;
    GraphicsImageButton *m_butterlockBtn;
    GraphicsImageButton *m_chocolateBtn;
    GraphicsImageButton *m_chocolatelockBtn;
    GraphicsImageButton *m_milkBtn;
    GraphicsImageButton *m_milklockBtn;
    GraphicsImageButton *m_flourBtn;
    GraphicsImageButton *m_flourlockBtn;
    GraphicsImageButton *m_envelopeBtn;
    GraphicsImageButton *m_recipeBtn;
    GraphicsImageButton *m_makeCakeBtn;

    QGraphicsPixmapItem *m_fridgemImg;
    QGraphicsPixmapItem *m_fridgedImg;
    QGraphicsPixmapItem *m_rightCabinet;
    QGraphicsPixmapItem *m_leftCabinet;
    QGraphicsPixmapItem *m_eggPuz;
    QGraphicsPixmapItem *m_box;
    QGraphicsPixmapItem *m_openBox;
    QGraphicsPixmapItem *m_collectDoneImg;

    int bagItemCount = 0;//背包里已经有几个道具

    //佩奇提示框
    PeppaDialog * m_tipPeppa = nullptr;

    GameScene *m_gameScene;

    //标记：锁是否已经被打开
    bool m_egglockSolved = false;
    bool m_butterlockSolved = false;
    bool m_chocolatelockSolved = false;
    bool m_milklockSolved = false;
    bool m_flourlockSolved = false;
    bool m_envelopeClicked = false;

    //标记：道具是否已经被收集
    bool m_eggCollected = false;
    bool m_butterCollected = false;
    bool m_chocolateCollected = false;
    bool m_milkCollected = false;
    bool m_flourCollected = false;
    bool m_recipeCollected = false;

    QList<QString> allCards;

protected:
    void mousePressEvent(QMouseEvent *event) override;

signals:
};

#endif // ITEMMANAGER_H
