#include "words_model.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>

int main(int argc, char* argv[])
{
	QGuiApplication app(argc, argv);

	QQuickStyle::setStyle("Material");

	WordsModel model;
	model.generateRandomData();
	QQmlApplicationEngine engine;
	QQmlContext* context = engine.rootContext();
	context->setContextProperty("wordsModel", &model);

	const QUrl url(QStringLiteral("qrc:/word_statistics/main.qml"));
	QObject::connect(
	  &engine,
	  &QQmlApplicationEngine::objectCreated,
	  &app,
	  [url](QObject* obj, const QUrl& objUrl) {
		  if (!obj && url == objUrl)
			  QCoreApplication::exit(-1);
	  },
	  Qt::QueuedConnection);
	engine.load(url);

	return app.exec();
}
