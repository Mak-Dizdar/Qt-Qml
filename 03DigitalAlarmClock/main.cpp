#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include <qdatetime.h>
#include <customlogger.h>
#include "sensorboard.h"
#include "alarmlogic.h"

//comment/uncomment this depending on configuration
//I tried to do it automatically however adding arguments made qmake fail to find files...

//#define RASPI


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    qInstallMessageHandler(CustomLogger::customLog);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));

   SensorBoard sensor;
   AlarmLogic alarm;

   engine.rootContext()->setContextProperty("timer", &alarm);
   engine.rootContext()->setContextProperty("sensor", &sensor);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);


    engine.load(url);

    return app.exec();
}
