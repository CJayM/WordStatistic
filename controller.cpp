#include "controller.h"

#include <QDebug>
#include <QFile>
#include <QtConcurrent>
#include <filesystem>

Controller::Controller(WordsModel& model, QObject* parent)
    : QObject{parent}
    , _model(model)
{
	connect(&_futureWatcher, &StatisticsFutureWatcher::finished, this, &Controller::onStatisticsFinished);
	connect(&_futureWatcher,
			&StatisticsFutureWatcher::progressRangeChanged,
			this,
			&Controller::onStatisticsPropgressRangeChanged);
	connect(&_futureWatcher,
			&StatisticsFutureWatcher::progressValueChanged,
			this,
			&Controller::onStatisticsPropgressChanged);
}

void Controller::setQmlRoot(QObject* root)
{
	_root = root;

	if (_root == nullptr)
		return;

	connect(_root, SIGNAL(sgnStart(QString)), this, SLOT(onSgnStart(QString)));
	connect(_root, SIGNAL(sgnPause()), this, SLOT(onSgnPause()));
	connect(_root, SIGNAL(sgnReset()), this, SLOT(onSgnReset()));

	_root->setProperty("state", "NORMAL");
	_root->setProperty("proccessProgress", 0);
}

void Controller::onSgnStart(QString filePath)
{
	// если была нажата пауза
	if (_futureWatcher.isSuspended())
	{
		_futureWatcher.resume();
		_root->setProperty("state", "LOADING");
		return;
	}

	// если новый запуск
	_futureParseFile = QtConcurrent::run(parseFile, filePath);
	auto futureWatcher = &_futureWatcher;
	auto pool = &_pool;

	_futureParseFile
	  .then([futureWatcher, pool](QList<QString> lines) {
		  if (futureWatcher->isRunning())
			  futureWatcher->cancel();
		  futureWatcher->setFuture(
			QtConcurrent::filteredReduced(pool,
										  lines,
										  filterSmallLines,
										  mapWordsStatistics,
										  QtConcurrent::UnorderedReduce | QtConcurrent::SequentialReduce));
	  })
	  .onCanceled([] { qDebug() << "Canceled"; })
	  .onFailed([] { qDebug() << "Failed"; });

	_root->setProperty("state", "LOADING");
}

void Controller::onSgnPause()
{
	if (_futureWatcher.isRunning())
	{
		_futureWatcher.suspend();
		_root->setProperty("state", "PAUSED");
	}
}

void Controller::onSgnReset()
{	
	if (_futureWatcher.isRunning())
		_futureWatcher.cancel();
	else
		_model.reset({});

	_root->setProperty("state", "NORMAL");
	_root->setProperty("proccessProgress", 0);
}

void Controller::onStatisticsFinished()
{	
	if (_futureWatcher.isCanceled()){
		_model.reset({});
		_root->setProperty("state", "NORMAL");
		_root->setProperty("proccessProgress", 0);
		_root->setProperty("maxCount", 0);
		return;
	}

	if (_futureWatcher.isFinished())
	{
		auto statistics = _futureWatcher.result();
		if (statistics.empty())
		{
			return;
		}

		QList<WordItem> items;
		for (auto i = statistics.cbegin(), end = statistics.cend(); i != end; ++i)
			items.append({i.key(), static_cast<quint16>(i.value())});

		std::sort(
		  items.begin(), items.end(), [](const WordItem& a, const WordItem& b) { return a.count > b.count; });

		QList<WordItem> result;
		result.reserve(15);
		for (int i = 0; i < 15; ++i)
		{
			auto it = items.cbegin();
			int random = rand() % items.size();
			std::advance(it, random);
			result.append(*it);
		}
		_root->setProperty("state", "NORMAL");
		_root->setProperty("proccessProgress", 0);

		int maxCount = result.first().count;
		for(const auto& item: result)
			if (item.count > maxCount)
				maxCount = item.count;
		_root->setProperty("maxCount", maxCount);

		_model.reset(result);
	}
}

void Controller::onStatisticsPropgressRangeChanged(int minimum, int maximum)
{
	_progressMin = minimum;
	_progressMax = maximum;
}

void Controller::onStatisticsPropgressChanged(int progress)
{
	float percent = float(progress) / (_progressMax - _progressMin);
	_root->setProperty("proccessProgress", percent);
}

QList<QString> parseFile(QString filePath)
{
	if (filePath.startsWith("file:///"))
		filePath = filePath.right(filePath.size() - 8);
	std::filesystem::path path = filePath.toStdU16String();

	QFile file(path);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug() << "ERROR reading file" << path.generic_u16string();
		return {};
	}

	QStringList lines;

	QTextStream in(&file);
	in.setEncoding(QStringConverter::System);

	while (!in.atEnd())
		lines.append(in.readLine().toLower());

	return lines;
}

bool filterSmallLines(const QString& line)
{
	// slow code
	int step = 0;
	int _;
	while (step < 1000000)
	{
		++step;
		_ = qSin(qDegreesToRadians(step));
	}

	if (line.size() < 3)
		return false;
	return true;
}

void mapWordsStatistics(QHash<QString, quint32>& result, const QString& line)
{
	auto parts = line.split(" ");
	for (const auto& part : parts)
	{
		if (part.size() < 3)
			continue;

		if (result.contains(part) == false)
			result[part] = 0;
		result[part] = result[part] + 1;
	}
}
