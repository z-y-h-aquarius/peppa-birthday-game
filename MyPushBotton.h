#ifndef MYPUSHBOTTON_H
#define MYPUSHBOTTON_H

#include <QPushButton>
#include<QWidget>

class MyPushBotton : public QPushButton
{
    Q_OBJECT
public:
    //normalImg 代表正常显示的图片
    //pressImg  代表按下后显示的图片，默认为空
    MyPushButton(QString normalImg,QString pressImg = "",QWidget * parent = nullptr);

    QString normalImgPath;  //默认显示图片路径
    QString pressedImgPath; //按下后显示图片路径

signals:
};

#endif // MYPUSHBOTTON_H
