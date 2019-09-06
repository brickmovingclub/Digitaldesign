#include "stdafx.h"
#include "CTableView.h"



CTableView::CTableView(QWidget *parent):QTableView(parent)
{
	

	this->setSelectionBehavior(QAbstractItemView::SelectRows);
	this->horizontalHeader()->setStretchLastSection(true);
	this->horizontalHeader()->setHighlightSections(true);
	this->verticalHeader()->setStretchLastSection(true);
	this->verticalHeader()->setHighlightSections(true);

	this->verticalHeader()->setVisible(true);
	this->setShowGrid(true);
	this->setEditTriggers(QAbstractItemView::NoEditTriggers);
	this->setSelectionMode(QAbstractItemView::ExtendedSelection);

	this->setAlternatingRowColors(true);
	// 把表格的背景调成黄蓝相间
	this->setStyleSheet("QTableView{background-color: rgb(250, 250, 115);"
		"alternate-background-color: rgb(141, 163, 215);}");

	mymodel = new CTableModel();
	this->setModel(mymodel);
	myheader = new CHeaderView;
	myheader->setModel(mymodel);
	this->setHorizontalHeader(myheader);

	this->initHeader();
	mymodel->setModalDatas(&grid_data_list);
	arrow_delegate = new ArrowDelegate();
	this->setItemDelegate(arrow_delegate);

	//	为每一行添加一个委托
	for (int i = 0; i < 5; i++)
	{
		this->setItemDelegateForRow(i, new LineEditDelegate(this));
		QModelIndex index = mymodel->index(i, 1, QModelIndex());
		mymodel->setData(index, i);
	}

	connect(mymodel, SIGNAL(updateCount(int)), this, SLOT(updateCount(int)));
	connect(myheader, SIGNAL(refresh()), this, SLOT(refreshmymodel()));

}

CTableView::~CTableView(void)
{
	if (arrow_delegate) {
		delete arrow_delegate;
		arrow_delegate = NULL;

	}

	if (mymodel) {
		delete mymodel;
		mymodel = NULL;

	}
	grid_data_list.clear();
}

void CTableView::addRow(QStringList rowList)
{
	grid_data_list.append(rowList);
	mymodel->refrushModel();
}

void CTableView::clearAllRow(int row)
{
	this->row = row;
	grid_data_list.clear();
	mymodel->refrushModel();
}

void CTableView::remove()
{
	QModelIndexList model_index_list = this->selectedIndexes();
	int model_count = model_index_list.count();
	if (model_count <= 0)
		return;

	QList<int> list_row;
	for (int i = model_count - 1; i >= 0; i--)
	{
		QModelIndex model_index = model_index_list.at(i);
		int row = model_index.row();
		if (!list_row.contains(row))
			list_row.append(row);
	}

	if (list_row.isEmpty())
		return;

	qSort(list_row);

	for (int i = list_row.count() - 1; i >= 0; i--)
	{
		grid_data_list.removeAt(list_row.at(i));
	}

	mymodel->refrushModel();
}

void CTableView::clear()
{
	grid_data_list.clear();
	mymodel->refrushModel();
}

int CTableView::rowCount()
{
	return mymodel->rowCount(QModelIndex());
}

void CTableView::initHeader()
{
	QStringList horizonHeader;
	horizonHeader << "Value"<<"Unit";
	//horizonHeader << "NO" << "Time" << "UE" << "S-ENB" << "T-ENB" << "S-MME" << "T-MME" << "SGSN"
	//	<< "S-SGW" << "T-SGW" << "PGW/GGSN" << "HSS/EIR" << "PCRF" << "AAA/ALP" << "AF";
	mymodel->setHorizontalHeaderList(horizonHeader);
	    //MyHeader *h = new MyHeader(this->horizontalHeader());
	QStringList verticalHeader;
	verticalHeader << "Area" << "Volume" << "Number of facet" << "Number of vertex" << "number of hole";
	mymodel->setVerticalHeaderList(verticalHeader);


}


void CTableView::refreshmymodel()
{
	mymodel->refrushModel();
}
