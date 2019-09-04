#include "stdafx.h"
#include "CTableView.h"

#include "CStackWidget.h"


CStackWidget::CStackWidget(QWidget *parent):QWidget(parent), m_stack(NULL)
{
	ui.setupUi(this);
	m_stack = new QStackedWidget();
	
	QWidget *tableWidget1 = new CTableView();
	QWidget *tableWidget2 = new CTableView();

	m_stack->addWidget(tableWidget1);
	m_stack->addWidget(tableWidget2);

	m_listWidget.push_back(tableWidget1);
	m_listWidget.push_back(tableWidget2);


	this->setWindowTitle("Macros");
}


CStackWidget::~CStackWidget()
{
	m_listWidget.clear();
	
	if (m_stack)
		delete m_stack;
}
