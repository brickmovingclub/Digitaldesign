#include "stdafx.h"
#include "CTableView.h"


CTableView::CTableView(QTableView * parent):QTableView(parent)
{
	QStandardItemModel* model = new QStandardItemModel(this);
	model->setColumnCount(3);
	model->setRowCount(3);

	model->setItem(0, 0, new QStandardItem("ÕÅÈý"));
	model->setItem(0, 1, new QStandardItem("3"));
	model->setItem(0, 2, new QStandardItem("ÄÐ"));
	this->setModel(model);

}


CTableView::~CTableView()
{
}
