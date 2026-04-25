#include "MyPushButton.h"

MyPushButton::MyPushButton(QString normalImg,int w,int h,QString pressImg)
{
    //成员变量normalImgPath保存正常显示图片路径
    normalImgPath = normalImg;
    //成员变量pressedImgPath保存按下后显示的图片
    pressedImgPath = pressImg;
    //创建QPixmap对象
    QPixmap pixmap(normalImgPath);

    //按照指定大小缩放图片
    if (w > 0 && h > 0) {
        pixmap = pixmap.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
    //设置按钮尺寸
    this->setFixedSize( pixmap.width(), pixmap.height());
    //设置透明背景按钮
    this->setStyleSheet(R"(QPushButton {
            border: none;
            background-color: transparent;
            padding: 0px;
            })");
    //设置图标
    this->setIcon(pixmap);
    //设置图标大小
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));
}


