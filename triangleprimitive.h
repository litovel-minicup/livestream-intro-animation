#ifndef TRIANGLEPRIMITIVE_H
#define TRIANGLEPRIMITIVE_H

#include <QColor>
#include <QVector3D>


class TrianglePrimitive
{
    private:
        QVector3D m_p1;
        QVector3D m_p2;
        QVector3D m_p3;
        QColor m_color;

    public:
        TrianglePrimitive(float x1, float y1,
                          float x2, float y2,
                          float x3, float y3,
                          const QColor& color);

        QColor color() const;
        QVector3D p1() const;
        QVector3D p2() const;
        QVector3D p3() const;
};

#endif // TRIANGLEPRIMITIVE_H
