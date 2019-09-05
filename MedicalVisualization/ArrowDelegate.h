#pragma once
#include <qitemdelegate.h>
class ArrowDelegate :
	public QItemDelegate
{
	Q_OBJECT
public:
	ArrowDelegate(QObject* parent = 0);
	virtual void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
	int Getg_x()const {
		return g_x;
	}
protected:

private:
	//
	int g_x;
};

