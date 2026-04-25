#ifndef PUZZLEDIALOG_H
#define PUZZLEDIALOG_H

#include <QDialog>

class PuzzleDialog : public QDialog
{
    Q_OBJECT
public:
    //构造：传题目图片+正确答案
    explicit PuzzleDialog(
        QString puzzleImg,//题目图
        QString tipImg,//提示图
        QString answer,//正确密码
        QString answerImg,//答案图
        QWidget *parent = nullptr);

    //判断是否答对
    bool m_lockSolved = false;

signals:


};
#endif // PUZZLEDIALOG_H
