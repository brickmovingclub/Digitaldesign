#include "stdafx.h"
#include "CVtkWidget.h"


CVtkWidget::CVtkWidget(QWidget *parent):QWidget(parent),m_widget(NULL), m_renderer(NULL)
{
	ui.setupUi(this);
	m_widget = new QVTKWidget(this);
	// add a renderer for a less messy view: The bug appears without it as well.
	m_renderer = vtkRenderer::New();
	m_renderer->SetBackground(0, 0, 1);
	m_widget->GetRenderWindow()->AddRenderer(m_renderer);
}


CVtkWidget::~CVtkWidget()
{
	if (m_renderer)
	{
		m_renderer->Delete();
		m_renderer = NULL;
	}
	if (m_widget)
	{
		delete m_widget;
		m_widget = NULL;
	}

}
