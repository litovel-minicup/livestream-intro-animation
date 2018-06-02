#ifndef PIECESMANAGER_H
#define PIECESMANAGER_H

#include <QObject>
#include "trianglesloader.h"


class PiecesManager : public QObject
{
    Q_OBJECT
    private:
        MappedTrianglePrimitives m_assembledTriangles;
        MappedTrianglePrimitives m_disassembledTriangles;

    public:
        explicit PiecesManager(const QString& assembledPiecesFilePath,
                               const QString& disassembledPiecesFilePath,
                               QObject *parent = nullptr);
    public slots:
        QVector<TrianglePrimitive> assembledTriangles() const;
        QVector<TrianglePrimitive> disassembledTriangles() const;
        QVariantList vAssembledTriangles() const;
        QVariantList vDisassembledTriangles() const;
};

#endif // PIECESMANAGER_H
