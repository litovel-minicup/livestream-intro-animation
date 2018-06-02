#ifndef TRIANGLEITEM_H
#define TRIANGLEITEM_H

#include <QObject>
#include <QPolygonF>
#include <QQuickPaintedItem>
#include <QVariantAnimation>
#include <QVector>


class TriangleItem : public QQuickPaintedItem
{
    Q_OBJECT

    private:
        qreal m_interpolation;
        bool m_runColorAnimation = true;
        QColor m_animatedColor;
        QPolygonF m_polygon;
        QColor m_color;
        QVector<QPointF> m_srcPoints;
        QVector<QPointF> m_destPoints;
        QVariantAnimation* m_colorAnimation;

    public:
        TriangleItem(QQuickItem* parent = nullptr);

        void paint(QPainter* painter) override;

        QColor color() const;
        QVector<QPointF> srcPoints() const;
        QVector<QPointF> destPoints() const;

    private slots:
        void setUpColorAnimation();
        void setUpContent();

    public slots:
        void setInterpolation(qreal i);
        void setColor(QColor color);
        void setSrcPoints(QVector<QPointF> srcPoints);
        void setDestPoints(QVector<QPointF> destPoints);

    signals:
        void colorChanged(QColor color);
        void srcPointsChanged(QVector<QPointF> srcPoints);
        void destPointsChanged(QVector<QPointF> destPoints);
        void interpolationChanged(qreal i);
};

#endif // TRIANGLEITEM_H
