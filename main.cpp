#include "MainScene.h"

#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainScene w;
    //设置窗口左上角图标
    w.setWindowIcon(QIcon("://image/peppa.png"));
    w.show();
    return a.exec();
}
