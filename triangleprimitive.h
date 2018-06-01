#ifndef TRIANGLEPRIMITIVE_H
#define TRIANGLEPRIMITIVE_H

#include <QColor>
#include <QDebug>
#include <QVector3D>


class TrianglePrimitive
{
    private:
        QVector3D m_p[3];
        QColor m_color;

    public:
        TrianglePrimitive() {}
        TrianglePrimitive(const QColor& color);
        TrianglePrimitive(float x1, float y1,
                          float x2, float y2,
                          float x3, float y3,
                          const QColor& color);
        TrianglePrimitive(const QVector3D& p1,
                          const QVector3D& p2,
                          const QVector3D& p3,
                          const QColor& color);

        QColor color() const;
        QVector3D point(int i) const;

        void setColor(const QColor& col);
        void setPoint(int i, const QVector3D& p);
        void setPoint(int i, float x, float y);

        QVariant toVariant() const;
};

QDebug operator <<(QDebug debug, const TrianglePrimitive& t);

#endif // TRIANGLEPRIMITIVE_H
