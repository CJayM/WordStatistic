#include "controller.h"
#include "words_model.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <memory>

int main(int argc, char* argv[])
{
	QGuiApplication app(argc, argv);
	app.setOrganizationName("Noname");
	app.setOrganizationDomain("nn.ru");
	app.setApplicationName("WordStatistics");

	QQuickStyle::setStyle("Material");

	WordsModel model;
	auto controller = std::make_shared<Controller>(model);

	QQmlApplicationEngine engine;
	engine.setInitialProperties({
	  {"wordsModel", QVariant::fromValue(&model)},
	});

	const QUrl url(QStringLiteral("qrc:/word_statistics/Main.qml"));
	QObject::connect(
	  &engine,
	  &QQmlApplicationEngine::objectCreated,
	  &app,
	  [url, controller](QObject* obj, const QUrl& objUrl) {
		  if (!obj && url == objUrl)
			  QCoreApplication::exit(-1);

		  controller->setQmlRoot(obj);
	  },
	  Qt::QueuedConnection);
	engine.load(url);

	return app.exec();
}
