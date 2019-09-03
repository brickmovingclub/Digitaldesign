#include "stdafx.h"
#include "CAlgorithm.h"

// 点云数据
pcl::PointCloud<pcl::PointXYZ>::Ptr  cloud(new pcl::PointCloud<pcl::PointXYZ>);


CAlgorithm::CAlgorithm()
{

}


CAlgorithm::~CAlgorithm()
{
}

// 读取PCD文件格式数据
void CAlgorithm::ReadPclFile(string m_fileName)
{
	pcl::io::loadPCDFile<pcl::PointXYZ>(m_fileName, *cloud);

	if (pcl::io::loadPCDFile<pcl::PointXYZ>(m_fileName, *cloud) == -1)
	{
		std::cout << "Cloud reading failed。" << std::endl;
		return;
	}
}

void CAlgorithm::KOrderDomain()
{
}

void CAlgorithm::ShowLeafNodes()
{
}

// 三维重建
pcl::PolygonMesh CAlgorithm::ThreeDimensionalReconstruction(string m_fileName)
{
	pcl::PolygonMesh triangles;//创建多边形网格，用于存储结果
	if (pcl::io::loadPCDFile<pcl::PointXYZ>(m_fileName, *cloud) == -1)
	{
		PCL_ERROR("Couldn't read file bunny.pcd\n");
		return triangles;
	}
	//Normal 法向量
	pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> n;
	pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
	pcl::search::KdTree < pcl::PointXYZ >::Ptr tree(new pcl::search::KdTree < pcl::PointXYZ >);
	tree->setInputCloud(cloud);
	n.setInputCloud(cloud);
	n.setSearchMethod(tree);
	n.setKSearch(20);
	n.compute(*normals);//法线
	//将点云和法线放在一起
	pcl::PointCloud<pcl::PointNormal>::Ptr Cloud_With_Normals(new pcl::PointCloud<pcl::PointNormal>);
	pcl::concatenateFields(*cloud, *normals, *Cloud_With_Normals);
	//创建查找树
	pcl::search::KdTree<pcl::PointNormal>::Ptr tree2(new pcl::search::KdTree < pcl::PointNormal >);
	tree2->setInputCloud(Cloud_With_Normals);
	//初始化对象
	pcl::GreedyProjectionTriangulation < pcl::PointNormal > gp3;
	//设置参数
	gp3.setSearchRadius(2.5);//设置连接点之间的最大距离（最大边长）用于确定k近邻的球半径，搜索半径
	gp3.setMu(2);//设置最近邻距离的乘子，已经得到每个点的最终搜索半径，即搜索半径
	gp3.setMaximumNearestNeighbors(100);//设置搜索的最近邻点的最大数量
	gp3.setMaximumSurfaceAngle(M_PI / 4);//45度最大平面角
	gp3.setMinimumAngle(M_PI / 18);//三角形的最小角度10度
	gp3.setMaximumAngle(2 * M_PI / 2);//三角形的最大角度120度
	gp3.setNormalConsistency(false);//若法向量一致，设为true
	//设置搜索方法和输出点云
	gp3.setInputCloud(Cloud_With_Normals);
	gp3.setSearchMethod(tree2);
	//执行重构，结果保存在triangles中
	gp3.reconstruct(triangles);
	std::cout << "************" << triangles.cloud.width << std::endl;

	std::cout << "************" << triangles.polygons.size() << std::endl;
	//保存网格图
	pcl::io::saveVTKFile("bunny.vtk", triangles);//保存为vtk文件
	//增加顶点信息
	return triangles;
}

void CAlgorithm::HoleRepair()
{
}

