#ifndef TRIANGLEPRIMITIVE_H
#define TRIANGLEPRIMITIVE_H

#include <QColor>
#include <QDebug>
#include <QPointF>


class TrianglePrimitive
{
    private:
        QVector<QPointF> m_p;
        QColor m_color;

    public:
        TrianglePrimitive() {}
        TrianglePrimitive(const QColor& color);
        TrianglePrimitive(qreal x1, qreal y1,
                          qreal x2, qreal y2,
                          qreal x3, qreal y3,
                          const QColor& color);
        TrianglePrimitive(const QPointF& p1,
                          const QPointF& p2,
                          const QPointF& p3,
                          const QColor& color);

        QColor color() const;
        QPointF point(int i) const;

        void setColor(const QColor& col);
        void setPoint(int i, const QPointF& p);
        void setPoint(int i, qreal x, qreal y);

        QVariant toVariant() const;
        QVector<QPointF> points() const;
};

QDebug operator <<(QDebug debug, const TrianglePrimitive& t);

#endif // TRIANGLEPRIMITIVE_H
