#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QWidget>
#include <QGraphicsPixmapItem>//图形元素
#include <QGraphicsView>//视图
#include <QGraphicsScene>//场景
#include <QList>
#include <GameScene.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainScene;
}
QT_END_NAMESPACE

class MainScene : public QWidget
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

public slots:
    void startGame();

private:
    Ui::MainScene *ui;

    QGraphicsView mGameView;//游戏视图
    QGraphicsScene mScene;//场景
    QGraphicsPixmapItem mPeppa;//佩奇
    QGraphicsPixmapItem mBackGround1;
    QGraphicsPixmapItem mBackGround2;

    QList<QGraphicsPixmapItem*> mBackpackItems;//背包

};
#endif // MAINSCENE_H
