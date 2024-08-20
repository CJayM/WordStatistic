#pragma once

#include "words_model.h"

#include <QFuture>
#include <QFutureWatcher>
#include <QObject>

using StatisticsFutureWatcher = QFutureWatcher<QHash<QString, quint32>>;

class Controller : public QObject
{
	Q_OBJECT
  public:
    explicit Controller(WordsModel& model, QObject* parent = nullptr);

    void setQmlRoot(QObject* root);

  signals:
  public slots:
    void onSgnStart(QString filePath);
    void onSgnPause();
    void onSgnReset();

  private slots:
    void onStatisticsFinished();
    void onStatisticsPropgressRangeChanged(int minimum, int maximum);
    void onStatisticsPropgressChanged(int progress);

  protected:


  private:
    WordsModel& _model;
    QObject* _root;
    QFuture<QList<QString>> _futureParseFile;
    StatisticsFutureWatcher _futureWatcher;
    QThreadPool _pool;
    int _progressMin;
    int _progressMax;
};

QList<QString> parseFile(QString path);
bool filterSmallLines(const QString& line, bool needSlow);
void mapWordsStatistics(QHash<QString, quint32>& result, const QString& line);

