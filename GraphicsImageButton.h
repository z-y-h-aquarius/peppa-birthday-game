#ifndef GRAPHICSIMAGEBUTTON_H
#define GRAPHICSIMAGEBUTTON_H

#include <QGraphicsObject>
#include <QPixmap>

class GraphicsImageButton : public QGraphicsObject
{
    Q_OBJECT
public:
    GraphicsImageButton(QString img,QString text,int w,int h,QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

signals:
    void clicked();

protected:
    //重写鼠标事件
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    QPainterPath shape() const override;

private:
    QPixmap m_pix;//按钮图片
    QSize m_size;//按钮大小
    QString m_text;//按钮文字
};

#endif
