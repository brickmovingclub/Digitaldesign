#pragma once
#include <qtableview.h>
#include "CHeaderView.h"
#include "ArrowDelegate.h"
#include "LineEditDelegate.h"
#include "CTableModel.h"


class CTableView :public QTableView
{
	Q_OBJECT

public:
	CTableView(QWidget *parent = 0);
	~CTableView(void);
	void addRow(QStringList rowList);
	void clearAllRow(int row);//Êý¾ÝÇå¿Õ
	int rowCount();
private:
	void initHeader();
private:
	CHeaderView *myheader;
	CTableModel *mymodel;
	QList< QStringList > grid_data_list;
	ArrowDelegate *arrow_delegate;
	int row;


signals:
	void updateCount(int count);

public slots:
	void remove();
	void clear();
	//void changeValue();
	void refreshmymodel();

	//void mouseReleaseEvent(QMouseEvent *event);
};

