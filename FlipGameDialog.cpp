#include "FlipGameDialog.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include <QTimer>
#include <algorithm>
#include <QTextEdit>

FlipGameDialog::FlipGameDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("纸牌配对游戏");
    setFixedSize(400,600);

    //规则页面
    pageRule = new QWidget(this);
    QVBoxLayout* ruleLayout = new QVBoxLayout(pageRule);

    QTextEdit* ruleText = new QTextEdit();
    ruleText->setReadOnly(true);
    ruleText->setHtml(R"(
        <div style="font-size:18px;">
        <h2>纸牌配对规则</h2>
        <p>1. 点击卡牌进行翻面。</p >
        <p>2. 每次只能翻开两张牌。</p >
        <p>3. 两张牌图案相同则配对成功并锁定。</p >
        <p>4. 全部配对完成即可解锁通关。</p >
    )");

    //返回按钮
    QPushButton* btnBack1 = new QPushButton("返回");
    ruleLayout->addWidget(ruleText);
    ruleLayout->addWidget(btnBack1);
    connect(btnBack1, &QPushButton::clicked, this, &FlipGameDialog::backToPuzzle);

    pagePuzzle = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(pagePuzzle);

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
    QGridLayout* layout = new QGridLayout();
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

    //底部按钮栏：查看规则、跳过
    QHBoxLayout* btnBar = new QHBoxLayout();
    QPushButton* btnRule = new QPushButton("查看规则");
    QPushButton* btnSkip = new QPushButton("跳过");

    btnBar->addWidget(btnRule);
    btnBar->addWidget(btnSkip);

    connect(btnRule, &QPushButton::clicked, this, &FlipGameDialog::showRule);
    connect(btnSkip, &QPushButton::clicked, this, &FlipGameDialog::onSkipClicked);

    mainLayout->addLayout(layout);
    mainLayout->addLayout(btnBar);

    //全局层级布局
    QVBoxLayout* globalLayout = new QVBoxLayout(this);
    globalLayout->addWidget(pagePuzzle);
    globalLayout->addWidget(pageRule);
    pageRule->hide();
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

//查看规则
void FlipGameDialog::showRule()
{
    pagePuzzle->hide();
    pageRule->show();
}

//返回游戏页面
void FlipGameDialog::backToPuzzle()
{
    pageRule->hide();
    pagePuzzle->show();
}

//跳过谜题
void FlipGameDialog::onSkipClicked()
{
    auto ret = QMessageBox::question(this, "跳过", "不再想想了吗？");
    if (ret == QMessageBox::Yes) {
        accept();
    }
}
