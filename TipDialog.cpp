#include "TipDialog.h"
#include "AnswerDialog.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPixmap>
//构造：接收提示图，答案图
TipDialog::TipDialog(QString tipImg,QString answerImg,QWidget *parent)
    : QDialog(parent),
    m_tipImg(tipImg),
    m_answerImg(answerImg)
{
    setFixedSize(600,500);
    setWindowTitle("提示");

    //提示图
    QLabel *img = new QLabel;
    img->setPixmap(QPixmap(m_tipImg).scaled(560,360,Qt::KeepAspectRatio));

    //按钮
    QPushButton *btnBack = new QPushButton("再试试");
    QPushButton *btnAns = new QPushButton("查看答案");

    //布局
    QVBoxLayout *ly = new QVBoxLayout;
    ly->addWidget(img);
    ly->addWidget(btnBack);
    ly->addWidget(btnAns);
    setLayout(ly);

    //再试试
    connect(btnBack,&QPushButton::clicked,this,&TipDialog::goBackToPuzzle);
    //查看答案
    connect(btnAns,&QPushButton::clicked,this,&TipDialog::goToAnswer);
}

//返回题目页面
void TipDialog::goBackToPuzzle()
{
    this->close();//关闭自己，会自动释放
}

//跳转答案页面
void TipDialog::goToAnswer()
{
    AnswerDialog d = AnswerDialog(m_answerImg);//把PuzzleDialog作为AnswerDialog的父对象
    if (d.exec() == QDialog::Accepted) {
        //AnswerDialog点 知道了 (accept)，直接关闭TipDialog
        this->close();//关闭TipDialog，回到PuzzleDialog
    }
    //如果点 取消 (reject)，不关闭TipDialog，留在TipDialog
}
