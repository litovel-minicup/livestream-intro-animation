#include "piecesmanager.h"

PiecesManager::PiecesManager(const QString &assembledPiecesFilePath,
                             const QString &disassembledPiecesFilePath,
                             QObject *parent): QObject { parent }
{
    m_assembledTriangles = TrianglesLoader::load(assembledPiecesFilePath);
    m_disassembledTriangles = TrianglesLoader::load(
                disassembledPiecesFilePath, QPointF(0, 120));
}

QVector<TrianglePrimitive> PiecesManager::assembledTriangles() const
{
    return m_assembledTriangles.values().toVector();
}

QVector<TrianglePrimitive> PiecesManager::disassembledTriangles() const
{
    return m_disassembledTriangles.values().toVector();
}

QVariantList PiecesManager::vAssembledTriangles() const
{
    QVariantList res;
    for(auto key: m_assembledTriangles.keys())
        res.append(m_assembledTriangles[key].toVariant());
    return res;
}

QVariantList PiecesManager::vDisassembledTriangles() const
{
    QVariantList res;
    for(auto key: m_disassembledTriangles.keys())
        res.append(m_disassembledTriangles[key].toVariant());
    return res;
}
