#include "triangleprimitive.h"



TrianglePrimitive::TrianglePrimitive(const QColor &color)
{
    m_color = color;
}

TrianglePrimitive::TrianglePrimitive(float x1, float y1,
                                     float x2, float y2,
                                     float x3, float y3,
                                     const QColor &color)
{
    m_color = color;
    m_p[1] = QVector3D(x1, y1, 1);
    m_p[2] = QVector3D(x2, y2, 1);
    m_p[3] = QVector3D(x3, y3, 1);
}

TrianglePrimitive::TrianglePrimitive(const QVector3D &p1,
                                     const QVector3D &p2,
                                     const QVector3D &p3,
                                     const QColor &color)
{
    m_color = color;
    m_p[1] = p1;
    m_p[2] = p2;
    m_p[3] = p3;
}

QColor TrianglePrimitive::color() const
{
    return m_color;
}

QVector3D TrianglePrimitive::point(int i) const
{
    return m_p[i];
}

void TrianglePrimitive::setColor(const QColor &col)
{
    m_color = col;
}

void TrianglePrimitive::setPoint(int i, const QVector3D &p)
{
    m_p[i] = p;
}

void TrianglePrimitive::setPoint(int i, float x, float y)
{
    m_p[i] = QVector3D { x, y, 1 };
}

QVariant TrianglePrimitive::toVariant() const
{
    QVariantMap data;
    data["color"] = m_color;
    data["points"] = QVariantList { m_p[0], m_p[1], m_p[2] };

    return data;
}


QDebug operator <<(QDebug debug, const TrianglePrimitive &t)
{
    debug << "Triangle(" << t.point(0)<< ", " << t.point(1) << ", " << t.point(2) << ")";
    return debug;
}
