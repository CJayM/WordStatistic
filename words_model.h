#pragma once

#include <QAbstractListModel>

struct WordItem
{
	QString name;
	quint16 count;
};

class WordsModel : public QAbstractListModel
{
    Q_OBJECT

  public:
    enum WordRoles
    {
        NameRole = Qt::UserRole + 1,
        CountRole
    };

	explicit WordsModel(QObject* parent = nullptr);

	void generateRandomData();
	void reset(QList<WordItem> statistics);

	// QAbstractItemModel interface
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QHash<int, QByteArray> roleNames() const override;

  private:
    QList<WordItem> _data;
};
