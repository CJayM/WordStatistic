#include "controller.h"

#include <QDebug>
#include <QFile>
#include <filesystem>

Controller::Controller(WordsModel& model, QObject* parent)
    : QObject{parent}
    , _model(model)
{}

void Controller::setQmlRoot(QObject* root)
{
	_root = root;

	if (root == nullptr)
		return;

	QObject::connect(_root, SIGNAL(sgnStart(QString)), this, SLOT(onSgnStart(QString)));
	QObject::connect(_root, SIGNAL(sgnReset()), this, SLOT(onSgnReset()));
}

void Controller::onSgnStart(QString filePath)
{
	qDebug() << "Pressed Start button for file " << filePath;
	_model.generateRandomData();

	if (filePath.startsWith("file:///"))
		filePath = filePath.right(filePath.size() - 8);
	std::filesystem::path path = filePath.toStdU16String();

	QFile file(path);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug() << "ERROR reading file" << path.generic_u16string();
		return;
	}

	QStringList lines;

	QTextStream in(&file);
	in.setEncoding(QStringConverter::System);
	while (!in.atEnd())
	{
		QString line = in.readLine().toLower();
		if (line.isEmpty())
			continue;

		lines.append(line);
	}

	QHash<QString, quint32> statistics;
	for (const auto& line : lines)
	{
		auto parts = line.split(" ");
		for (const auto& part : parts)
		{
			if (part.size() < 3)
				continue;

			if (statistics.contains(part) == false)
				statistics[part] = 0;
			statistics[part] = statistics[part] + 1;
		}
	}

	QList<WordItem> items;
	for (auto i = statistics.cbegin(), end = statistics.cend(); i != end; ++i)
		items.append({i.key(), static_cast<quint16>(i.value())});

	std::sort(
	  items.begin(), items.end(), [](const WordItem& a, const WordItem& b) { return a.count > b.count; });

	_model.reset(items.first(15));
}

void Controller::onSgnReset()
{
	_model.reset({});
}
