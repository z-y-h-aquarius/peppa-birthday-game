#include "GraphicsImageButton.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

GraphicsImageButton::GraphicsImageButton(QString img,QString text, int w, int h, QGraphicsItem *parent)
    :QGraphicsObject(parent),m_text(text)
{
    m_pix = QPixmap(img).scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    m_size = m_pix.size();

    //启用鼠标悬停事件，配合shape()实现“只点不透明区域才有效”
    setAcceptHoverEvents(true);
}

QRectF GraphicsImageButton::boundingRect() const
{
    return QRectF(0, 0, m_size.width(), m_size.height());
}



void GraphicsImageButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    //画图片
    painter->drawPixmap(0, 0, m_pix);

    //画文字
    if(!m_text.isEmpty()){
        QFont font("幼圆", 27, QFont::Bold);
        painter->setFont(font);
        painter->setPen(Qt::white);
        painter->drawText(boundingRect(), Qt::AlignCenter, m_text);
    }
}

//鼠标按下事件
void GraphicsImageButton::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    //整个按钮向右下移动2像素，视觉上像是被按下去了
    setPos(pos() + QPointF(2, 2));
}

//鼠标松开事件：移动回去，并且发信号
void GraphicsImageButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    setPos(pos() - QPointF(2, 2));
    emit clicked();
}

QPainterPath GraphicsImageButton::shape() const
{
    QPainterPath path;

    if (m_pix.isNull()) {
        path.addRect(boundingRect());
        return path;
    }

    QImage img = m_pix.toImage();
    for (int y = 0; y < img.height(); ++y) {
        for (int x = 0; x < img.width(); ++x) {
            // 不透明的部分才算点击区域
            if (qAlpha(img.pixel(x, y)) > 1) {
                path.addRect(x, y, 1, 1);
            }
        }
    }

    return path;
}
