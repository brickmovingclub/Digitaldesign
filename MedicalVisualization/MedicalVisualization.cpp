#include "stdafx.h"

#include "MedicalVisualization.h"

//文件操作
FileOption fileoption;
// 算法操作
CAlgorithm calgorithm;
//MedicalVisualization::MedicalVisualization(QWidget *parent)
//	: QMainWindow(parent)
//{
//	ui.setupUi(this);
//	
//	ui.qvtkWidget->SetRenderWindow(viewer->getRenderWindow());
//	viewer->setupInteractor(ui.qvtkWidget->GetInteractor(), ui.qvtkWidget->GetRenderWindow());
//	ui.qvtkWidget->update();
//}

MedicalVisualization::MedicalVisualization(QWidget *parent)
	: QMainWindow(parent), m_pMdiAreaCenter(NULL), midAreaMacros(NULL), m_textEditWidget(NULL)
{
	ui.setupUi(this);
	//viewer.reset(new pcl::visualization::PCLVisualizer("viewer", false));
	InitToolbar();
	InitScence();
	InitVtk();


	// 去掉下划线
	foreach(QTabBar* tab, m_pMdiAreaCenter->findChildren<QTabBar *>())
	{
		//tab->setDrawBase(false);// 不绘制 底边（默认，QTabBar下面有条黑边）
		//tab->setBaseSize(QSize(5, 5)); 
		//tab->setMaximumWidth(50);
		//tab->setFixedSize(QSize(50, 10));
	}
}

void MedicalVisualization::InitVtk()
{
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	//renderer->AddActor(actor);
	renderer->SetBackground(.3, .6, .3);
	vtkSmartPointer<vtkRenderWindow> renderwindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderwindow->AddRenderer(renderer);
	//vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	//renderWindowInteractor->SetRenderWindow(renderwindow);
	//vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	//renderWindowInteractor->SetInteractorStyle(style);
	//renderWindowInteractor->Initialize();
	//renderwindow->Render();
	m_vtkWidget = new QVTKWidget(this);
	m_vtkWidget->setWindowTitle("vtkWidget");
	m_pMdiAreaCenter->addSubWindow(m_vtkWidget);
	m_vtkWidget->SetRenderWindow(renderwindow);
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
	m_pMdiAreaCenter->setMinimumWidth(100);

	// VtkWidget 
	

	//window1
	m_textEditWidget = new QTextEdit();
	m_textEditWidget->setWindowTitle("TextEdit");

	m_textEditWidget->setHtml("Cccccc");
	m_pMdiAreaCenter->addSubWindow(m_textEditWidget);     //将window1放进mdiArea框架

	

	//	添加QTreeView
	QDockWidget* dockWidget1 = new QDockWidget("Object tree", this);
	QTreeView *treeView = new QTreeView(this);
	dockWidget1->setWidget(treeView);
	this->addDockWidget(Qt::RightDockWidgetArea, dockWidget1);

	//	添加QTableView
	QDockWidget* dockWidget2 = new QDockWidget("Macros", this);
	dockWidget2->setMaximumSize(QSize(400, 400));
	dockWidget2->setMinimumSize(100, 200);

	midAreaMacros = new QMdiArea(this);


	tablePropretyView = new CTableView(dockWidget2);
	tableMacrosView = new CTableView(dockWidget2);

	tablePropretyView->setWindowTitle("proprety");
	tableMacrosView->setWindowTitle("Macros");


	midAreaMacros->setViewMode(QMdiArea::TabbedView);
	midAreaMacros->setTabShape(QTabWidget::Triangular);
	midAreaMacros->setTabPosition(QTabWidget::North);
	midAreaMacros->setTabsMovable(true);
	midAreaMacros->setTabsClosable(true);
	midAreaMacros->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	midAreaMacros->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	midAreaMacros->addSubWindow(tablePropretyView);
	midAreaMacros->addSubWindow(tableMacrosView);

	dockWidget2->setWidget(midAreaMacros);
	this->addDockWidget(Qt::RightDockWidgetArea, dockWidget2);


	setCentralWidget(m_pMdiAreaCenter);

	//	禁用功能
	ui.actionNew_Project->setEnabled(false);
	ui.actionOpen_Project->setEnabled(false);
	ui.actionSave_Project->setEnabled(false);
	ui.actionSearchNPoints->setEnabled(false);
	ui.actionShowleafNodes->setEnabled(false);
	ui.actionShowHoles->setEnabled(false);
	ui.actionReconstruction->setEnabled(false);
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
	if (m_pMdiAreaCenter)
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

	if (m_textEditWidget->toPlainText() == QString(""))
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


// 三维重建
void MedicalVisualization::Reconstruction()
{
	// 文件数据读取
	/*FileOption fo;
	
	QFile file;
	QString f = QFileDialog::getOpenFileName(this, QString("OpenFile"),
		QString("/"), QString("ASC(*.asc);;PCD(*.pcd)"));
	//QString转char * 
	QByteArray temp = f.toLocal8Bit();
	char *name = temp.data();
   //	qDebug() << f;
	fo.ReadAscFile(name);
	//fo.ReadAscFile("plane.asc");*/
	/*string filename= fileoption.AscToPcd();

	std::cout <<"filename is "<< filename << std::endl;
	calgorithm.ReadPclFile(filename);*/
	
	string filenamevtk= calgorithm.ThreeDimensionalReconstruction();
	// 显示,读取vtk文件
	std::cout << "保存vtk文件：" << filenamevtk << std::endl;
	vtkSmartPointer<vtkPolyDataReader> reader = vtkSmartPointer<vtkPolyDataReader>::New();
	reader->SetFileName(filenamevtk.c_str());
	reader->Update();

	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(reader->GetOutputPort());
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

	renderer->AddActor(actor);
	renderer->SetBackground(.3, .6, .3);
	vtkSmartPointer<vtkRenderWindow> renderwindow = vtkSmartPointer<vtkRenderWindow>::New();

	renderwindow->AddRenderer(renderer);
	m_vtkWidget->SetRenderWindow(renderwindow);
	m_vtkWidget->show();
}


// 孔洞修补
void MedicalVisualization::FillHoles()
{

	//fileoption.ReadAscllStlFile("bunny.stl");

	fileoption.m_CTrianglesData= calgorithm.HoleRepair(fileoption.m_allListCEdgeBorder, fileoption.m_CTrianglesData);
	fileoption.SavePly("bunny.ply");
	std::cout << "补洞完成" << std::endl;

	// 读取stl文件显示

	vtkSmartPointer<vtkPLYReader> reader = vtkSmartPointer<vtkPLYReader>::New();
	reader->SetFileName("bunny.ply");
	reader->Update();

	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(reader->GetOutputPort());
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

	renderer->AddActor(actor);
	
	renderer->SetBackground(.3, .6, .3);
	vtkSmartPointer<vtkRenderWindow> renderwindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderwindow->AddRenderer(renderer);
	/*vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetSize(0, 0);
	renderWindowInteractor->SetRenderWindow(renderwindow);
	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
		vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	renderWindowInteractor->SetInteractorStyle(style);
	renderWindowInteractor->Initialize();
	renderwindow->Render();*/
	m_vtkWidget->SetRenderWindow(renderwindow);
	m_vtkWidget->show();
	//->show();
	

}

// 查找N维领域点，并高亮显示
void MedicalVisualization::DrawDomainPoints(long &num, long &step)
{
	 
	UpdateTableView(125.0, 125.0, 12111, 3655);
	// TODO: 在此处添加实现代码.
	//绘制模型
	std::map<int, MyPoint> points = fileoption.m_SortMapPoint;
	std::vector<CTriangles> triangles = fileoption.m_CTrianglesData;

	vtkSmartPointer<vtkPoints> pts = vtkSmartPointer<vtkPoints>::New();
	vtkSmartPointer<vtkCellArray> lines = vtkSmartPointer<vtkCellArray>::New();

	int count = 0;
	for (auto it = triangles.begin(); it != triangles.end(); it++, count++)
	{
		double p0[3] = { it->p0.x, it->p0.y, it->p0.z };
		double p1[3] = { it->p1.x, it->p1.y, it->p1.z };
		double p2[3] = { it->p2.x, it->p2.y, it->p2.z };
		pts->InsertNextPoint(p0);//ID = 3 * count + 0;
		pts->InsertNextPoint(p1);//ID = 3 * count + 1;
		pts->InsertNextPoint(p2);//ID = 3 * count + 2;

		vtkSmartPointer<vtkPolyLine> polyLine = vtkSmartPointer<vtkPolyLine>::New();
		polyLine->GetPointIds()->SetNumberOfIds(4);
		for (unsigned int i = 0; i < 3; i++)
			polyLine->GetPointIds()->SetId(i, count * 3 + i);
		polyLine->GetPointIds()->SetId(3, count * 3 + 0);
		lines->InsertNextCell(polyLine);
	}

	vtkSmartPointer<vtkPolyData> linesPolyData = vtkSmartPointer<vtkPolyData>::New();
	linesPolyData->SetPoints(pts);
	linesPolyData->SetLines(lines);

	vtkSmartPointer<vtkPolyDataMapper> linesMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	linesMapper->SetInputData(linesPolyData);

	vtkSmartPointer<vtkActor> lineActor = vtkSmartPointer<vtkActor>::New();
	lineActor->SetMapper(linesMapper);
	lineActor->GetProperty()->SetColor(1, 1, 1);
	lineActor->GetProperty()->SetLineWidth(1);

	//绘制领域点
	int pointSerailNumber = num, n = step;
	std::set<MyPoint> neighborPoints = CAlgorithm::KOrderDomain(pointSerailNumber, n, points, triangles);
	std::cout << "neighborPoints:" << neighborPoints.size() << std::endl;

	//高亮显示领域点
	vtkPoints *domainPoints = vtkPoints::New();
	vtkCellArray *cells = vtkCellArray::New();
	vtkIdType idtype;
	for (auto it = neighborPoints.begin(); it != neighborPoints.end(); it++)
	{
		idtype = domainPoints->InsertNextPoint(it->x, it->y, it->z);
		cells->InsertNextCell(1, &idtype);
	}

	vtkPolyData *polyData = vtkPolyData::New();
	polyData->SetPoints(domainPoints);
	polyData->SetVerts(cells);

	vtkPolyDataMapper *mapper = vtkPolyDataMapper::New();
	mapper->SetInputData(polyData);

	vtkActor *actor = vtkActor::New();
	actor->SetMapper(mapper);
	//设置颜色与点大小
	actor->GetProperty()->SetColor(0.0, 0.0, 1.0);
	actor->GetProperty()->SetPointSize(5);

	//绘制中心点
	vtkPoints *centerPoints = vtkPoints::New();
	vtkCellArray *centerCells = vtkCellArray::New();
	idtype = centerPoints->InsertNextPoint(points[pointSerailNumber].x, points[pointSerailNumber].y, points[pointSerailNumber].z);
	centerCells->InsertNextCell(1, &idtype);

	vtkPolyData *polyDataCenter = vtkPolyData::New();
	polyDataCenter->SetPoints(centerPoints);
	polyDataCenter->SetVerts(centerCells);

	vtkPolyDataMapper *mapperCenter = vtkPolyDataMapper::New();
	mapperCenter->SetInputData(polyDataCenter);

	vtkActor *actorCenter = vtkActor::New();
	actorCenter->SetMapper(mapperCenter);
	//设置颜色与点大小
	actorCenter->GetProperty()->SetColor(1.0, 0.0, 0.0);
	actorCenter->GetProperty()->SetPointSize(10);

	//显示
	vtkRenderer *renderer = vtkRenderer::New();
	renderer->AddActor(lineActor);
	renderer->AddActor(actor);
	renderer->AddActor(actorCenter);
	renderer->SetBackground(.3, .6, .3);
	vtkRenderWindow *renderWindow = vtkRenderWindow::New();
	renderWindow->AddRenderer(renderer);

	//vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
	//iren->SetRenderWindow(renderWindow);

	//vtkInteractorStyleTrackballCamera *style = vtkInteractorStyleTrackballCamera::New();
	//iren->SetInteractorStyle(style);

	//iren->Initialize();
	m_vtkWidget->SetRenderWindow(renderWindow);
	m_vtkWidget->update();
}

// 绘制叶子节点
void MedicalVisualization::DrawLeafNodes()
{
	// TODO: 在此处添加实现代码.
	std::vector<Eigen::Vector3f> min, max;
	CAlgorithm::ShowLeafNodes(m_cloud, min, max);

	vtkSmartPointer<vtkPoints> pts = vtkSmartPointer<vtkPoints>::New();
	vtkSmartPointer<vtkCellArray> lines = vtkSmartPointer<vtkCellArray>::New();

	int count = 0;
	for (auto it = min.begin(), its = max.begin(); it != min.end(); it++, its++, count++)
	{
		double p0[3] = { it->x(), it->y(), it->z() };
		double p1[3] = { it->x(), its->y(), it->z() };
		double p2[3] = { it->x(), its->y(), its->z() };
		double p3[3] = { it->x(), it->y(), its->z() };
		double p4[3] = { its->x(), it->y(), its->z() };
		double p5[3] = { its->x(), its->y(), its->z() };
		double p6[3] = { its->x(), its->y(), it->z() };
		double p7[3] = { its->x(), it->y(), it->z() };
		pts->InsertNextPoint(p0);//ID = 0;
		pts->InsertNextPoint(p1);//ID = 1;
		pts->InsertNextPoint(p2);//ID = 2;
		pts->InsertNextPoint(p3);//ID = 3;
		pts->InsertNextPoint(p4);//ID = 4;
		pts->InsertNextPoint(p5);//ID = 5;
		pts->InsertNextPoint(p6);//ID = 6;
		pts->InsertNextPoint(p7);//ID = 7;

		vtkSmartPointer<vtkPolyLine> polyLine = vtkSmartPointer<vtkPolyLine>::New();
		polyLine->GetPointIds()->SetNumberOfIds(5);
		for (unsigned int i = 0; i < 4; i++)
			polyLine->GetPointIds()->SetId(i, count * 8 + i);
		polyLine->GetPointIds()->SetId(4, count * 8 + 0);
		lines->InsertNextCell(polyLine);

		vtkSmartPointer<vtkPolyLine> polyLine1 = vtkSmartPointer<vtkPolyLine>::New();
		polyLine1->GetPointIds()->SetNumberOfIds(5);
		for (unsigned int i = 0; i < 4; i++)
			polyLine1->GetPointIds()->SetId(i, count * 8 + i + 4);
		polyLine1->GetPointIds()->SetId(4, count * 8 + 4);
		lines->InsertNextCell(polyLine1);

		vtkSmartPointer<vtkPolyLine> polyLine2 = vtkSmartPointer<vtkPolyLine>::New();
		polyLine2->GetPointIds()->SetNumberOfIds(5);
		for (unsigned int i = 0; i < 4; i++)
			polyLine2->GetPointIds()->SetId(i, count * 8 + i + 2);
		polyLine2->GetPointIds()->SetId(4, count * 8 + 2);
		lines->InsertNextCell(polyLine2);

		vtkSmartPointer<vtkPolyLine> polyLine3 = vtkSmartPointer<vtkPolyLine>::New();
		polyLine3->GetPointIds()->SetNumberOfIds(5);
		polyLine3->GetPointIds()->SetId(0, count * 8 + 0);
		polyLine3->GetPointIds()->SetId(1, count * 8 + 1);
		polyLine3->GetPointIds()->SetId(2, count * 8 + 6);
		polyLine3->GetPointIds()->SetId(3, count * 8 + 7);
		polyLine3->GetPointIds()->SetId(4, count * 8 + 0);
		lines->InsertNextCell(polyLine3);
	}

	vtkSmartPointer<vtkPolyData> linesPolyData = vtkSmartPointer<vtkPolyData>::New();
	linesPolyData->SetPoints(pts);
	linesPolyData->SetLines(lines);

	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(linesPolyData);

	vtkSmartPointer<vtkActor> lineActor = vtkSmartPointer<vtkActor>::New();
	lineActor->SetMapper(mapper);
	lineActor->GetProperty()->SetColor(0, 0, 1);
	lineActor->GetProperty()->SetLineWidth(1);

	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);
	//renderWindow->SetSize(1000, 800);

	//vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	//renderWindowInteractor->SetRenderWindow(renderWindow);

	//vtkInteractorStyleTrackballCamera *style = vtkInteractorStyleTrackballCamera::New();
	//renderWindowInteractor->SetInteractorStyle(style);
	renderer->SetBackground(.3, .6, .3);
	renderer->AddActor(lineActor);
	renderWindow->Render();

	//renderWindowInteractor->Initialize();
	//renderWindowInteractor->Start();

	m_vtkWidget->SetRenderWindow(renderWindow);
	m_vtkWidget->update();
}

void MedicalVisualization::ReadFile()
{
	fileoption.m_CTrianglesData.clear();
	fileoption.m_MapPoint.clear();
	fileoption.m_allListCEdgeBorder.clear();
	fileoption.m_SortMapPoint.clear();
	fileoption.normal.clear();
	fileoption.m_allListCEdgeBorder.clear();
	QString file_full, file_name, file_path, file_suffix;
	QFileInfo fileinfo;
	file_full = QFileDialog::getOpenFileName(this, QString("打开文件"), QString("."), tr("ALL Files(*);;STL(*.stl);;PLY(*.ply);;Asc(*.asc)"));
	fileinfo = QFileInfo(file_full);
	//文件名
	file_name = fileinfo.fileName();
	//文件后缀
	file_suffix = fileinfo.suffix();
	//绝对路径
	file_path = fileinfo.absolutePath();
	std::cout << "文件名：" << file_name.toStdString().data() << std::endl;
	std::cout << "后缀：" << file_suffix.toStdString().data() << std::endl;
	std::cout << "绝对路径：" << file_path.toStdString().data() << std::endl;
	QByteArray temp = file_path.toStdString().data();
	temp = file_full.toLocal8Bit();
	char *name1 = temp.data();
	ui.actionSearchNPoints->setEnabled(true);
	ui.actionFile_holes->setEnabled(true);
	ui.actionReconstruction->setEnabled(true);

	ui.actionShowleafNodes->setEnabled(true);
	if (strcmp(file_suffix.toStdString().data(),"stl") == 0)
	{

		ui.actionReconstruction->setEnabled(false);
		ui.actionShowleafNodes->setEnabled(false);
		fileoption.ReadAscllStlFile(name1);
		//计算模型体积与面积
		double volume = 0, area = 0; //体积、面积
		int pointSize = fileoption.m_SortMapPoint.size(); //顶点数
		int triangleSize = fileoption.m_CTrianglesData.size(); //面片数
		CAlgorithm::CalculateVolumeAndArea(fileoption.m_SortMapPoint, fileoption.m_CTrianglesData, volume, area);
		std::cout << volume << "\t" << area << std::endl;

		//	更新显示
		UpdateTableView(area, volume, triangleSize, pointSize);
		vtkSmartPointer<vtkSTLReader> reader = vtkSmartPointer<vtkSTLReader>::New();
		reader->SetFileName(name1);
		reader->Update();

		vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
		mapper->SetInputConnection(reader->GetOutputPort());
		vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
		actor->SetMapper(mapper);

		vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
		renderer->AddActor(actor);
		renderer->SetBackground(.3, .6, .3);
		vtkSmartPointer<vtkRenderWindow> renderwindow =
			vtkSmartPointer<vtkRenderWindow>::New();
		renderwindow->AddRenderer(renderer);
		m_vtkWidget->SetRenderWindow(renderwindow);
		m_vtkWidget->show();
	}
	else if (strcmp(file_suffix.toStdString().data(), "ply") == 0)
	{
	

		ui.actionReconstruction->setEnabled(false);
		ui.actionShowleafNodes->setEnabled(false);
		fileoption.ReadPlyFile(name1);
		//计算模型体积与面积
		double volume = 0, area = 0; //体积、面积
		int pointSize = fileoption.m_SortMapPoint.size(); //顶点数
		int triangleSize = fileoption.m_CTrianglesData.size(); //面片数
		CAlgorithm::CalculateVolumeAndArea(fileoption.m_SortMapPoint, fileoption.m_CTrianglesData, volume, area);
		std::cout << volume << "\t" << area << std::endl;
		UpdateTableView(area, volume, triangleSize, pointSize);

		vtkSmartPointer<vtkPLYReader> reader = vtkSmartPointer<vtkPLYReader>::New();
		reader->SetFileName(name1);
		reader->Update();

		vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
		mapper->SetInputConnection(reader->GetOutputPort());
		vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
		actor->SetMapper(mapper);

		vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
		renderer->AddActor(actor);
		renderer->SetBackground(.3, .6, .3);
		vtkSmartPointer<vtkRenderWindow> renderwindow =
			vtkSmartPointer<vtkRenderWindow>::New();
		renderwindow->AddRenderer(renderer);
		m_vtkWidget->SetRenderWindow(renderwindow);
		m_vtkWidget->show();
	}
	else if (strcmp(file_suffix.toStdString().data(), "asc") == 0)
	{
		ui.actionFile_holes->setEnabled(false);
		// 读取asc文件
		fileoption.ReadAscFile(name1);
		// 显示点云数据
		// asc文件转换成pcd
		string pclFile=fileoption.AscToPcd();
		// 读取pcd文件生成点云
		m_cloud = calgorithm.ReadPclFile(pclFile);
		ShowPointCloud();
	}
}

void MedicalVisualization::SaveFile()
{
	QString file_full, file_suffix;
	QFileInfo fileinfo;
	file_full = QFileDialog::getSaveFileName(this, tr("Save File"), "/", tr("STL(*.stl);;PLY(*.ply)"));
	if (file_full == "")
	{
		return;
	}
	fileinfo = QFileInfo(file_full);
	//文件后缀
	file_suffix = fileinfo.suffix();
	QByteArray temp;
	temp = file_full.toLocal8Bit();
	char *name1 = temp.data();
	if (strcmp(file_suffix.toStdString().data(), "stl") == 0)
	{
		fileoption.SaveAsStl(name1);
	}
	else if (strcmp(file_suffix.toStdString().data(), "ply") == 0)
	{
		fileoption.SavePly(name1);
	}

}

void MedicalVisualization::ShowPointCloud()
{
	vtkPoints *points = vtkPoints::New();
	vtkCellArray *cells = vtkCellArray::New();
	vtkIdType idtype;
	for (auto it = m_cloud->points.begin(); it != m_cloud->points.end(); it++)
	{
		idtype = points->InsertNextPoint(it->x, it->y, it->z);
		cells->InsertNextCell(1, &idtype);
	}

//<<<<<<< HEAD
	vtkPolyData *polyData = vtkPolyData::New();
	polyData->SetPoints(points);
	polyData->SetVerts(cells);

	vtkPolyDataMapper *mapper = vtkPolyDataMapper::New();
	mapper->SetInputData(polyData);

	vtkActor *actor = vtkActor::New();
	actor->SetMapper(mapper);
	//设置颜色与点大小
	actor->GetProperty()->SetColor(176.0/255, 196.0/255, 222.0/255);
	actor->GetProperty()->SetPointSize(3);

	//显示
	vtkRenderer *renderer = vtkRenderer::New();
	renderer->AddActor(actor);
	renderer->SetBackground(.3, .6, .3);

	vtkRenderWindow *renderWindow = vtkRenderWindow::New();
	renderWindow->AddRenderer(renderer);

	m_vtkWidget->SetRenderWindow(renderWindow);
	m_vtkWidget->update();
//=======
}

void MedicalVisualization::UpdateTableView(const float area, const float volum, const int faceNum, const int vertexNum)
{
	QStringList strList1, strList2, strList3, strList4;

	QString strArea = QString::number(area);
	strList1 << strArea;
	tablePropretyView->addRow(strList1);

	QString strVolum = QString::number(volum);
	strList2 << strVolum;
	tablePropretyView->addRow(strList2);

	QString strfaceNum = QString::number(faceNum);
	strList3 << strfaceNum;
	tablePropretyView->addRow(strList3);

	QString strvertexNum = QString::number(vertexNum);
	strList4 << strvertexNum;
	tablePropretyView->addRow(strList4);

}

void MedicalVisualization::OnActionSearchNearPoints()
{
	CTerritoryWidget *widget = new CTerritoryWidget();
	widget->setWindowTitle(QString::fromLocal8Bit("领域点搜索"));
	connect(widget, SIGNAL(TerritoryChanged(long &, long &)), this, SLOT(DrawDomainPoints(long &, long &)));
	widget->show();
//>>>>>>> master_back
}

// 去除模型中离散的三角形
void MedicalVisualization::RemoveDiscreteTriangles()
{
	// TODO: 在此处添加实现代码.
	//去除离散三角形
	CAlgorithm::RemoveDiscreteTriangles(fileoption.m_SortMapPoint, fileoption.m_CTrianglesData);

	//绘制模型
	std::map<int, MyPoint> points = fileoption.m_SortMapPoint;
	std::vector<CTriangles> triangles = fileoption.m_CTrianglesData;

	vtkSmartPointer<vtkPoints> pts = vtkSmartPointer<vtkPoints>::New();
	vtkSmartPointer<vtkCellArray> lines = vtkSmartPointer<vtkCellArray>::New();

	int count = 0;
	for (auto it = triangles.begin(); it != triangles.end(); it++, count++)
	{
		double p0[3] = { it->p0.x, it->p0.y, it->p0.z };
		double p1[3] = { it->p1.x, it->p1.y, it->p1.z };
		double p2[3] = { it->p2.x, it->p2.y, it->p2.z };
		pts->InsertNextPoint(p0);//ID = 3 * count + 0;
		pts->InsertNextPoint(p1);//ID = 3 * count + 1;
		pts->InsertNextPoint(p2);//ID = 3 * count + 2;

		vtkSmartPointer<vtkPolyLine> polyLine = vtkSmartPointer<vtkPolyLine>::New();
		polyLine->GetPointIds()->SetNumberOfIds(4);
		for (unsigned int i = 0; i < 3; i++)
			polyLine->GetPointIds()->SetId(i, count * 3 + i);
		polyLine->GetPointIds()->SetId(3, count * 3 + 0);
		lines->InsertNextCell(polyLine);
	}

	vtkSmartPointer<vtkPolyData> linesPolyData = vtkSmartPointer<vtkPolyData>::New();
	linesPolyData->SetPoints(pts);
	linesPolyData->SetLines(lines);

	vtkSmartPointer<vtkPolyDataMapper> linesMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	linesMapper->SetInputData(linesPolyData);

	vtkSmartPointer<vtkActor> lineActor = vtkSmartPointer<vtkActor>::New();
	lineActor->SetMapper(linesMapper);
	lineActor->GetProperty()->SetColor(1, 1, 1);
	lineActor->GetProperty()->SetLineWidth(1);

	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(lineActor);
	renderer->SetBackground(.3, .6, .3);

	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);

	m_vtkWidget->SetRenderWindow(renderWindow);
	m_vtkWidget->update();
}