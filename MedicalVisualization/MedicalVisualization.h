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
	void FillHoles();		//	孔洞修补
	void Reconstruction();	//	重建	
	void DrawDomainPoints(); // 查找N维领域点，并高亮显示
	void DrawLeafNodes(); // 绘制叶子节点
	void ShowHoles();
};
