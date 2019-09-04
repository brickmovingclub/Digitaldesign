#include "stdafx.h"
#include "MedicalVisualization.h"

MedicalVisualization::MedicalVisualization(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	/*viewer.reset(new pcl::visualization::PCLVisualizer("viewer", false));
	ui.qvtkWidget->SetRenderWindow(viewer->getRenderWindow());
	viewer->setupInteractor(ui.qvtkWidget->GetInteractor(), ui.qvtkWidget->GetRenderWindow());
	ui.qvtkWidget->update();*/
}

// 三维重建
void MedicalVisualization::Reconstruction()
{
	// 文件数据读取
	FileOption fo;
	CAlgorithm ca;
	QFile file;
	QString f = QFileDialog::getOpenFileName(this, QString("OpenFile"),
		QString("/"), QString("ASC(*.asc);;PCD(*.pcd)"));
	//QString转char * 
	QByteArray temp = f.toLocal8Bit();
	char *name = temp.data();
   //	qDebug() << f;
	fo.ReadAscFile(name);
	//fo.ReadAscFile("plane.asc");
	string filename=fo.AscToPcd();
	std::cout <<"filename is "<< filename << std::endl;
	ca.ReadPclFile(filename);

	pcl::PolygonMesh triangles=ca.ThreeDimensionalReconstruction();
	// 显示

	viewer->setBackgroundColor(0, 0, 0);
	viewer->addPolygonMesh(triangles, "my");//设置显示的网格
	viewer->initCameraParameters();

	while (!viewer->wasStopped())
	{
		viewer->spinOnce(100);
		boost::this_thread::sleep(boost::posix_time::microseconds(100000));
	}
}

// 显示补洞后的结果
void MedicalVisualization::ShowHoles()
{
	// 读取stl文件显示
	std::cout << "ShowHoles: " << std::endl;
	std::string inputFilename = "play.ply";

	vtkSmartPointer<vtkPLYReader> reader =
		vtkSmartPointer<vtkPLYReader>::New();
	reader->SetFileName(inputFilename.c_str());
	reader->Update();
	vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(reader->GetOutputPort());
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	renderer->SetBackground(.3, .6, .3);
	vtkSmartPointer<vtkRenderWindow> renderwindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderwindow->AddRenderer(renderer);
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderwindow);
	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
		vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	renderWindowInteractor->SetInteractorStyle(style);
	renderWindowInteractor->Initialize();
	//renderwindow->Render();
	ui.qvtkWidget->SetRenderWindow(renderWindowInteractor->GetRenderWindow());
	ui.qvtkWidget->show();
}

// 孔洞修补
void MedicalVisualization::FillHoles()
{
	// 文件操作
	FileOption fo;
	// 算法
	CAlgorithm ca;
	fo.ReadAscllStlFile("三维重建.stl");

	fo.m_CTrianglesData=ca.HoleRepair(fo.m_allListCEdgeBorder, fo.m_CTrianglesData);
	fo.SavePly();
	std::cout << "补洞完成" << std::endl;

}

// 查找N维领域点，并高亮显示
void MedicalVisualization::DrawDomainPoints()
{
	// TODO: 在此处添加实现代码.
	//绘制模型
	FileOption file;
	file.Bin2ToStl();
	std::map<int, MyPoint> points = file.m_SortMapPoint;
	std::vector<CTriangles> triangles = file.m_CTrianglesData;

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
	int pointSerailNumber = 0, n = 5;
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

	vtkRenderWindow *renderWindow = vtkRenderWindow::New();
	renderWindow->AddRenderer(renderer);

	vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
	iren->SetRenderWindow(renderWindow);

	vtkInteractorStyleTrackballCamera *style = vtkInteractorStyleTrackballCamera::New();
	iren->SetInteractorStyle(style);

	iren->Initialize();
	ui.qvtkWidget->SetRenderWindow(iren->GetRenderWindow());
	ui.qvtkWidget->show();
}

// 绘制叶子节点
void MedicalVisualization::DrawLeafNodes()
{
	// TODO: 在此处添加实现代码.
	std::vector<Eigen::Vector3f> min, max;
	CAlgorithm::ShowLeafNodes(min, max);

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
	renderWindow->SetSize(1000, 800);

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);

	vtkInteractorStyleTrackballCamera *style = vtkInteractorStyleTrackballCamera::New();
	renderWindowInteractor->SetInteractorStyle(style);

	renderer->AddActor(lineActor);
	renderWindow->Render();

	renderWindowInteractor->Initialize();
	//renderWindowInteractor->Start();

	ui.qvtkWidget->SetRenderWindow(renderWindowInteractor->GetRenderWindow());
	ui.qvtkWidget->show();
}