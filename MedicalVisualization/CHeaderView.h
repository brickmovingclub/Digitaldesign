#pragma once
#include <qheaderview.h>
class CHeaderView :
	public QHeaderView
{
	Q_OBJECT

public:
	CHeaderView(QWidget *parent = 0);//:QHeaderView(Qt::Horizontal, parent)

protected:
	void mouseReleaseEvent(QMouseEvent *e);

signals:
	void refresh();
};

