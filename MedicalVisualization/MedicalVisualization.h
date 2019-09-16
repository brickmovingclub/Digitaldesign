#pragma once

#include "ui_MedicalVisualization.h"

#include "CTableView.h"
#include "CTerritoryWidget.h"


class MedicalVisualization : public QMainWindow
{
	Q_OBJECT


public:
	MedicalVisualization(QWidget *parent = Q_NULLPTR);

protected:
	pcl::visualization::PCLVisualizer::Ptr viewer;

private:
	Ui::MedicalVisualizationClass ui;
public:
	pcl::PointCloud<pcl::PointXYZ>::Ptr m_cloud;


	QMdiArea *m_pMdiAreaCenter; 
	QMdiArea *midAreaMacros;
	QTextEdit *m_textEditWidget;

	QVTKWidget  *m_vtkWidget;
	CTableView *tablePropretyView;
	CTableView *tableMacrosView;
private:
	void InitVtk();
	void InitScence();
	void InitToolbar(); //	����ĵ��༭������
	void UpdateTableView(const float area,const float volum,const int faceNum,const int vertexNum);
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


private slots:
	void ReadFile();		//	��STL��PLY����Ascall ��������ļ�
	void SaveFile();		//	����STL��Plyģ��
	void FillHoles();		//	�׶��޲�
	void Reconstruction();	//	�ؽ�	
	void DrawDomainPoints(long &num, long &step); // ����Nά����㣬��������ʾ
	void DrawLeafNodes(); // ����Ҷ�ӽڵ�

	void ShowPointCloud();
	void OnActionSearchNearPoints();
	void RemoveDiscreteTriangles();
};
