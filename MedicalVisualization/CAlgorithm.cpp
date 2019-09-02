#include "stdafx.h"
#include "CAlgorithm.h"

// ��������
pcl::PointCloud<pcl::PointXYZ>::Ptr  cloud(new pcl::PointCloud<pcl::PointXYZ>);


CAlgorithm::CAlgorithm()
{

}


CAlgorithm::~CAlgorithm()
{
}

// ��ȡPCD�ļ���ʽ����
void CAlgorithm::ReadPclFile(string m_fileName)
{
	pcl::io::loadPCDFile<pcl::PointXYZ>(m_fileName, *cloud);

	if (pcl::io::loadPCDFile<pcl::PointXYZ>(m_fileName, *cloud) == -1)
	{
		std::cout << "Cloud reading failed��" << std::endl;
		return;
	}
}

void CAlgorithm::KOrderDomain()
{
}

void CAlgorithm::ShowLeafNodes()
{
}

// ��ά�ؽ�
pcl::PolygonMesh CAlgorithm::ThreeDimensionalReconstruction(string m_fileName)
{
	pcl::PolygonMesh triangles;//����������������ڴ洢���
	if (pcl::io::loadPCDFile<pcl::PointXYZ>(m_fileName, *cloud) == -1)
	{
		PCL_ERROR("Couldn't read file bunny.pcd\n");
		return triangles;
	}
	//Normal ������
	pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> n;
	pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
	pcl::search::KdTree < pcl::PointXYZ >::Ptr tree(new pcl::search::KdTree < pcl::PointXYZ >);
	tree->setInputCloud(cloud);
	n.setInputCloud(cloud);
	n.setSearchMethod(tree);
	n.setKSearch(20);
	n.compute(*normals);//����
	//�����ƺͷ��߷���һ��
	pcl::PointCloud<pcl::PointNormal>::Ptr Cloud_With_Normals(new pcl::PointCloud<pcl::PointNormal>);
	pcl::concatenateFields(*cloud, *normals, *Cloud_With_Normals);
	//����������
	pcl::search::KdTree<pcl::PointNormal>::Ptr tree2(new pcl::search::KdTree < pcl::PointNormal >);
	tree2->setInputCloud(Cloud_With_Normals);
	//��ʼ������
	pcl::GreedyProjectionTriangulation < pcl::PointNormal > gp3;
	//���ò���
	gp3.setSearchRadius(2.5);//�������ӵ�֮��������루���߳�������ȷ��k���ڵ���뾶�������뾶
	gp3.setMu(2);//��������ھ���ĳ��ӣ��Ѿ��õ�ÿ��������������뾶���������뾶
	gp3.setMaximumNearestNeighbors(100);//��������������ڵ���������
	gp3.setMaximumSurfaceAngle(M_PI / 4);//45�����ƽ���
	gp3.setMinimumAngle(M_PI / 18);//�����ε���С�Ƕ�10��
	gp3.setMaximumAngle(2 * M_PI / 2);//�����ε����Ƕ�120��
	gp3.setNormalConsistency(false);//��������һ�£���Ϊtrue
	//���������������������
	gp3.setInputCloud(Cloud_With_Normals);
	gp3.setSearchMethod(tree2);
	//ִ���ع������������triangles��
	gp3.reconstruct(triangles);
	std::cout << "************" << triangles.cloud.width << std::endl;

	std::cout << "************" << triangles.polygons.size() << std::endl;
	//��������ͼ
	pcl::io::saveVTKFile("bunny.vtk", triangles);//����Ϊvtk�ļ�
	//���Ӷ�����Ϣ
	return triangles;
}

void CAlgorithm::HoleRepair()
{
}

