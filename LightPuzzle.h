#ifndef LIGHTPUZZLE_H
#define LIGHTPUZZLE_H

#include <QDialog>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QTextEdit>

class LightPuzzle : public QDialog
{
    Q_OBJECT
public:
    explicit LightPuzzle(QWidget *parent = nullptr);

    //三行三列
    static constexpr int ROW = 3;
    static constexpr int COL = 3;

private:
    QPushButton* m_btns[ROW][COL];
    bool m_isLight[ROW][COL];  //true=亮 false=暗

    void initRandom();         //随机初始状态
    void flip(int r, int c);   //翻转自己+上下左右
    void updateButton(int r, int c); //根据状态切换图片
    bool checkAllLight();      //判断是否全亮

    QWidget* pagePuzzle;
    QWidget* pageRule;
    QWidget* pageTip;

private slots:
    void onLightClicked();
    void onRefreshClicked();
    void onSkipClicked();
    void showRule();
    void showTip();
    void backToPuzzle();
};

#endif // LIGHTPUZZLE_H
