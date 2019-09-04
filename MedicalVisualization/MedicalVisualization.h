#pragma once


#include "ui_MedicalVisualization.h"


class MedicalVisualization : public QMainWindow
{
	Q_OBJECT

public:
	MedicalVisualization(QWidget *parent = Q_NULLPTR);

private:
	Ui::MedicalVisualizationClass ui;

	//CVtkWidget *m_vtkWidget;
	QMdiArea *m_pMdiAreaCenter; 
	QMdiArea *midAreaMacros;
	QTextEdit *m_textEditWidget;
	
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

};
