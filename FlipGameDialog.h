#ifndef FLIPGAMEDIALOG_H
#define FLIPGAMEDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QVector>
#include <QPixmap>
#include <QVBoxLayout>
#include <QHBoxLayout>

class FlipGameDialog : public QDialog
{
    Q_OBJECT
public:
    explicit FlipGameDialog(QWidget *parent = nullptr);

private slots:
    void cardClicked();  //点击牌

private:
    void checkSuccess();  //检查是否通关
    void showRule();
    void backToPuzzle();
    void onSkipClicked();

    QVector<QPixmap> m_frontPix;  //正面图
    QPixmap m_backPix;            //背面图

    QWidget* pagePuzzle;
    QWidget* pageRule;

    QPushButton* m_firstBtn = nullptr;
    bool m_isFlipping = false;
    int m_pairCount = 0;          //已配对数量
};

#endif // FLIPGAMEDIALOG_H
