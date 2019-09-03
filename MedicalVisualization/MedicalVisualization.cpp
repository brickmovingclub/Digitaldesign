#include "stdafx.h"
#include "MedicalVisualization.h"

MedicalVisualization::MedicalVisualization(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	viewer.reset(new pcl::visualization::PCLVisualizer("viewer", false));
	ui.qvtkWidget->SetRenderWindow(viewer->getRenderWindow());
	viewer->setupInteractor(ui.qvtkWidget->GetInteractor(), ui.qvtkWidget->GetRenderWindow());
	ui.qvtkWidget->update();
}

// ��ά�ؽ�
void MedicalVisualization::Reconstruction()
{
	// �ļ����ݶ�ȡ
	FileOption fo;
	CAlgorithm ca;
	QFile file;
	QString f = QFileDialog::getOpenFileName(this, QString("OpenFile"),
		QString("/"), QString("ASC(*.asc);;PCD(*.pcd)"));
	//QStringתchar * 
	QByteArray temp = f.toLocal8Bit();
	char *name = temp.data();
   //	qDebug() << f;
	fo.ReadAscFile(name);
	//fo.ReadAscFile("plane.asc");
	string filename=fo.AscToPcd();
	std::cout <<"filename is "<< filename << std::endl;
	ca.ReadPclFile(filename);

	pcl::PolygonMesh triangles=ca.ThreeDimensionalReconstruction();
	// ��ʾ

	viewer->setBackgroundColor(0, 0, 0);
	viewer->addPolygonMesh(triangles, "my");//������ʾ������
	viewer->initCameraParameters();

	while (!viewer->wasStopped())
	{
		viewer->spinOnce(100);
		boost::this_thread::sleep(boost::posix_time::microseconds(100000));
	}
}

// �׶��޲�
void MedicalVisualization::FillHoles()
{
	// �ļ�����
	FileOption fo;
	// �㷨
	CAlgorithm ca;
	

}
