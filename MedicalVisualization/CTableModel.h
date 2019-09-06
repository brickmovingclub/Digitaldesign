#pragma once
#include <qabstractitemmodel.h>
class CTableModel :
	public QAbstractTableModel
{
	Q_OBJECT

public:

	CTableModel(QObject *parent = 0);
	~CTableModel(void);
	void setHorizontalHeaderList(QStringList horizontalHeaderList);
	void setVerticalHeaderList(QStringList verticalHeaderList);
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	void setModalDatas(QList< QStringList > *rowlist);
	void refrushModel();
private:

	QStringList horizontal_header_list;
	QStringList vertical_header_list;
	QList< QStringList > *arr_row_list;
protected:

signals:

	void updateCount(int count);
};

