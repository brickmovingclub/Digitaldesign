#pragma once

#include "ui_CStackWidget.h"
class CStackWidget :
	public QWidget
{
	Q_OBJECT
public:
	CStackWidget(QWidget *parent = Q_NULLPTR);
	~CStackWidget();
private:
	Ui::StackWidget ui;
	QStackedWidget *m_stack;	//	
	QList<QWidget *> m_listWidget;		//	存储在stackwidget中的窗体
};

