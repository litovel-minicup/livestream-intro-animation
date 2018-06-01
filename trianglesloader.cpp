#include "trianglesloader.h"
#include <QFile>
#include <QDebug>
#include <QDomDocument>

MappedTrianglePrimitives TrianglesLoader::load(const QString &filename)
{
    // load file
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)) {
        file.close();
        qWarning() << "Could not open file" << filename;
        return MappedTrianglePrimitives{};
    }

    // parse xml
    QDomDocument doc;
    if(!doc.setContent(&file)) {
        file.close();
        qWarning() << "Invalid svg in file" << filename;
        return MappedTrianglePrimitives{};
    }

    file.close();

    // parse polygons
    const QDomElement root = doc.documentElement();
    QDomElement polygonElem = root.firstChildElement("polygon");
    MappedTrianglePrimitives result;

    while(!polygonElem.isNull()) {
        const int id { polygonElem.attribute("id").replace("a", "").toInt() };
        const QColor color { polygonElem.attribute("fill") };
        const QString rawPointsData { polygonElem.attribute("points") };

        QStringList rawSplittedPointsData { rawPointsData.split(" ") };
        rawSplittedPointsData.removeAll("");

        // process primitive
        TrianglePrimitive triangle { color };
        for(int i = 0; i < 3; i++) {
            const QStringList rawPointData = rawSplittedPointsData[i].split(",");
            triangle.setPoint(i, QVector3D {rawPointData[0].toFloat(),
                                            rawPointData[1].toFloat(),
                                            1.} );
        }

        // map
        result[id] = triangle;

        polygonElem = polygonElem.nextSiblingElement("polygon");
    }

    return result;
}
