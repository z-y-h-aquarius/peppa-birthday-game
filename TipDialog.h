#ifndef TIPDIALOG_H
#define TIPDIALOG_H

#include <QDialog>

class TipDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TipDialog(
        QString tipImg,//提示图
        QString answerImg,//答案图
        QWidget *parent = nullptr);

private slots:
    void goBackToPuzzle();//返回题目页面
    void goToAnswer();//跳转答案页面

private:
    QString m_tipImg;
    QString m_answerImg;
signals:
};

#endif // TIPDIALOG_H
