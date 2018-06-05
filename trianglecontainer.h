#ifndef TRIANGLECONTAINER_H
#define TRIANGLECONTAINER_H

#include <QQuickItem>
#include <triangleitem.h>
#include <QMatrix4x4>
#include <triangleprimitive.h>


class TrianglesContainer : public QQuickItem
{
        Q_OBJECT
        Q_PROPERTY(qreal piecesRotation READ piecesRotation WRITE setPiecesRotation NOTIFY piecesRotationChanged)

    private:
        QVector<TriangleItem*> m_triangles;
        QVector<TrianglePrimitive> m_cloudedPolygons;
        QVector<TrianglePrimitive> m_disasmPolygons;
        QVector<TrianglePrimitive> m_asmPolygons;
        qreal m_piecesRotation;
        QMatrix4x4 m_currentTransformation;

    public:
        TrianglesContainer(QQuickItem* parent = nullptr);
        qreal piecesRotation() const;

    private slots:
    public slots:
        void interpolateToDisAsm(qreal currentAngle = 0., bool inverted = false);
        void interpolateToAsm(qreal currentAngle = 0., bool inverted = false);
        void initTriangles();
        void setPiecesRotation(qreal piecesRotation);

    signals:
        void piecesRotationChanged(qreal piecesRotation);
        void interpolationRequest(bool inverted = false);
        void setTransformationMatrixRequest(const QMatrix4x4& currentTransformations = QMatrix4x4{});
};

#endif // TRIANGLECONTAINER_H
