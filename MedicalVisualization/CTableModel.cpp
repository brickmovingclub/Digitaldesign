#include "stdafx.h"

#include "CTableModel.h"



CTableModel::CTableModel(QObject *parent)
	: QAbstractTableModel(parent), arr_row_list(NULL)
{

}

CTableModel::~CTableModel(void)
{
	arr_row_list = NULL;
}

void CTableModel::setHorizontalHeaderList(QStringList horizontalHeaderList)
{
	horizontal_header_list = horizontalHeaderList;
}

void CTableModel::setVerticalHeaderList(QStringList verticalHeaderList)
{
	vertical_header_list = verticalHeaderList;
}

int CTableModel::rowCount(const QModelIndex &parent) const
{
	if (vertical_header_list.size() > 0)
		return vertical_header_list.size();

	if (NULL == arr_row_list)
		return 0;
	else
		return arr_row_list->size();
}

int CTableModel::columnCount(const QModelIndex &parent) const
{
	if (horizontal_header_list.size() > 0)
		return horizontal_header_list.size();

	if (NULL == arr_row_list)
		return 0;
	else if (arr_row_list->size() < 1)
		return 0;
	else
		return arr_row_list->at(0).size();
}

QVariant CTableModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (NULL == arr_row_list)
		return QVariant();

	if (arr_row_list->size() < 1)
		return QVariant();

	if (role == Qt::TextAlignmentRole)
	{
		return int(Qt::AlignLeft | Qt::AlignVCenter);
	}
	else if (role == Qt::DisplayRole)
	{
		if (index.row() >= arr_row_list->size())
			return QVariant();
		if (index.column() >= arr_row_list->at(0).size())
			return QVariant();
		return arr_row_list->at(index.row()).at(index.column());
	}
	return QVariant();
}

QVariant CTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			if (horizontal_header_list.size() > section)
				return horizontal_header_list[section];
			else
				return QVariant();
		}
		else
		{
			if (vertical_header_list.size() > section)
				return vertical_header_list[section];
			else
				return QVariant();
		}
	}

	return QVariant();
}

Qt::ItemFlags CTableModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	Qt::ItemFlags flag = QAbstractItemModel::flags(index);

	// flag|=Qt::ItemIsEditable
	return flag;
}

void CTableModel::setModalDatas(QList< QStringList > *rowlist)
{
	arr_row_list = rowlist;
}

void CTableModel::refrushModel()
{
	beginResetModel();
	endResetModel();

	emit updateCount(this->rowCount(QModelIndex()));
}