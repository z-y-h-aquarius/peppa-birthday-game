#include "PeppaDialog.h"

PeppaDialog::PeppaDialog(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    //佩奇
    m_peppa = new QGraphicsPixmapItem(this); // 父对象设为 this，自动管理内存
    m_peppa->setPixmap(QPixmap("://image/peppa.png"));
    m_peppa->setPos(0,376);
    m_peppa->setScale(0.74);
    m_peppa->setZValue(90);

    //气泡（圆角）
    QPainterPath bubblePath;
    bubblePath.addRoundedRect(335,390,457,121,13,13);
    m_bubble = new QGraphicsPathItem(bubblePath, this);
    m_bubble->setBrush(QColor(255,230,235,204));
    m_bubble->setPen(QPen(Qt::black,2));
    m_bubble->setZValue(91);

    //尖角
    QPolygonF arrow;
    arrow << QPointF(335,443)
          << QPointF(295,470)
          << QPointF(335,470);

    m_tail = new QGraphicsPolygonItem(arrow, this);
    m_tail->setBrush(QColor(255,230,235,204));
    m_tail->setPen(QPen(Qt::black,2));
    m_tail->setZValue(92);

    //提示文字
    m_tipText = new QGraphicsTextItem(this);
    m_tipText->setFont(QFont("微软雅黑",14));
    m_tipText->setPos(360,420);
    m_tipText->setZValue(93);//层级93（改在气泡上面）

    //点击任意处继续
    m_clickTip = new QGraphicsTextItem(this);
    m_clickTip->setPlainText("点击任意处继续");
    m_clickTip->setFont(QFont("微软雅黑",10));
    m_clickTip->setPos(670,480);
    m_clickTip->setDefaultTextColor(Qt::gray);
    m_clickTip->setZValue(94);
}

//设置提示文字（外部调用接口）
void PeppaDialog::setText(const QString &text)
{
    m_tipText->setPlainText(text);
}

//定义气泡的边界矩形
QRectF PeppaDialog::boundingRect() const
{
    //按画布最大范围设置，避免裁剪
    return QRectF(0,0,1235,700);
}
void PeppaDialog::paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) {}
