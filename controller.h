#pragma once

#include "words_model.h"

#include <QFuture>
#include <QObject>

class Controller : public QObject
{
	Q_OBJECT
  public:
    explicit Controller(WordsModel& model, QObject* parent = nullptr);

    void setQmlRoot(QObject* root);

  signals:
  public slots:
    void onSgnStart(QString filePath);
    void onSgnReset();

  protected:


  private:
    WordsModel& _model;
    QObject* _root;
    QFuture<QList<WordItem>> _futureParse;
};

QList<WordItem> parseFile(QString path);

