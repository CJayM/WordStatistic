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

	if (root == nullptr)
		return;

	connect(_root, SIGNAL(sgnStart(QString)), this, SLOT(onSgnStart(QString)));
	connect(_root, SIGNAL(sgnReset()), this, SLOT(onSgnReset()));
}

void Controller::onSgnStart(QString filePath)
{
	qDebug() << "Pressed Start button for file " << filePath;
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
}

void Controller::onSgnReset()
{
	_model.reset({});
}

void Controller::onStatisticsFinished()
{
	qDebug() << "Statistics calculated";
	auto statistics = _futureWatcher.result();
	if (statistics.empty())
		return;

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

	_model.reset(result);
}

void Controller::onStatisticsPropgressRangeChanged(int minimum, int maximum)
{
	_progressMin = minimum;
	_progressMax = maximum;
}

void Controller::onStatisticsPropgressChanged(int progress)
{
	float percent =  float(progress)/(_progressMax - _progressMin);	
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
