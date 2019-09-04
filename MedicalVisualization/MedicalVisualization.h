#pragma once
#include "stdafx.h"
#include <QtWidgets/QMainWindow>
#include "ui_MedicalVisualization.h"
#include "vtkAutoInit.h"

VTK_MODULE_INIT(vtkRenderingOpenGL2);

VTK_MODULE_INIT(vtkInteractionStyle);
class MedicalVisualization : public QMainWindow
{
	Q_OBJECT


public:
	MedicalVisualization(QWidget *parent = Q_NULLPTR);

protected:
	pcl::visualization::PCLVisualizer::Ptr viewer;

private:
	Ui::MedicalVisualizationClass ui;
private slots:
	void FillHoles();		//	¿×¶´ÐÞ²¹
	void Reconstruction();	//	ÖØ½¨
	void ShowHoles();
};
