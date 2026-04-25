#ifndef CARDPUZZLEDIALOG_H
#define CARDPUZZLEDIALOG_H

#include <QDialog>
#include <QString>
#include <QList>

class CardPuzzleDialog : public QDialog
{
    Q_OBJECT
public:
    // 题目图 + 提示图 + 所有扑克牌路径列表 + 正确牌路径
    explicit CardPuzzleDialog(
        const QString& puzzleImg,//题目图
        const QString tipImg,//提示图
        QString answerImg,//答案图
        const QList<QString>& cardPaths,//所有牌的图片路径
        const QString& correctCardPath,//正确的牌的路径
        QWidget *parent = nullptr
        );

private:
    bool m_lockSolved = false;  // 通关锁，防止重复点击
};

#endif // CARDPUZZLEDIALOG_H
