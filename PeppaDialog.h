#ifndef PEPPADIALOG_H
#define PEPPADIALOG_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsPathItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsTextItem>
#include <QFont>
#include <QColor>
#include <QPen>
#include <QPainterPath>
#include <QPixmap>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

class PeppaDialog :public QGraphicsItem
{
public:
    explicit PeppaDialog(QGraphicsItem *parent = nullptr);

    //设置对话文字
    void setText(const QString &text);

    //函数重写
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QGraphicsPixmapItem *m_peppa;
    QGraphicsPathItem *m_bubble;
    QGraphicsPolygonItem *m_tail;
    QGraphicsTextItem *m_tipText;
    QGraphicsTextItem *m_clickTip;

signals:
};

#endif // PEPPADIALOG_H
