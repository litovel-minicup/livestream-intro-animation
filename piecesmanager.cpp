#include "piecesmanager.h"

PiecesManager::PiecesManager(const QString &assembledPiecesFilePath,
                             const QString &disassembledPiecesFilePath,
                             QObject *parent): QObject { parent }
{
    m_assembledTriangles = TrianglesLoader::load(assembledPiecesFilePath);
    m_disassembledTriangles = TrianglesLoader::load(
                disassembledPiecesFilePath, QPointF(0, 120));
}

QVariant PiecesManager::interpolated(float i, bool inverted)
{
    QVariantList points;
    MappedTrianglePrimitives srcPolygons = m_disassembledTriangles;
    MappedTrianglePrimitives destPolygons = m_assembledTriangles;
    if(inverted)
        qSwap(srcPolygons, destPolygons);

    for(int key: m_assembledTriangles.keys()) {
        const TrianglePrimitive srcTriangle = srcPolygons[key];
        const TrianglePrimitive desTriangle = destPolygons[key];
        TrianglePrimitive interpolatedTriangle { srcTriangle.color() };
        for(int j = 0; j <3; j++) {
            interpolatedTriangle.setPoint(j,
                                          srcTriangle.point(j) +
                                          (desTriangle.point(j) -
                                           srcTriangle.point(j)) * i);
        }

        points.append(interpolatedTriangle.toVariant());
    }

    return points;
}
