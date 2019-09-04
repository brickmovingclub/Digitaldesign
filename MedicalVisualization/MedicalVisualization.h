#pragma once
#include "stdafx.h"
#include <QtWidgets/QMainWindow>
#include "ui_MedicalVisualization.h"

#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType);

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
	void FillHoles();		//	�׶��޲�
	void Reconstruction();	//	�ؽ�	
	void DrawDomainPoints(); // ����Nά����㣬��������ʾ
	void DrawLeafNodes(); // ����Ҷ�ӽڵ�
	void ShowHoles();
};
