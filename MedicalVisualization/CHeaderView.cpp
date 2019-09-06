#include "stdafx.h"
#include "CHeaderView.h"


CHeaderView::CHeaderView(QWidget *parent) :QHeaderView(Qt::Horizontal, parent)
{

}

void CHeaderView::mouseReleaseEvent(QMouseEvent *e)
{
	emit refresh();
}
