#pragma once

#include "ui_vtkWidget.h"
class CVtkWidget:public QWidget
{
	Q_OBJECT
public:
	CVtkWidget(QWidget *parent = Q_NULLPTR);
	~CVtkWidget();
private:
	Ui::VtkWidget ui;
	QVTKWidget * m_widget;
	vtkRenderer* m_renderer;
};

