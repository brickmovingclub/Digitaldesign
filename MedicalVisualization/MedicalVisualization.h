#pragma once
<<<<<<< HEAD


#include "ui_MedicalVisualization.h"

=======
#include "stdafx.h"
#include <QtWidgets/QMainWindow>
#include "ui_MedicalVisualization.h"

#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType);
>>>>>>> d8e72855f7a27854b8af6cb920225bc70af1a531

class MedicalVisualization : public QMainWindow
{
	Q_OBJECT


public:
	MedicalVisualization(QWidget *parent = Q_NULLPTR);

protected:
	pcl::visualization::PCLVisualizer::Ptr viewer;

private:
	Ui::MedicalVisualizationClass ui;

<<<<<<< HEAD
	//CVtkWidget *m_vtkWidget;
	QMdiArea *m_pMdiAreaCenter; 
	QMdiArea *midAreaMacros;
	QTextEdit *m_textEditWidget;
	
	//QVTKWidget  *m_vtkWidget;
private:
	void InitVtk();
	void InitScence();
	void InitToolbar(); //	����ĵ��༭������

private slots:
	void on_btnCloseAll_clicked();
	void on_btnClose_clicked();
	void on_btnNext_clicked();
	void on_btnPrevious_clicked();
	void on_btnNewWindow_clicked();
	void on_btnRemoveWindow_clicked();

	//	�ĵ��༭
	void OnActionCut();
	void OnActionPaste();
	void OnActionOpendocument();
	void OnActionSavedocument();

=======
private slots:
	void FillHoles();		//	�׶��޲�
	void Reconstruction();	//	�ؽ�	
	void DrawDomainPoints(); // ����Nά����㣬��������ʾ
	void DrawLeafNodes(); // ����Ҷ�ӽڵ�
	void ShowHoles();
>>>>>>> d8e72855f7a27854b8af6cb920225bc70af1a531
};
