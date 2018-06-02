#ifndef TRIANGLECONTAINER_H
#define TRIANGLECONTAINER_H

#include <QQuickItem>
#include <triangleitem.h>
#include <piecesmanager.h>


class TrianglesContainer : public QQuickItem
{
        Q_OBJECT
        Q_PROPERTY(qreal piecesRotation READ piecesRotation WRITE setPiecesRotation NOTIFY piecesRotationChanged)

    private:
        PiecesManager* m_pieceManager;
        QVector<TriangleItem*> m_triangles;
        QVector<TrianglePrimitive> m_srcPolygons;
        QVector<TrianglePrimitive> m_destPolygons;
        qreal m_piecesRotation;
        QVariantAnimation* m_interpolationAnimation;

    public:
        TrianglesContainer(QQuickItem* parent = nullptr);
        qreal piecesRotation() const;

    public slots:
        void interpolate(bool inverted = false);
        void initTriangles(const QVector<TrianglePrimitive>& srcPolygons,
                           const QVector<TrianglePrimitive>& destPolygons);
        void setPiecesRotation(qreal piecesRotation);
    signals:
        void piecesRotationChanged(qreal piecesRotation);
        void interpolationRequest(qreal i);
};

#endif // TRIANGLECONTAINER_H
