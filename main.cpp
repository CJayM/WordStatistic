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

	QQmlContext* context = engine.rootContext();
	context->setContextProperty("wordsModel", &model);

	const QUrl url(QStringLiteral("qrc:/word_statistics/main.qml"));
	QObject::connect(
	  &engine,
	  &QQmlApplicationEngine::objectCreated,
	  &app,
	  [url, controller](QObject* obj, const QUrl& objUrl) {
		  if (!obj && url == objUrl)
			  QCoreApplication::exit(-1);

		  QObject::connect(obj, SIGNAL(sgnStart(QString)), controller.get(), SLOT(onSgnStart(QString)));
		  QObject::connect(obj, SIGNAL(sgnReset()), controller.get(), SLOT(onSgnReset()));
	  },
	  Qt::QueuedConnection);
	engine.load(url);

	return app.exec();
}
