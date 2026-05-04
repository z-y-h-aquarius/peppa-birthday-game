#include "PuzzleDialog.h"
#include "TipDialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QPixmap>
#include <QDebug>
//构造：接收题目，提示，答案，正确密码
PuzzleDialog::PuzzleDialog(QString puzzleImg,QString tipImg,QString answer,QString answerImg,QString windowText,QWidget *parent)
    : QDialog(parent)
{
    setFixedSize(600,500);

    setWindowTitle(windowText);

    //显示题目图片
    QLabel *imgLabel = new QLabel;
    imgLabel->setPixmap(QPixmap(puzzleImg).scaled(560,360,Qt::KeepAspectRatio));

    //密码输入框
    QLineEdit *edit = new QLineEdit;
    edit->setPlaceholderText("输入密码");

    //按钮
    QPushButton *btnOk = new QPushButton("确认");
    QPushButton *btnTip = new QPushButton("提示");

    //布局
    QVBoxLayout *ly = new QVBoxLayout;
    ly->addWidget(imgLabel);
    ly->addWidget(edit);
    ly->addWidget(btnOk);
    ly->addWidget(btnTip);
    setLayout(ly);

    //确认按钮
    connect(btnOk, &QPushButton::clicked, this,[=](){
        //答对后不能再点
        if(m_lockSolved)
            return;
        else if (edit->text() == answer) {
            m_lockSolved = true;
            accept();//密码正确->关闭弹窗，返回“成功”
        }
        else {
            QMessageBox::warning(this, "错误", "密码不正确！");
        }
    });

    //提示按钮
    connect(btnTip,&QPushButton::clicked,this,[=](){
        //先创建新窗口，再隐藏自己
        TipDialog d(tipImg,answerImg,this);
        d.exec(); // 阻塞，TipDialog关闭后自动回到这里
    });
}
