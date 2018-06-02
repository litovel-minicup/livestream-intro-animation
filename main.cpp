#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "piecesmanager.h"
#include "triangleitem.h"
#include "trianglecontainer.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<TriangleItem>("TriangleItem", 1, 0, "TriangleItem");
    qmlRegisterType<TrianglesContainer>("TriangleContainer", 1, 0, "TriangleContainer");

//    engine.rootContext()->setContextProperty("pieceManager", &pieceManager);


    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
