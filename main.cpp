#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "piecesmanager.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    PiecesManager pieceManager(":/low-poly.svg", ":/low-poly-disasembled.svg");

    engine.rootContext()->setContextProperty("pieceManager", &pieceManager);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
