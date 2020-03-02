#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>

#include "statusbar.h"
#include "QMorse.h"
#include "comMorse.h"

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QGuiApplication app(argc, argv);

	// set style
	QQuickStyle::setStyle("Material");


	// set status bar
	qmlRegisterType<StatusBar>("StatusBar", 0, 1, "StatusBar");

	QQmlApplicationEngine engine;
	const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
					 &app, [url](QObject *obj, const QUrl &objUrl) {
		if (!obj && url == objUrl)
			QCoreApplication::exit(-1);
	}, Qt::QueuedConnection);
	engine.load(url);

	// set the treeMorse;
	int cursor = 0;
	treeNode* treeMorse = createMorseTree(dictio, cursor);

	// set QML objects Morse
	comMorse comMorse;
	comMorse.setTreeMorse(treeMorse);

	engine.rootContext()->setContextProperty("comMorse", &comMorse);

	return app.exec();
}
