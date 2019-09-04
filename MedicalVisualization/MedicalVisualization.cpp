#include "stdafx.h"
#include "CVtkWidget.h"

#include "CTableView.h"

#include "CStackWidget.h"

#include "MedicalVisualization.h"


MedicalVisualization::MedicalVisualization(QWidget *parent)
	: QMainWindow(parent), m_pMdiAreaCenter(NULL), midAreaMacros(NULL), m_textEditWidget(NULL)
{
	ui.setupUi(this);
	InitToolbar();
	InitScence();
	InitVtk();

}

void MedicalVisualization::InitVtk()
{
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->SetBackground(.3, .6, .3);
	vtkSmartPointer<vtkRenderWindow> renderwindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderwindow->AddRenderer(renderer);
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderwindow);
	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	renderWindowInteractor->SetInteractorStyle(style);
	renderWindowInteractor->Initialize();
	//renderwindow->Render();
	// VtkWidget 
	QVTKWidget  *m_vtkWidget = new QVTKWidget(this);
	m_vtkWidget->setWindowTitle("vtkWidget");
	m_pMdiAreaCenter->addSubWindow(m_vtkWidget);
	m_vtkWidget->SetRenderWindow(renderWindowInteractor->GetRenderWindow());
	//m_vtkWidget->show();
}

void MedicalVisualization::InitScence()
{
	m_pMdiAreaCenter = new QMdiArea(this);
	m_pMdiAreaCenter->setViewMode(QMdiArea::TabbedView);
	m_pMdiAreaCenter->setTabShape(QTabWidget::Triangular);
	m_pMdiAreaCenter->setTabPosition(QTabWidget::North);
	m_pMdiAreaCenter->setTabsMovable(true);
	m_pMdiAreaCenter->setTabsClosable(true);
	m_pMdiAreaCenter->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	m_pMdiAreaCenter->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	

	//window1
	m_textEditWidget = new QTextEdit();
	m_textEditWidget->setWindowTitle("TextEdit");

	m_textEditWidget->setHtml("Cccccc");
	m_pMdiAreaCenter->addSubWindow(m_textEditWidget);     //将window1放进mdiArea框架

	// 去掉下划线
	foreach(QTabBar* tab, m_pMdiAreaCenter->findChildren<QTabBar *>())
	{
		tab->setDrawBase(false);// 不绘制 底边（默认，QTabBar下面有条黑边）
		//tab->setBaseSize(QSize(5, 5)); 
		//tab->setMaximumWidth(20);
	}

	//	添加QTreeView
	QDockWidget* dockWidget1 = new QDockWidget("Object tree", this);
	QTreeView *treeView = new QTreeView(this);
	dockWidget1->setWidget(treeView);
	this->addDockWidget(Qt::RightDockWidgetArea, dockWidget1);

	//	添加QTableView
	QDockWidget* dockWidget2 = new QDockWidget("Macros", this);
	midAreaMacros = new QMdiArea(this);
	CTableView *tableView1 = new CTableView();
	CTableView *tableView2 = new CTableView();

	midAreaMacros->setViewMode(QMdiArea::TabbedView);
	midAreaMacros->setTabShape(QTabWidget::Triangular);
	midAreaMacros->setTabPosition(QTabWidget::North);
	midAreaMacros->setTabsMovable(true);
	midAreaMacros->setTabsClosable(true);
	midAreaMacros->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	midAreaMacros->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	midAreaMacros->addSubWindow(tableView1);
	midAreaMacros->addSubWindow(tableView2);

	dockWidget2->setWidget(midAreaMacros);
	this->addDockWidget(Qt::RightDockWidgetArea, dockWidget2);


	setCentralWidget(m_pMdiAreaCenter);
}

void MedicalVisualization::InitToolbar()
{
	QAction *actionOpen = new QAction(tr("&open"), this);
	actionOpen->setIcon(QIcon(":/MedicalVisualization/Image/open.png"));

	QAction *actionPaste = new QAction(tr("&paste"), this);
	actionPaste->setIcon(QIcon(":/MedicalVisualization/Image/paste.png"));

	QAction *actionSave = new QAction(tr("&save"), this);
	actionSave->setIcon(QIcon(":/MedicalVisualization/Image/save.png"));

	QAction *actionCut = new QAction(tr("&cut"), this);
	actionCut->setIcon(QIcon(":/MedicalVisualization/Image/cut.png"));



	ui.mainToolBar->addAction(actionOpen);
	ui.mainToolBar->addAction(actionPaste);
	ui.mainToolBar->addAction(actionSave);
	ui.mainToolBar->addAction(actionCut);

	connect(actionOpen, SIGNAL(triggered(bool)), this, SLOT(OnActionOpendocument()));
	connect(actionPaste, SIGNAL(triggered(bool)), this, SLOT(OnActionPaste()));
	connect(actionSave, SIGNAL(triggered(bool)), this, SLOT(OnActionSavedocument()));
	connect(actionCut, SIGNAL(triggered(bool)), this, SLOT(OnActionCut()));
}

void MedicalVisualization::on_btnCloseAll_clicked()
{  
	if(m_pMdiAreaCenter)
		m_pMdiAreaCenter->closeAllSubWindows();
}

 void MedicalVisualization::on_btnClose_clicked()
{
	 if (m_pMdiAreaCenter)
		 m_pMdiAreaCenter->closeActiveSubWindow();
 }

void MedicalVisualization::on_btnNext_clicked()
 {
	if (m_pMdiAreaCenter)
		m_pMdiAreaCenter->activateNextSubWindow();
}

 void MedicalVisualization::on_btnPrevious_clicked()
 {
	 if (m_pMdiAreaCenter)
		 m_pMdiAreaCenter->activatePreviousSubWindow();
}

 void MedicalVisualization::on_btnNewWindow_clicked()
 {
		QMdiSubWindow  *newwin = new QMdiSubWindow;
	     newwin->setWindowTitle("test");
	    newwin->setWidget(&QLabel("hey"));
	     newwin->setAttribute(Qt::WA_DeleteOnClose);
	     newwin->resize(200, 200);
		 m_pMdiAreaCenter->addSubWindow(newwin);
	     newwin->show();     
}

 void MedicalVisualization::on_btnRemoveWindow_clicked()
 {
	 if (m_pMdiAreaCenter)
		 m_pMdiAreaCenter->removeSubWindow(m_pMdiAreaCenter->currentSubWindow());   //remove 当前窗口
}

 void MedicalVisualization::OnActionCut()
 {

 }
 void MedicalVisualization::OnActionPaste()
 {

 }
 void MedicalVisualization::OnActionOpendocument()
 {
	 QString path = QFileDialog::getOpenFileName(this, "Open");
	 if (path != "")
	 {
		 QFile file(path);

		 if (file.open(QIODevice::ReadOnly | QIODevice::Text))
		 {
			 m_textEditWidget->setWindowTitle(path);
			 m_textEditWidget->setPlainText(QString(file.readAll()));//读取文件的所有数据并导入到编辑组件
			 file.close();
			 setWindowTitle("NotePad - [ " + path + " ]");
		 }
		 else
		 {
			 QMessageBox::information(this, QString("Open file error! \n\n") + "\"" + path + "\"", QString("Information!"), QMessageBox::Ok);
		 }
	 }
 }
 void MedicalVisualization::OnActionSavedocument()
 {
	 //	检测是否已经打开了文件
	 QString path = m_textEditWidget->windowTitle();
	 QFileInfo fileInfo(path);
	 if (path == QString("") || !fileInfo.exists())
	 {
		 QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("请先创建或者打开文件"));
		 return;
	 }

	 if(m_textEditWidget->toPlainText() == QString(""))
		 QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("内容不能为空!"), QMessageBox::Ok);
	 else
	 {
		
	
		 QFile file(path);
		 if (file.open(QIODevice::WriteOnly | QIODevice::Text))
		 {
			 QMessageBox::warning(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("打开文件失败"), QMessageBox::Ok);
			 return;
		 }

		 QTextStream textStream(&file);
		 QString str = m_textEditWidget->toPlainText();
		 textStream << str;
		 file.close();

		 QMessageBox::information(this, QString::fromLocal8Bit("保存文件"), QString::fromLocal8Bit("保存文件成功"), QMessageBox::Ok);
	
	 }

	
	
 }