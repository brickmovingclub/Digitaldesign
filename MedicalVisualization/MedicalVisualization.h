#pragma once

#include "ui_MedicalVisualization.h"



class MedicalVisualization : public QMainWindow
{
	Q_OBJECT


public:
	MedicalVisualization(QWidget *parent = Q_NULLPTR);

protected:
	pcl::visualization::PCLVisualizer::Ptr viewer;

private:
	Ui::MedicalVisualizationClass ui;
	//vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	//vtkSmartPointer<vtkRenderWindow> renderwindow =
	//	vtkSmartPointer<vtkRenderWindow>::New();
	QVTKWidget  *m_vtkWidget = new QVTKWidget(this);

//<<<<<<< HEAD
	//CVtkWidget *m_vtkWidget;
	QMdiArea *m_pMdiAreaCenter; 
	QMdiArea *midAreaMacros;
	QTextEdit *m_textEditWidget;
	QVTKWidget  *m_vtkWidget;
	//QVTKWidget  *m_vtkWidget;
private:
	void InitVtk();
	void InitScence();
	void InitToolbar(); //	添加文档编辑工具栏

private slots:
	void on_btnCloseAll_clicked();
	void on_btnClose_clicked();
	void on_btnNext_clicked();
	void on_btnPrevious_clicked();
	void on_btnNewWindow_clicked();
	void on_btnRemoveWindow_clicked();

	//	文档编辑
	void OnActionCut();
	void OnActionPaste();
	void OnActionOpendocument();
	void OnActionSavedocument();

//=======
private slots:
	void ReadFile();		//	打开STL、PLY、的Ascall 或二进制文件
	void SaveFile();		//	保存STL、Ply模型
	void FillHoles();		//	孔洞修补
	void Reconstruction();	//	重建	
	void DrawDomainPoints(); // 查找N维领域点，并高亮显示
	void DrawLeafNodes(); // 绘制叶子节点
	void ShowHoles();
//>>>>>>> d8e72855f7a27854b8af6cb920225bc70af1a531
};
