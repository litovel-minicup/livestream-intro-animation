#include "trianglecontainer.h"
#include <trianglesloader.h>

TrianglesContainer::TrianglesContainer(QQuickItem* parent): QQuickItem(parent)
{
    m_cloudedPolygons = TrianglesLoader::load(":/low-poly-couded.svg").values().toVector();
    m_disasmPolygons = TrianglesLoader::load(":/low-poly-disasembled.svg").values().toVector();
    m_asmPolygons = TrianglesLoader::load(":/low-poly.svg").values().toVector();
    this->initTriangles();
}

qreal TrianglesContainer::piecesRotation() const
{
    return m_piecesRotation;
}

void TrianglesContainer::interpolateToDisAsm(qreal currentAngle, bool inverted)
{
    emit this->setTransformationMatrixRequest(QMatrix4x4 {});
    emit this->interpolationRequest(inverted);
}

void TrianglesContainer::interpolateToAsm(qreal currentAngle, bool inverted)
{
    for(TriangleItem* item: m_triangles) {
        const int i = m_triangles.indexOf(item);
        item->setRawInterpolation(0);
        item->setSrcPoints(m_disasmPolygons.at(i).points());
        item->setDestPoints(m_asmPolygons.at(i).points());
    }

    const QPointF origin { 650, 295 };
    m_currentTransformation.setToIdentity();
    m_currentTransformation.translate(origin.x(), origin.y());
    m_currentTransformation.rotate(currentAngle, QVector3D { 0., 0., 1. });
    m_currentTransformation.translate(-origin.x(), -origin.y());

    emit this->setTransformationMatrixRequest(m_currentTransformation);
    emit this->interpolationRequest(inverted);
}

void TrianglesContainer::initTriangles()
{
    for(int i = 0; i < m_cloudedPolygons.length(); i++) {
        const TrianglePrimitive triangleData = m_cloudedPolygons.at(i);
        const TrianglePrimitive destTriangleData = m_disasmPolygons.at(i);

        TriangleItem* item = new TriangleItem { this };
        item->setColor(triangleData.color());
        item->setSrcPoints(triangleData.points());
        item->setDestPoints(destTriangleData.points());
        item->setAnimationDelay(i * 10);
        m_triangles.append(item);

        connect(this, &TrianglesContainer::interpolationRequest,
                item, &TriangleItem::interpolate);
        connect(this, &TrianglesContainer::setTransformationMatrixRequest,
                item, &TriangleItem::setCurrentTransformation);
    }
}

void TrianglesContainer::setPiecesRotation(qreal piecesRotation)
{
    if (qFuzzyCompare(m_piecesRotation, piecesRotation))
        return;

    m_piecesRotation = piecesRotation;
    emit piecesRotationChanged(m_piecesRotation);
}
