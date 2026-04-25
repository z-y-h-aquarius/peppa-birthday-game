#include "AnswerDialog.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

AnswerDialog::AnswerDialog(QString answerImg,QWidget *parent)
    :QDialog(parent)
{
    setFixedSize(600,500);
    setWindowTitle("答案");

    //显示答案图片
    QLabel *img = new QLabel;
    img->setPixmap(QPixmap(answerImg).scaled(560,360,Qt::KeepAspectRatio));

    //知道了按钮
    QPushButton *btnGot = new QPushButton("知道了，返回");

    //布局
    QVBoxLayout *ly = new QVBoxLayout;
    ly->addWidget(img);
    ly->addWidget(btnGot);
    setLayout(ly);

    connect(btnGot,&QPushButton::clicked,this,&AnswerDialog::goBackToPuzzle);
}

//知道了->直接回到 PuzzleDialog
    void AnswerDialog::goBackToPuzzle()
{
         this->accept();//触发accept()，关闭AnswerDialog，返回TipDialog
}
