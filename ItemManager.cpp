#include "ItemManager.h"
#include <QGraphicsScene>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <QTimer>
#include "PuzzleDialog.h"
#include "CardPuzzleDialog.h"
#include "FlipGameDialog.h"
#include "LightPuzzle.h"
#include "GameScene.h"
#include "CakeScene.h"

ItemManager::ItemManager(GameScene *gameScene,QWidget *parent) : QWidget(parent),m_gameScene(gameScene)
{
}

QList<GraphicsImageButton*> ItemManager::createAllPuzzleItems()
{
    QList<GraphicsImageButton*> list;

    //变暗背景
    m_darkBg = new QGraphicsRectItem;
    m_darkBg->setRect(0,0,1235,700);
    m_darkBg->setBrush(QColor(0,0,0,200));
    m_darkBg->setZValue(105);
    m_gameScene->m_scene.addItem(m_darkBg);
    m_darkBg->hide();

    //鸡蛋道具
    m_eggBtn = new GraphicsImageButton("://image/egg.png", "",80,80);
    m_eggBtn->setPos(853,293);
    connect(m_eggBtn, &GraphicsImageButton::clicked, this, &ItemManager::onEggClicked);

    //先隐藏
    m_eggBtn->hide();

    //显示手掌光标
    m_eggBtn->setCursor(Qt::PointingHandCursor);

    list << m_eggBtn;

    //黄油道具
    m_butterBtn = new GraphicsImageButton("://image/butter.png","",75,37);
    m_butterBtn->setPos(865,380);
    connect(m_butterBtn, &GraphicsImageButton::clicked, this, &ItemManager::onButterClicked);
    m_butterBtn->hide();
    m_butterBtn->setCursor(Qt::PointingHandCursor);
    list << m_butterBtn;

    //巧克力道具
    m_chocolateBtn = new GraphicsImageButton("://image/chocolate.png","",61,45);
    m_chocolateBtn->setPos(479,383);
    connect(m_chocolateBtn, &GraphicsImageButton::clicked, this, &ItemManager::onChocolateClicked);
    m_chocolateBtn->hide();
    m_chocolateBtn->setCursor(Qt::PointingHandCursor);
    list << m_chocolateBtn;

    //牛奶道具
    m_milkBtn = new GraphicsImageButton("://image/milk.png", "",112,55);
    m_milkBtn->setPos(75,430);
    connect(m_milkBtn, &GraphicsImageButton::clicked, this, &ItemManager::onMilkClicked);
    m_milkBtn->setCursor(Qt::PointingHandCursor);
    m_milkBtn->hide();
    list << m_milkBtn;

    //面粉道具
    m_flourBtn = new GraphicsImageButton("://image/flour.png", "",71,50);
    m_flourBtn->setPos(680,520);
    connect(m_flourBtn, &GraphicsImageButton::clicked, this, &ItemManager::onFlourClicked);
    m_flourBtn->setCursor(Qt::PointingHandCursor);
    m_flourBtn->hide();
    list << m_flourBtn;

    //信封道具
    m_envelopeBtn = new GraphicsImageButton("://image/envelope.png", "",111,50);
    m_envelopeBtn->setPos(380,520);
    connect(m_envelopeBtn, &GraphicsImageButton::clicked, this, &ItemManager::onEnvelopeClicked);
    m_envelopeBtn->setCursor(Qt::PointingHandCursor);
    list << m_envelopeBtn;

    //食谱
    m_recipeBtn = new GraphicsImageButton("://image/recipe.png", "",283,400);
    m_recipeBtn->setPos(450,100);
    connect(m_recipeBtn, &GraphicsImageButton::clicked, this, &ItemManager::onRecipeClicked);
    list << m_recipeBtn;
    m_recipeBtn->setCursor(Qt::PointingHandCursor);
    m_recipeBtn->setZValue(110);
    m_recipeBtn->hide();

    //鸡蛋锁
    m_egglockBtn = new GraphicsImageButton("://image/egglock.png","",40,40);
    m_egglockBtn->setPos(815,320);
    connect(m_egglockBtn, &GraphicsImageButton::clicked, this, &ItemManager::onEggLockClicked);
    m_egglockBtn->setCursor(Qt::PointingHandCursor);
    list << m_egglockBtn;
    m_egglockBtn->setZValue(100);

    //鸡蛋题目
    m_eggPuz = new QGraphicsPixmapItem;
    m_eggPuz->setPixmap(QPixmap("://image/eggpuzzle.png").scaled(76,40,Qt::KeepAspectRatio,Qt::FastTransformation));
    m_eggPuz->setPos(850,275);
    m_eggPuz->setZValue(102);
    m_gameScene->m_scene.addItem(m_eggPuz);

    //黄油锁
    m_butterlockBtn = new GraphicsImageButton("://image/butterlock.png","",95,56);
    m_butterlockBtn->setPos(822,397);
    connect(m_butterlockBtn, &GraphicsImageButton::clicked, this, &ItemManager::onButterLockClicked);
    list << m_butterlockBtn;
    m_butterlockBtn->setCursor(Qt::PointingHandCursor);
    m_butterlockBtn->setZValue(101);

    //巧克力锁
    m_chocolatelockBtn = new GraphicsImageButton("://image/chocolatelock.png","",40,50);
    m_chocolatelockBtn->setPos(500,395);
    connect(m_chocolatelockBtn, &GraphicsImageButton::clicked, this, &ItemManager::onChocolateLockClicked);
    m_chocolatelockBtn->setCursor(Qt::PointingHandCursor);
    list << m_chocolatelockBtn;

    //牛奶锁
    m_milklockBtn = new GraphicsImageButton("://image/milklock.png","",40,50);
    m_milklockBtn->setPos(85,395);
    connect(m_milklockBtn, &GraphicsImageButton::clicked, this, &ItemManager::onMilkLockClicked);
    m_milklockBtn->setCursor(Qt::PointingHandCursor);
    list << m_milklockBtn;

    //面粉锁
    m_flourlockBtn = new GraphicsImageButton("://image/flourlock.png","",30,30);
    m_flourlockBtn->setPos(555,500);
    connect(m_flourlockBtn, &GraphicsImageButton::clicked, this, &ItemManager::onFlourLockClicked);
    m_flourlockBtn->setCursor(Qt::PointingHandCursor);
    list << m_flourlockBtn;

    //盒子
    m_box = new GraphicsImageButton("://image/box.png","",84,75);
    m_box->setPos(530,500);
    m_gameScene->m_scene.addItem(m_box);
    connect(m_box, &GraphicsImageButton::clicked, this, &ItemManager::onBoxClicked);
    m_box->setCursor(Qt::PointingHandCursor);
    list << m_box;

    //打开的盒子
    m_openBox = new QGraphicsPixmapItem;
    m_openBox->setPixmap(QPixmap("://image/openbox.png").scaled(132,75));
    m_openBox->setPos(530,480);
    m_gameScene->m_scene.addItem(m_openBox);
    m_openBox->hide();

    //冰箱中部
    m_fridgemImg = new QGraphicsPixmapItem;
    m_fridgemImg->setPixmap(QPixmap("://image/fridgemiddle.png").scaled(206,333));
    m_fridgemImg->setPos(798,163);
    m_gameScene->m_scene.addItem(m_fridgemImg);
    m_fridgemImg->hide();

    //冰箱下部
    m_fridgedImg = new QGraphicsPixmapItem;
    m_fridgedImg->setPixmap(QPixmap("://image/fridgedown.png").scaled(241,340));
    m_fridgedImg->setPos(800,162);
    m_gameScene->m_scene.addItem(m_fridgedImg);
    m_fridgedImg->hide();

    //右侧柜门
    m_rightCabinet = new QGraphicsPixmapItem;
    m_rightCabinet->setPixmap(QPixmap("://image/rightcabinet.png").scaled(218,180));
    m_rightCabinet->setPos(414,315);
    m_gameScene->m_scene.addItem(m_rightCabinet);
    m_rightCabinet->hide();

    //左侧柜门
    m_leftCabinet = new QGraphicsPixmapItem;
    m_leftCabinet->setPixmap(QPixmap("://image/leftcabinet.png").scaled(138,202));
    m_leftCabinet->setPos(10,317);
    m_gameScene->m_scene.addItem(m_leftCabinet);
    m_leftCabinet->hide();

    //把16张牌的路径按顺序放进列表
    allCards = {
        //第1行
        "://image/card/heart_A.png",
        "://image/card/heart_Q.png",
        "://image/card/heart_4.png",
        //第2行
        "://image/card/spade_J.png",
        "://image/card/spade_8.png",
        "://image/card/spade_4.png",
        "://image/card/spade_2.png",
        "://image/card/spade_7.png",
        "://image/card/spade_3.png",
        //第3行
        "://image/card/club_K.png",
        "://image/card/club_Q.png",
        "://image/card/club_5.png",
        "://image/card/club_4.png",
        "://image/card/club_6.png",
        //第4行
        "://image/card/diamond_A.png",
        "://image/card/diamond_5.png"
    };
    return list;
}

//弹出提示框
void ItemManager::showTipMessage(const QString& text)
{
    // 如果已经有弹窗，先删掉，防止重复
    if (m_tipPeppa) {
        // 先从场景移除，再删除，否则会残留图形
        m_gameScene->m_scene.removeItem(m_tipPeppa);
        delete m_tipPeppa;
        m_tipPeppa = nullptr;
    }
    ifTip = true;
    m_tipPeppa = new PeppaDialog;
    m_tipPeppa->setText(text);
    //加到GameScene的场景里，显示提示
    m_gameScene->m_scene.addItem(m_tipPeppa);
}

//飞入背包
void ItemManager::flyItemToBag(GraphicsImageButton* btn, int bagX, double scale)
{
    int index = bagItemCount;
    int y = 50 + index * 90;
    bagItemCount++;//背包物品数+1，下一个道具用下一个位置

    //缩放
    if (scale != 1.0) {
        QTransform transform;
        transform.scale(scale, scale);
        btn->setTransform(transform);
    }

    //飞行动画
    QPropertyAnimation *fly = new QPropertyAnimation(btn, "pos");
    fly->setStartValue(btn->pos());//动画起点
    fly->setEndValue(QPoint(bagX, y));//动画终点
    fly->setDuration(600);//动画时长(ms)
    fly->start(QAbstractAnimation::DeleteWhenStopped);//启动动画，动画结束后自动删除对象，不占内存

}

//点击食谱
void ItemManager::onRecipeClicked()
{
    if(m_gameFinished||ifTip)
        return;

    if (m_recipeCollected){
        showTipMessage("快去收集食材吧~");
        return;
    }
    else{
        m_recipeCollected = true;

        m_darkBg->hide();//背景变亮

        flyItemToBag(m_recipeBtn, 1127, 0.15);

        m_recipeBtn->setCursor(Qt::ArrowCursor);
        ifMakeCake();
    }
}

//点击鸡蛋
void ItemManager::onEggClicked()
{
    if(m_gameFinished||ifTip)
        return;

    //鸡蛋已经在背包里
    if (m_eggCollected){
        showTipMessage("先把食材都集齐吧~");
        return;
    }
    else{
        m_eggCollected = true;//防止重复点击

        flyItemToBag(m_eggBtn, 1115);

        m_fridgemImg->hide();//冰箱中部关闭
        m_egglockBtn->show();//鸡蛋锁出现
        m_eggPuz->show();

        m_eggBtn->setCursor(Qt::ArrowCursor);
        ifMakeCake();
    }
}

//点击黄油
void ItemManager::onButterClicked()
{
    if(m_gameFinished||ifTip)
        return;

    //黄油已经在背包里
    if (m_butterCollected){
        showTipMessage("先把食材都集齐吧~");
        return;
    }
    else{
        m_butterCollected = true;//防止重复点击

        flyItemToBag(m_butterBtn, 1115);

        m_fridgedImg->hide();//冰箱中部关闭
        m_butterlockBtn->show();

        m_butterBtn->setCursor(Qt::ArrowCursor);
        ifMakeCake();
    }
}

//点击巧克力
void ItemManager::onChocolateClicked()
{
    if(m_gameFinished||ifTip)
        return;

    if (m_chocolateCollected){
        showTipMessage("先把食材都集齐吧~");
        return;
    }
    else{
        m_chocolateCollected = true;

        flyItemToBag(m_chocolateBtn, 1122);

        m_rightCabinet->hide();//右侧柜门关闭
        m_chocolatelockBtn->show();

        m_chocolateBtn->setCursor(Qt::ArrowCursor);
        ifMakeCake();
    }
}

//点击牛奶
void ItemManager::onMilkClicked()
{
    if(m_gameFinished||ifTip)
        return;

    if (m_milkCollected){
        showTipMessage("先把食材都集齐吧~");
        return;
    }
    else{
        m_milkCollected = true;

        flyItemToBag(m_milkBtn, 1134);

        m_leftCabinet->hide();//左侧柜门关闭
        m_milklockBtn->show();

        m_milkBtn->setCursor(Qt::ArrowCursor);
        ifMakeCake();
    }
}

//点击面粉
void ItemManager::onFlourClicked()
{
    if(m_gameFinished||ifTip)
        return;

    if (m_flourCollected){
        showTipMessage("先把食材都集齐吧~");
        return;
    }
    else{
        m_flourCollected = true;

        flyItemToBag(m_flourBtn, 1115);

        m_openBox->hide();
        m_box->show();
        m_flourlockBtn->show();

        m_flourBtn->setCursor(Qt::ArrowCursor);
        ifMakeCake();
    }
}

//点击信封
void ItemManager::onEnvelopeClicked()
{
    if (m_envelopeClicked||ifTip) {
        return;
    }

    m_darkBg->show();//背景变暗
    m_recipeBtn->show();
    m_envelopeClicked = true;
    m_envelopeBtn->setCursor(Qt::ArrowCursor);
}

//点击鸡蛋锁
void ItemManager::onEggLockClicked()
{
    //已经解开/有提示框，点击无效
    if (m_egglockSolved||ifTip) {
        return;
    }
    //显示题目
    PuzzleDialog dlg("://image/eggpuzzle.png","://image/eggtip.png","3506","://image/egganswer.png","四位数字密码");

    //密码正确
    //模态对话框 阻塞等待操作，仅当密码正确时执行解锁
    if (dlg.exec() == QDialog::Accepted) {

        m_egglockSolved = true;
        m_egglockBtn->hide();
        m_fridgemImg->show();//解开锁，冰箱中部打开
        m_eggPuz->hide();
        m_eggBtn->show();//解开锁，鸡蛋出现
        m_egglockBtn->setCursor(Qt::ArrowCursor);
    }

}

//点击黄油锁
void ItemManager::onButterLockClicked()
{
    if (m_butterlockSolved||ifTip) {
        return;
    }

    CardPuzzleDialog dlg("://image/butterpuzzle.png","://image/buttertip.png","://image/butteranswer.png",
                         allCards,"://image/card/diamond_5.png");

    if (dlg.exec() == QDialog::Accepted) {
        m_butterlockSolved = true;
        m_butterlockBtn->hide();
        m_fridgedImg->show();//解开锁，冰箱下部打开
        m_butterBtn->show();//解开锁，黄油出现
        m_butterlockBtn->setCursor(Qt::ArrowCursor);
    }
}

//点击巧克力锁
void ItemManager::onChocolateLockClicked()
{
    if (m_chocolatelockSolved||ifTip) {
        return;
    }
    //显示翻牌游戏
    FlipGameDialog dlg;
    if(dlg.exec() == QDialog::Accepted){
        m_chocolatelockSolved = true;
        m_chocolatelockBtn->hide();
        m_rightCabinet->show();//解开锁，右侧柜门打开
        m_chocolateBtn->show();//解开锁，巧克力出现
        m_chocolatelockBtn->setCursor(Qt::ArrowCursor);
    }
}

//点击牛奶锁
void ItemManager::onMilkLockClicked()
{
    if (m_milklockSolved||ifTip) {
        return;
    }
    //显示点灯游戏
    LightPuzzle dlg;
    if(dlg.exec() == QDialog::Accepted){
        m_milklockSolved = true;
        m_milklockBtn->hide();
        m_leftCabinet->show();//解开锁，左侧柜门打开
        m_milkBtn->show();//解开锁，牛奶出现
        m_milklockBtn->setCursor(Qt::ArrowCursor);
    }
}

//点击面粉锁
void ItemManager::onFlourLockClicked()
{
    if (m_flourlockSolved||ifTip) {
        return;
    }
    //显示题目
    PuzzleDialog dlg("://image/flourpuzzle.png","://image/flourtip.png","5269","://image/flouranswer.png","四位数字密码");

    if(dlg.exec() == QDialog::Accepted){
        m_flourlockSolved = true;
        m_flourlockBtn->hide();
        m_box->hide();
        m_openBox->show();
        m_flourBtn->show();
        m_flourlockBtn->setCursor(Qt::ArrowCursor);
        m_box->setCursor(Qt::ArrowCursor);
    }
}

//点击盒子
void ItemManager::onBoxClicked()
{
    if (m_flourlockSolved||ifTip) {
        return;
    }
    //显示题目
    PuzzleDialog dlg("://image/flourpuzzle.png","://image/flourtip.png","5269","://image/flouranswer.png","四位数字密码");

    if(dlg.exec() == QDialog::Accepted){
        m_flourlockSolved = true;
        m_flourlockBtn->hide();
        m_box->hide();
        m_openBox->show();
        m_flourBtn->show();
        m_box->setCursor(Qt::ArrowCursor);
        m_flourlockBtn->setCursor(Qt::ArrowCursor);
    }
}

void ItemManager::ifMakeCake()
{
    //先判断是否集齐
    if (bagItemCount!=6&&!(!m_envelopeClicked&&bagItemCount==5))
        return;

    //====================== 已经集齐 ======================
    m_gameFinished = true;

    QTimer::singleShot(1000,this,[=]() {
        //合成图
        m_collectDoneImg = new QGraphicsPixmapItem;
        m_collectDoneImg->setPixmap(QPixmap("://image/collectdone.png").scaled(328,400));

        int sceneW = 1235;
        int sceneH = 700;
        int imgW = m_collectDoneImg->pixmap().width();
        int imgH = m_collectDoneImg->pixmap().height();
        int imgX = (sceneW - imgW) / 2;
        int imgY = (sceneH - imgH) / 2;

        m_collectDoneImg->setPos(imgX, imgY);
        m_gameScene->m_scene.addItem(m_collectDoneImg);

        //让图片更立体
        QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
        shadow->setColor(QColor(0,0,0,100));
        m_collectDoneImg->setGraphicsEffect(shadow);

        //合成蛋糕按钮
        m_makeCakeBtn = new GraphicsImageButton("://image/start_button.png", "合成蛋糕",187,67);
        m_makeCakeBtn->setZValue(107);

        int btnW = 187;
        int btnH = 67;
        int btnX = imgX + (imgW - btnW) / 2 + 13;
        int btnY = imgY + (imgH - btnH) / 2 + 79;

        m_makeCakeBtn->setPos(btnX, btnY);
        m_gameScene->m_scene.addItem(m_makeCakeBtn);

        // 点击进入 CakeScene
        connect(m_makeCakeBtn, &GraphicsImageButton::clicked, this, [=]() {
            m_collectDoneImg->hide();
            m_makeCakeBtn->hide();

            // ========== 关键：创建下一阶段 ==========
            CakeScene* cakePage = new CakeScene(m_gameScene, nullptr);
            cakePage->setGeometry(0, 0, 1235, 700);
            cakePage->setStyleSheet("background:transparent;");
            m_gameScene->m_scene.addWidget(cakePage);
        });
    });
}

//点击任意处继续
void ItemManager::mousePressEvent(QMouseEvent *event)
{
    if (m_tipPeppa) {
        // 先从场景移除，再删除，否则会残留图形
        m_gameScene->m_scene.removeItem(m_tipPeppa);
        delete m_tipPeppa;
        m_tipPeppa = nullptr;
        ifTip = false;
    }

    QWidget::mousePressEvent(event);
}
