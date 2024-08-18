#pragma once

#include "words_model.h"

#include <QObject>

class Controller : public QObject
{
	Q_OBJECT
  public:
    explicit Controller(WordsModel& model, QObject* parent = nullptr);

  signals:
  public slots:
    void onSgnStart(QString filePath);
    void onSgnReset();

  private:
    WordsModel& _model;
};

