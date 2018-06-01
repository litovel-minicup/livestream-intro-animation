#include "triangleprimitive.h"



TrianglePrimitive::TrianglePrimitive(float x1, float y1,
                                     float x2, float y2,
                                     float x3, float y3,
                                     const QColor &color)
{
    m_color = color;
    m_p1 = QVector3D(x1, y1, 1);
    m_p1 = QVector3D(x2, y2, 1);
    m_p1 = QVector3D(x3, y3, 1);
}

QColor TrianglePrimitive::color() const
{
    return m_color;
}

QVector3D TrianglePrimitive::p1() const
{
    return m_p1;
}

QVector3D TrianglePrimitive::p2() const
{
    return m_p2;
}

QVector3D TrianglePrimitive::p3() const
{
    return m_p3;
}
