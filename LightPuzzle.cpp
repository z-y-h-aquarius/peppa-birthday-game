#include "LightPuzzle.h"
#include <random>

LightPuzzle::LightPuzzle(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("点灯谜题");
    setFixedSize(420, 420);

    //规则页面
    pageRule = new QWidget(this);
    QVBoxLayout* ruleLayout = new QVBoxLayout(pageRule);

    QTextEdit* ruleText = new QTextEdit();
    ruleText->setReadOnly(true);
    ruleText->setHtml(R"(
        <div style="font-size:18px;">
        <h2>规则说明</h2>
        <p>1. 点击任意一盏灯，它自己和上下左右的灯会一起切换亮/暗。</p >
        <p>2. 目标：把所有灯全部点亮。</p >
        <p>3. 点亮所有灯即可找到牛奶，完成谜题。</p >
    )");

    //返回按钮
    QPushButton* btnBack1 = new QPushButton("返回");
    ruleLayout->addWidget(ruleText);
    ruleLayout->addWidget(btnBack1);
    connect(btnBack1, &QPushButton::clicked, this, &LightPuzzle::backToPuzzle);

    //提示页面
    pageTip = new QWidget(this);
    QVBoxLayout* tipLayout = new QVBoxLayout(pageTip);

    QTextEdit* tipText = new QTextEdit();
    tipText->setReadOnly(true);
    tipText->setHtml(R"(
        <div style="font-size:16px;">
        <h2>3×3点灯解谜步骤</h2>
        <p>给灯编号：</p >
        <p>1 2 3</p >
        <p>4 5 6</p >
        <p>7 8 9</p >

        <p><b>第一步：处理第一行</b></p >
        <p>灯1灭 → 点4</p >
        <p>灯2灭 → 点5</p >
        <p>灯3灭 → 点6</p >
        <br>
        <p><b>第二步：处理第二行</b></p >
        <p>灯4灭 → 点7</p >
        <p>灯5灭 → 点8</p >
        <p>灯6灭 → 点9</p >
        <br>
        <p><b>第三步：根据最后一行状态点击</b></p >
        <p>1=亮，0=灭</p >
        <p>000 → 点2,4,5,6号灯</p >
        <p>001 → 点3,5,6,7,9号灯</p >
        <p>010 → 点1,3,4,6号灯</p >
        <p>011 → 点1,2,6,7,9号灯</p >
        <p>100 → 点1,4,5,7,9号灯</p >
        <p>101 → 点1,2,3,5号灯</p >
        <p>110 → 点2,3,4,7,9号灯</p >
    )");

    QPushButton* btnBack2 = new QPushButton("返回");
    tipLayout->addWidget(tipText);
    tipLayout->addWidget(btnBack2);
    connect(btnBack2, &QPushButton::clicked, this, &LightPuzzle::backToPuzzle);

    //游戏页面
    pagePuzzle = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(pagePuzzle);
    QGridLayout* grid = new QGridLayout();

    for (int r = 0; r < ROW; ++r) {
        for (int c = 0; c < COL; ++c) {
            m_btns[r][c] = new QPushButton();
            m_btns[r][c]->setFixedSize(70, 70);
            connect(m_btns[r][c], &QPushButton::clicked, this, &LightPuzzle::onLightClicked);
            grid->addWidget(m_btns[r][c], r, c);
        }
    }

    //按钮栏：规则/提示/刷新/跳过
    QHBoxLayout* btnBar = new QHBoxLayout();//横向布局
    QPushButton* btnRule = new QPushButton("查看规则");
    QPushButton* btnTip = new QPushButton("查看提示");
    QPushButton* btnRefresh = new QPushButton("刷新题目");
    QPushButton* btnSkip = new QPushButton("跳过");

    btnBar->addWidget(btnRule);
    btnBar->addWidget(btnTip);
    btnBar->addWidget(btnRefresh);
    btnBar->addWidget(btnSkip);

    connect(btnRule, &QPushButton::clicked, this, &LightPuzzle::showRule);
    connect(btnTip, &QPushButton::clicked, this, &LightPuzzle::showTip);
    connect(btnRefresh, &QPushButton::clicked, this, &LightPuzzle::onRefreshClicked);
    connect(btnSkip, &QPushButton::clicked, this, &LightPuzzle::onSkipClicked);

    mainLayout->addLayout(grid);
    mainLayout->addLayout(btnBar);

    //全局布局
    QVBoxLayout* globalLayout = new QVBoxLayout(this);
    globalLayout->addWidget(pagePuzzle);
    globalLayout->addWidget(pageRule);
    pageRule->hide();
    globalLayout->addWidget(pageTip);
    pageTip->hide();

    //随机初始灯
    initRandom();
}

//随机亮暗
void LightPuzzle::initRandom()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    for (int r = 0; r < ROW; ++r) {
        for (int c = 0; c < COL; ++c) {
            m_isLight[r][c] = dis(gen);
            updateButton(r, c);
        }
    }
}

//根据状态切换亮暗两张图
void LightPuzzle::updateButton(int r, int c)
{
    //亮灯图标
    QIcon iconOn("://image/light_on.png");
    //灭灯图标
    QIcon iconOff("://image/light_off.png");

    if (m_isLight[r][c]) {
        m_btns[r][c]->setIcon(iconOn);
    } else {
        m_btns[r][c]->setIcon(iconOff);
    }

    //让图标充满按钮
    m_btns[r][c]->setIconSize(m_btns[r][c]->size());

    //去掉按钮背景、边框、点击效果，按钮透明
    m_btns[r][c]->setStyleSheet(R"(
        QPushButton {
            border: none;
            background: transparent;
        }
    )");
}
//翻转：自己 + 上下左右
void LightPuzzle::flip(int r, int c)
{
    auto toggle = [&](int rr, int cc) {
        if (rr < 0 || rr >= ROW || cc < 0 || cc >= COL) return;
        m_isLight[rr][cc] = !m_isLight[rr][cc];
        updateButton(rr, cc);
    };

    toggle(r, c);
    toggle(r-1, c);
    toggle(r+1, c);
    toggle(r, c-1);
    toggle(r, c+1);
}

//点击灯
void LightPuzzle::onLightClicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    for (int r = 0; r < ROW; ++r) {
        for (int c = 0; c < COL; ++c) {
            if (m_btns[r][c] == btn) {
                flip(r, c);
                if (checkAllLight()) {
                    QMessageBox::information(this, "恭喜", "你找到了牛奶！");
                    accept();
                }
                return;
            }
        }
    }
}

//判断是否全亮
bool LightPuzzle::checkAllLight()
{
    for (int r = 0; r < ROW; ++r)
        for (int c = 0; c < COL; ++c)
            if (!m_isLight[r][c]) return false;
    return true;
}

//刷新题目
void LightPuzzle::onRefreshClicked()
{
    initRandom();
}

//跳过
void LightPuzzle::onSkipClicked()
{
    auto ret = QMessageBox::question(this, "跳过", "不再想想了吗？");
    if (ret == QMessageBox::Yes) {
        accept();
    }
}

//规则页
void LightPuzzle::showRule()
{
    pagePuzzle->hide();
    pageRule->show();
}

//提示页
void LightPuzzle::showTip()
{
    pagePuzzle->hide();
    pageTip->show();
}

//返回游戏
void LightPuzzle::backToPuzzle()
{
    pageRule->hide();
    pageTip->hide();
    pagePuzzle->show();
}
