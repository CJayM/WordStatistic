#include "controller.h"
#include <QDebug>

Controller::Controller(WordsModel& model, QObject* parent)
    : QObject{parent}
    , _model(model)
{}

void Controller::onSgnStart()
{
	qDebug() << "Pressed Start button";
	_model.generateRandomData();
}
