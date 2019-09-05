#include "stdafx.h"
#include "ArrowDelegate.h"


ArrowDelegate::ArrowDelegate(QObject *parent)
	: QItemDelegate(parent)
{
	g_x = 0;
}

void ArrowDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	int g_x = this->Getg_x();
	int row = index.row();
	int x = option.rect.x();
	int y = option.rect.y();
	int width = option.rect.width();
	int height = option.rect.height();
	QPen pen_black;
	pen_black.setWidth(2);
	pen_black.setColor(QColor(Qt::black));
	QStyleOptionViewItem myOption = option;

	if (index.column() == 2)//UE
	{
		QPainterPath path_UE;

		QPoint One;
		QPoint Two;
		//        pen.setWidth(2);
		One.setX(x + width / 2);
		One.setY(y);
		Two.setX(x + width / 2);
		Two.setY(y + height);
		path_UE.moveTo(One);
		path_UE.lineTo(Two);
		painter->setPen(pen_black);
		painter->drawPath(path_UE);
	}

	if (index.column() == 3)
	{
		g_x = x + width / 2;//get the begin
		QPainterPath path_SENB;

		QPoint One;
		QPoint Two;
		One.setX(x + width / 2);
		One.setY(y);
		Two.setX(x + width / 2);
		Two.setY(y + height);
		path_SENB.moveTo(One);
		path_SENB.lineTo(Two);
		//        pen.setColor(QColor(Qt::black));
		painter->setPen(pen_black);
		painter->drawPath(path_SENB);
		//        g_y = y + height / 2;
	}
	if (index.column() == 4)
	{
		QString str4 = index.model()->data(index, Qt::DisplayRole).toString();
		if (!str4.isEmpty())
		{
			QPainterPath path_TENB;

			QPoint One;
			QPoint Two;
			//        pen.setWidth(2);
			One.setX(x + width / 2);
			One.setY(y);
			Two.setX(x + width / 2);
			Two.setY(y + height);
			path_TENB.moveTo(One);
			path_TENB.lineTo(Two);
			painter->setPen(pen_black);
			painter->drawPath(path_TENB);
		}
	}

	if (index.column() == 5)
	{
		QPainterPath path, path_SMME;
		QPen pen;
		QPoint One;
		QPoint Two;
		//        pen5.setWidth(2);
		One.setX(x + width / 2);
		One.setY(y);
		Two.setX(x + width / 2);
		Two.setY(y + height);
		path_SMME.moveTo(One);
		path_SMME.lineTo(Two);
		//        pen5.setColor(QColor(Qt::black));
		painter->setPen(pen_black);
		painter->drawPath(path_SMME);

		QString str = index.model()->data(index, Qt::DisplayRole).toString();
		if (str.isEmpty())
			return;//break this turn
		QStringList strList = str.split("+");
		QString text = strList.at(0);
		int direction = strList.at(1).toInt();

		myOption.displayAlignment = Qt::AlignCenter;

		QRectF rect;
		pen.setWidth(1);
		if (direction)
		{
			pen.setColor(QColor(255, 0, 0));//red
			//            One.setX(x);
			//            One.setY(y + 3 * height / 4);
			One.setX(g_x);
			One.setY(y + 3 * height / 4);
			Two.setX(x + width / 2);
			Two.setY(y + 3 * height / 4);
			//            painter->drawText(One,text);
		}
		else
		{
			pen.setColor(QColor(0, 0, 255));
			//            Two.setX(x);
			//            Two.setY(y + 3 * height / 4);
			Two.setX(g_x);
			Two.setY(y + 3 * height / 4);
			One.setX(x + width / 2);
			One.setY(y + 3 * height / 4);
			//            painter->drawText(Two,text);
		}

		int Height = 20;
		//        QPoint Three(x + width / 2 , y + height / 3);

		double slopy, cosy, siny;
		double Par = Height / 2;
		slopy = atan2((One.y() - Two.y()), (One.x() - Two.x()));
		cosy = cos(slopy);
		siny = sin(slopy);


		path.moveTo(One);
		path.lineTo(Two);


		path.moveTo(Two);
		path.lineTo(Two.x() + int(Par * cosy - (Par / 2.0 * siny)),
			Two.y() + int(Par * siny + (Par / 2.0 * cosy)));
		path.moveTo(Two);
		path.lineTo(Two.x() + int(Par * cosy - (Par / 2.0 * siny)),
			Two.y() - int(Par * siny + (Par / 2.0 * cosy)));

		painter->setPen(pen);
		painter->drawPath(path);

		//        pen.setColor(QColor(Qt::black));
		painter->setPen(pen_black);
		rect.setTopLeft(QPointF(g_x, y));
		rect.setBottomRight(QPointF(x + width / 2, y + height / 2));
		//        rect(QPointF(g_x,y),QPointF(x + width / 2,y + height / 2));
		QTextOption textOption;
		textOption.setAlignment(Qt::AlignCenter);
		painter->drawText(rect, text, textOption);
	}
	else
	{
		return QItemDelegate::paint(painter, option, index);
	}
}