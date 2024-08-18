#include "words_model.h"
#include <experimental/random>

WordsModel::WordsModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

void WordsModel::generateRandomData()
{
	beginResetModel();
	_data.clear();
	static const QStringList names{"First word",
								   "Second word",
								   "Third word",
								   "Fourth word",
								   "Fifth word",
								   "Sixth word",
								   "Seventh word",
								   "Eighth word",
								   "Ninth word",
								   "Tenth word",
								   "Eleventh word",
								   "Twelfth word",
								   "Thirteenth word",
								   "Fourteenth word",
								   "Fifteenth word"};

	for (const auto& name: names)
	{
		_data.append(WordItem{name, static_cast<quint16>(std::experimental::randint(20, 100))});
	}
	endResetModel();
}

void WordsModel::reset()
{
	beginResetModel();
	_data.clear();
	endResetModel();
}

int WordsModel::rowCount(const QModelIndex& parent) const
{
	if (parent.isValid())
		return 0;

	return _data.size();
}

QVariant WordsModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
	{
		return QVariant();
	}

	const auto& item = _data[index.row()];

	switch (role)
	{
	case NameRole:
		return item.name;
	case CountRole:
		return item.count;
	default:
		return QVariant();
	}
}

QHash<int, QByteArray> WordsModel::roleNames() const
{
	QHash<int, QByteArray> roles;
	roles[NameRole] = "Name";
	roles[CountRole] = "Count";
	return roles;
}
