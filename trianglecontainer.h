#ifndef TRIANGLECONTAINER_H
#define TRIANGLECONTAINER_H

#include <QQuickItem>
#include <triangleitem.h>
#include <piecesmanager.h>
#include <QMatrix4x4>


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
        QMatrix4x4 m_currentTransformation;

    public:
        TrianglesContainer(QQuickItem* parent = nullptr);
        qreal piecesRotation() const;

    public slots:
        void interpolate(qreal currentAngle = 0., bool inverted = false);
        void initTriangles(const QVector<TrianglePrimitive>& srcPolygons,
                           const QVector<TrianglePrimitive>& destPolygons);
        void setPiecesRotation(qreal piecesRotation);
    signals:
        void piecesRotationChanged(qreal piecesRotation);
        void interpolationRequest(qreal i, const QMatrix4x4& currentTransformations = QMatrix4x4{});
};

#endif // TRIANGLECONTAINER_H
