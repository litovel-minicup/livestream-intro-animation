#ifndef TRIANGLESLOADER_H
#define TRIANGLESLOADER_H

#include <QMap>
#include <triangleprimitive.h>


using MappedTrianglePrimitives = QMap<int, TrianglePrimitive>;

class TrianglesLoader
{
    public:
        static MappedTrianglePrimitives load(const QString& filename, QPointF translation = QPointF());
};

#endif // TRIANGLESLOADER_H
