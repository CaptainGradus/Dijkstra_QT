#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "graphdata.h"
#include "graph.h"
#include "graphdatavector.h"
#include "graphmatrixmodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<GraphMatrixModel>("Graph", 1, 0, "GraphModel");
    qmlRegisterUncreatableType<GraphDataVector>("Graph", 1, 0, "GraphDataVector",
                                                  QStringLiteral("GraphDataVector should not be created in QML"));
    qmlRegisterUncreatableType<Graph>("Graph", 1, 0, "AlgGraph",
                                                  QStringLiteral("Graph should not be created in QML"));
    qmlRegisterUncreatableType<GraphData>("Graph", 1, 0, "GraphData",
                                                  QStringLiteral("GraphData should not be created in QML"));

    GraphDataVector graphData;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("graphData"), &graphData);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
