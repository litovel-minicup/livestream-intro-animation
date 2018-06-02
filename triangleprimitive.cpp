#include "triangleprimitive.h"



TrianglePrimitive::TrianglePrimitive(const QColor &color)
{
    m_color = color;
    m_p.fill(QPointF(), 3);
}

TrianglePrimitive::TrianglePrimitive(qreal x1, qreal y1,
                                     qreal x2, qreal y2,
                                     qreal x3, qreal y3,
                                     const QColor &color)
{
    m_color = color;
    m_p.append(QPointF(x1, y1));
    m_p.append(QPointF(x2, y2));
    m_p.append(QPointF(x3, y3));
}

TrianglePrimitive::TrianglePrimitive(const QPointF &p1,
                                     const QPointF &p2,
                                     const QPointF &p3,
                                     const QColor &color)
{
    m_color = color;
    m_p.append(p1);
    m_p.append(p2);
    m_p.append(p3);
}

QColor TrianglePrimitive::color() const
{
    return m_color;
}

QPointF TrianglePrimitive::point(int i) const
{
    return m_p[i];
}

void TrianglePrimitive::setColor(const QColor &col)
{
    m_color = col;
}

void TrianglePrimitive::setPoint(int i, const QPointF &p)
{
    m_p[i] = p;
}

void TrianglePrimitive::setPoint(int i, qreal x, qreal y)
{
    m_p[i] = QPointF { x, y };
}

QVariant TrianglePrimitive::toVariant() const
{
    QVariantMap data;
    data["color"] = m_color;
    data["points"] = QVariantList { m_p[0], m_p[1], m_p[2] };

return data;
}

QVector<QPointF> TrianglePrimitive::points() const
{
    return m_p;
}

QDebug operator <<(QDebug debug, const TrianglePrimitive &t)
{
    debug << "Triangle(" << t.point(0)<< ", " << t.point(1) << ", " << t.point(2) << ")";
    return debug;
}
