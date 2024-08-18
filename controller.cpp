#include "controller.h"
#include <QDebug>

Controller::Controller(WordsModel& model, QObject* parent)
    : QObject{parent}
    , _model(model)
{}

void Controller::onSgnStart(QString filePath)
{
	qDebug() << "Pressed Start button for file " << filePath;
	_model.generateRandomData();
}
