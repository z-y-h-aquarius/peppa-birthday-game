#include "FlipGameDialog.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include <QTimer>
#include <algorithm>

FlipGameDialog::FlipGameDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("纸牌配对游戏");
    setFixedSize(400,568);

    m_backPix = QPixmap("://image/cardback.png").scaled(80,122);

    m_frontPix << QPixmap("://image/card/diamond_A.png").scaled(80,122);
    m_frontPix << QPixmap("://image/card/diamond_A.png").scaled(80,122);
    m_frontPix << QPixmap("://image/card/heart_4.png").scaled(80,122);
    m_frontPix << QPixmap("://image/card/heart_4.png").scaled(80,122);
    m_frontPix << QPixmap("://image/card/spade_2.png").scaled(80,122);
    m_frontPix << QPixmap("://image/card/spade_2.png").scaled(80,122);
    m_frontPix << QPixmap("://image/card/club_6.png").scaled(80,122);
    m_frontPix << QPixmap("://image/card/club_6.png").scaled(80,122);
    m_frontPix << QPixmap("://image/card/diamond_5.png").scaled(80,122);
    m_frontPix << QPixmap("://image/card/diamond_5.png").scaled(80,122);
    m_frontPix << QPixmap("://image/card/heart_A.png").scaled(80,122);
    m_frontPix << QPixmap("://image/card/heart_A.png").scaled(80,122);
    m_frontPix << QPixmap("://image/card/spade_7.png").scaled(80,122);
    m_frontPix << QPixmap("://image/card/spade_7.png").scaled(80,122);
    m_frontPix << QPixmap("://image/card/club_4.png").scaled(80,122);
    m_frontPix << QPixmap("://image/card/club_4.png").scaled(80,122);

    //随机打乱顺序
    std::shuffle(m_frontPix.begin(), m_frontPix.end(), *QRandomGenerator::global());

    //纸牌布局
    QGridLayout* layout = new QGridLayout(this);
    for(int i=0; i<16; i++){
        QPushButton* btn = new QPushButton;
        btn->setIcon(m_backPix);
        btn->setIconSize(QSize(80,122));
        btn->setFixedSize(80,122);
        connect(btn, &QPushButton::clicked, this, &FlipGameDialog::cardClicked);
        layout->addWidget(btn, i/4, i%4);

        //存索引，让按钮记住自己对应的是第几张正面图
        btn->setProperty("index", i);
    }
}

void FlipGameDialog::cardClicked()
{
    //禁止翻牌动画中再次点击
    if(m_isFlipping)
        return;

    //找到谁被点击了
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if(!btn) return;

    //只判断是不是背面
    QIcon currentIcon = btn->icon();
    if (currentIcon.name() == "" && currentIcon.pixmap(80,122).toImage() == m_backPix.toImage())
    {
        int idx = btn->property("index").toInt();
        QPixmap front = m_frontPix[idx];
        btn->setIcon(front);

        if(!m_firstBtn){
            m_firstBtn = btn;
        }else{//第二张牌
            m_isFlipping = true;

            int idx1 = m_firstBtn->property("index").toInt();
            int idx2 = btn->property("index").toInt();

            //两张一样
            if(m_frontPix[idx1].toImage() == m_frontPix[idx2].toImage()){
                //禁用按钮
                m_firstBtn->setEnabled(false);
                btn->setEnabled(false);
                //配对数+1
                m_pairCount++;
                //检查是否胜利
                checkSuccess();

                m_firstBtn = nullptr;
                m_isFlipping = false;
            }
            else{//不相同，等500ms翻回背面
                QTimer::singleShot(500, this,[=](){
                    m_firstBtn->setIcon(m_backPix);
                    btn->setIcon(m_backPix);

                    m_firstBtn = nullptr;
                    m_isFlipping = false;
                });
            }
        }
    }
}

void FlipGameDialog::checkSuccess()
{
    //匹配完八对
    if(m_pairCount == 8){
        QMessageBox::information(this, "恭喜", "解锁成功！");
        accept();
    }
}
