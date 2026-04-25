#ifndef ANSWERDIALOG_H
#define ANSWERDIALOG_H

#include <QDialog>

class AnswerDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AnswerDialog(QString answerImg,QWidget *parent = nullptr);

public slots:
    void goBackToPuzzle();//跳转到答题页

private:
    QString m_answerImg;

signals:
};

#endif // ANSWERDIALOG_H
