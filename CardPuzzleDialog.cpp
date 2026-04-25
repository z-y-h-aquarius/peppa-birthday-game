#include "CardPuzzleDialog.h"
#include "TipDialog.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPixmap>

CardPuzzleDialog::CardPuzzleDialog(
    const QString& puzzleImg,
    QString tipImg,
    QString answerImg,
    const QList<QString>& cardPaths,
    const QString& correctCardPath,
    QWidget *parent
    ) : QDialog(parent)
{
    // 窗口大小适配4行牌+题目图
    setFixedSize(1004,700);
    setWindowTitle("选择正确的扑克牌");


    //顶部题目图片区域
    QLabel* imgLabel = new QLabel(this);
    imgLabel->setPixmap(QPixmap(puzzleImg).scaled(1004,591, Qt::KeepAspectRatio));
    imgLabel->setGeometry(0,0,1004,591); // 手动固定位置，居中

    //扑克牌容器
    QWidget* cardContainer = new QWidget(this);
    cardContainer->setGeometry(30,100,965,430);//牌区整体位置

    //牌的固定尺寸
    const int cardW = 65;
    const int cardH = 99;
    const int iconW = 65;
    const int iconH = 99;

    //手动给16张牌设置坐标
    //格式：{x坐标, y坐标}，相对于cardContainer的位置
    QList<QPoint> cardPosList = {
        // 第一行（3张：红桃A、红桃Q、红桃4）
        QPoint(500, 0),
        QPoint(580, 0),
        QPoint(660, 0),

        // 第二行（6张：黑桃J、8、4、2、7、3）
        QPoint(500, 110),
        QPoint(580, 110),
        QPoint(660, 110),
        QPoint(740, 110),
        QPoint(820, 110),
        QPoint(900, 110),

        // 第三行（5张：梅花K、Q、5、4、6）
        QPoint(500, 220),
        QPoint(580, 220),
        QPoint(660, 220),
        QPoint(740, 220),
        QPoint(820, 220),

        // 第四行（2张：方块A、方块5）
        QPoint(500, 330),
        QPoint(580, 330)
    };

    // 遍历创建所有牌按钮，手动设置位置
    for (int i = 0; i < cardPaths.size(); i++) {
        const QString& path = cardPaths[i];
        QPoint pos = cardPosList[i];

        // 创建牌按钮
        QPushButton* cardBtn = new QPushButton(cardContainer);
        // 设置按钮位置和大小
        cardBtn->setGeometry(pos.x(), pos.y(), cardW, cardH);

        // 设置牌的图片
        QPixmap cardPix(path);
        cardBtn->setIcon(cardPix.scaled(iconW, iconH, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        cardBtn->setIconSize(QSize(iconW, iconH));

        // 按钮样式：去掉边框，加hover高亮效果
        cardBtn->setStyleSheet(R"(
        QPushButton {
            border: none;
            background: transparent;
            border-radius: 6px;
        }
        QPushButton:hover {
            border: 3px solid #ff6688;
        }
        )");
        cardBtn->setCursor(Qt::PointingHandCursor); // 鼠标放上去变手型

        // 点击事件：判断对错，逻辑和之前完全一致
        connect(cardBtn, &QPushButton::clicked, this,[=](){
            if (m_lockSolved) return; // 已经解锁就不让点了

            if (path == correctCardPath) {
                m_lockSolved = true;
                accept(); // 选对了，关闭弹窗返回成功
            } else {
                QMessageBox::warning(this, "选错啦", "这张牌不对哦~再仔细想想吧！");
            }
        });
    }

    //底部提示按钮
    QPushButton* btnTip = new QPushButton("查看提示", this);
    btnTip->setGeometry(440,625,150,60); // 手动固定位置，底部居中
    btnTip->setStyleSheet(R"(
    QPushButton {
        background-color: #ffd0e0;
        border-radius: 8px;
        font-size: 18px;
    }
    QPushButton:hover {
        background-color: #ffb0c0;
    }
    )");
    //点击打开提示弹窗
    connect(btnTip, &QPushButton::clicked, this,[=](){
        TipDialog tipDlg(tipImg, answerImg, this);
        tipDlg.exec();
    });
}
