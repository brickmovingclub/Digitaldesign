#pragma once
#include <qtableview.h>


class CTableView :
	public QTableView
{
	Q_OBJECT

public:
	CTableView(QTableView * parent = Q_NULLPTR);
	~CTableView();
private:
};

