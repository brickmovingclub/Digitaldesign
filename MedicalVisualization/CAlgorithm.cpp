#include "stdafx.h"
#include "CAlgorithm.h"

using namespace std;
// 点云数据
pcl::PointCloud<pcl::PointXYZ>::Ptr cloudTriangles(new pcl::PointCloud<pcl::PointXYZ>);
pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

CAlgorithm::CAlgorithm()
{

}

CAlgorithm::~CAlgorithm()
{
}

// 读取PCD文件格式数据
pcl::PointCloud<pcl::PointXYZ>::Ptr CAlgorithm::ReadPclFile(string m_fileName)
{
	pcl::io::loadPCDFile<pcl::PointXYZ>(m_fileName, *cloud);

	if (pcl::io::loadPCDFile<pcl::PointXYZ>(m_fileName, *cloud) == -1)
	{
		std::cout << "Cloud reading failed。" << std::endl;
		return cloud;
	}
	return cloud;
}

//  K阶领域显示
std::set<MyPoint> CAlgorithm::KOrderDomain(int pointSerailNumber, int n, std::map<int, MyPoint> points, std::vector<CTriangles> triangles)
{
	int index = 0;
	std::set<MyPoint> neighborPointAll; //所有的节点
	neighborPointAll.insert(points[pointSerailNumber]);
	std::list<int> neighborPointN; // 第N环的节点
	neighborPointN.push_back(pointSerailNumber);
	for (int ring = 0; ring < n; ring++)
	{
		// 第ring环的节点
		int ringSize = neighborPointN.size();// 当前环节点的个数
		for (int i = 0; i < ringSize && !neighborPointN.empty(); i++)
		{
			//找到点的编号
			index = neighborPointN.front();
			neighborPointN.pop_front();
			//寻找节点index的邻居节点
			for (auto it = points[index].m_TrianglesList.begin(); it != points[index].m_TrianglesList.end(); it++)
			{
				if (neighborPointAll.count(triangles[*it].p0) == 0)
				{
					neighborPointN.push_back(triangles[*it].mp0);
					neighborPointAll.insert(triangles[*it].p0);
				}
				if (neighborPointAll.count(triangles[*it].p1) == 0)
				{
					neighborPointN.push_back(triangles[*it].mp1);
					neighborPointAll.insert(triangles[*it].p1);
				}
				if (neighborPointAll.count(triangles[*it].p2) == 0)
				{
					neighborPointN.push_back(triangles[*it].mp2);
					neighborPointAll.insert(triangles[*it].p2);
				}
			}
		}
	}
	return neighborPointAll;
}

// 叶子节点显示
void CAlgorithm::ShowLeafNodes(pcl::PointCloud<pcl::PointXYZ>::Ptr m_cloud, std::vector<Eigen::Vector3f> &min, std::vector<Eigen::Vector3f> &max)
{
	float resolu = 1.0f;
	pcl::octree::OctreePointCloudSearch<pcl::PointXYZ> tree(resolu);
	tree.setInputCloud(m_cloud);
	tree.addPointsFromInputCloud();
	std::cout << "叶子节点个数：" << tree.getLeafCount() << std::endl;

	int depth = tree.getTreeDepth();
	for (auto it = tree.begin(depth); it != tree.end(); it++)
	{
		if (it.isLeafNode())
		{
			Eigen::Vector3f min_pt, max_pt;
			tree.getVoxelBounds(it, min_pt, max_pt);
			min.push_back(min_pt);
			max.push_back(max_pt);
		}
	}
}

// 三维重建
string CAlgorithm::ThreeDimensionalReconstruction()
{
	pcl::PolygonMesh triangles;//创建多边形网格，用于存储结果

	//Normal 法向量
	pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> n;
	pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
	pcl::search::KdTree < pcl::PointXYZ >::Ptr tree(new pcl::search::KdTree < pcl::PointXYZ >);
	tree->setInputCloud(cloud);
	n.setInputCloud(cloud);
	n.setSearchMethod(tree);
	n.setKSearch(10);
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
	gp3.setMaximumNearestNeighbors(50);//设置搜索的最近邻点的最大数量
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
		//增加顶点信息
	std::vector<int> parts = gp3.getPartIDs();
	std::vector<int> states = gp3.getPointStates();
	return "bunny.vtk";
}

// 孔洞修补
vector<CTriangles> CAlgorithm::HoleRepair(vector<CEdge>m_borderEdgeList, vector<CTriangles> m_CTrianglesData) 
{
	std::cout <<"之前面的大小：" <<m_CTrianglesData.size() << std::endl;
	// 获取孔洞边
	map<int, vector<CEdge>>m_holeList;
	// 排序后的孔洞边
	map<int, vector<CEdge>>m_sortHoleList;
	// 新增边集合
	map<int, vector<CEdge>>m_resultCEdgeList;
	// 获选点

	int m_count = 0;
	m_holeList = GetHole(m_borderEdgeList);

	
	// 补洞之前对每一个洞的list进行排序
	for (auto it = m_holeList.begin();it != m_holeList.end();it++)
	{
		vector<CEdge>sortEdge = it->second;
		CEdge m_c1;
		CEdge m_c2;
		CEdge m_cc;
		MyPoint my;
		double a = 360;
		double angle = 0;
		vector<CEdge>m_activeCEdgeList;
		for (int i = 0;i < sortEdge.size() - 1;i++)
		{
			m_c1 = sortEdge[i];
			m_c2 = sortEdge[i + 1];
			double A = GetAngleRear(m_c1, m_c2);
			if (A < a)
			{
				m_cc = sortEdge[i];
				my = m_c1.startNode;
				angle = A;
				a = A;
			}
		}
		m_activeCEdgeList.push_back(m_cc);
		if (sortEdge.size() > 0)
		{
			my = m_cc.endNode;
			MyPoint point = m_cc.startNode;
			while (!(my == point))
			{
				for (int i = 0;i < sortEdge.size(); i++)
				{
					if ((sortEdge[i].startNode == my) && ((!(sortEdge[i].startNode == m_cc.startNode)) && (!(sortEdge[i].endNode == m_cc.endNode))))
					{
						//cout << "点 ： " << my.x << " "<<my.y<<" "<<my.z<<endl;

						m_activeCEdgeList.push_back(sortEdge[i]);

						m_cc = sortEdge[i];
						my = m_cc.endNode;
						break;
					}
				}
			}
		}
		m_sortHoleList.insert(pair<int, vector<CEdge>>(m_count++, m_activeCEdgeList));
	}
	// 补洞算法
	std::cout << "孔洞的个数 " << m_sortHoleList.size() << std::endl;

	for (auto it = m_sortHoleList.begin();it != m_sortHoleList.end();it++)
	{
		vector<CEdge>m_activeCEdgeList=it->second;
		vector<CEdge>m_listResult;
		if (m_activeCEdgeList.size() >= 2)
		{
			// 当前边
				// 当前边
			CEdge  currentEdge(m_activeCEdgeList[0].startNode, m_activeCEdgeList[1].endNode);
			m_listResult.push_back(currentEdge);
			// 当前面
			CTriangles ct(m_activeCEdgeList[0].startNode, m_activeCEdgeList[0].endNode, m_activeCEdgeList[1].endNode);
			m_CTrianglesData.push_back(ct);
			// 删除最小角的边
			m_activeCEdgeList.erase(m_activeCEdgeList.begin());

			m_activeCEdgeList.erase(m_activeCEdgeList.begin());
			int i = 0;
			do
			{
				// 获取候选点
				GettingCandidatePoints(currentEdge, m_activeCEdgeList);
				// 计算二面角
				CTriangles ctFront(currentEdge.startNode, currentEdge.endNode, frontPoint);
				vector<double>list1 = getNormal(currentEdge.startNode, currentEdge.endNode, frontPoint);

				CTriangles ctRear(rearPoint, currentEdge.startNode, currentEdge.endNode);

				vector<double>list2 = getNormal(rearPoint, currentEdge.startNode, currentEdge.endNode);
				vector<double>list3 = getNormal(ct.p0, ct.p1, ct.p2);
				double A = GetAngle(ctFront, ct);
				double B = GetAngle(ctRear, ct);
				if (list1.size() < 3 || list2.size() < 3 || list3.size() < 3)
					break;
				if (list1[1] * list3[1] > 0)
				{
					A = 360;
				}
				if (list2[1] * list3[1] > 0)
				{
					B = 360;
				}
				// 种子法向量

				if (A > B)
				{
					currentEdge.ToString();

					std::cout << "A: " << A << std::endl;
					currentEdge.startNode = frontPoint;
					currentEdge.endNode = currentEdge.endNode;
					ct = ctFront;
					std::cout << "生成后的边： " << std::endl;
					currentEdge.ToString();
					m_CTrianglesData.push_back(ctFront);

				}
				else if (A < B)
				{
					currentEdge.ToString();

					std::cout << "B: " << B << std::endl;

					MyPoint pp = currentEdge.startNode;
					currentEdge.startNode = pp;
					currentEdge.endNode = rearPoint;
					ct = ctRear;
					std::cout << "生成后的边： " << std::endl;
					m_CTrianglesData.push_back(ctRear);

					currentEdge.ToString();

				}
				else
				{
					// 若二面角相等则计算面积
					double areaFront = GetArea(ctFront);
					double areaRear = GetArea(ctRear);
					if (areaFront > areaRear)
					{
						std::cout << "A: " << A << std::endl;
						currentEdge.startNode = frontPoint;
						currentEdge.endNode = currentEdge.endNode;
						ct = ctFront;
						std::cout << "生成后的边： " << std::endl;
						m_CTrianglesData.push_back(ctFront);

						currentEdge.ToString();
					}
					else
					{
						currentEdge.ToString();

						std::cout << "B: " << B << std::endl;

						MyPoint pp = currentEdge.startNode;
						currentEdge.startNode = pp;
						currentEdge.endNode = rearPoint;
						ct = ctRear;
						std::cout << "生成后的边： " << std::endl;

						currentEdge.ToString();
						m_CTrianglesData.push_back(ctRear);

					}

				}

				m_listResult.push_back(currentEdge);
				// 删除头的那条边
				if (m_activeCEdgeList.size() > 0)
				{
					m_activeCEdgeList.erase(m_activeCEdgeList.begin());
					m_activeCEdgeList.insert(m_activeCEdgeList.begin(), currentEdge);
				}
				else
				{
					break;

				}
			} while (m_activeCEdgeList.size() > 2);
			std::cout << "后前面的大小：" << m_CTrianglesData.size() << std::endl;
		}
	}
	return m_CTrianglesData;
}

// 获取孔洞边界
map<int, vector<CEdge>> CAlgorithm::GetHole(vector<CEdge>m_borderEdgeList)
{
	// 获取孔洞边
	map<int, vector<CEdge>>m_holeList;
	// 暂存孔洞边的集合
	vector<CEdge>m_tempList;
	// 获取孔洞边
	for (auto it = m_borderEdgeList.begin();it != m_borderEdgeList.end();it++)
	{
		CEdge e = *it;
		if (count(m_borderEdgeList.begin(), m_borderEdgeList.end(), e) == 1)
		{
			m_tempList.push_back(e);
		}
	}
	// 获取每个孔洞
	int i = 0;
	int m_countEdge = m_tempList.size();
	while (m_countEdge>0)
	{
		// 代理
		vector<CEdge>m_tempListCEdge=m_tempList;
		// 暂存
		vector<CEdge>result;
		CEdge c1 = m_tempListCEdge[0];
		result.push_back(c1);
		MyPoint point = c1.startNode;
		MyPoint my;

		if (m_borderEdgeList.size() > 0)
		{
			my = c1.endNode;
			while (!(my == point))
			{
				for (int i = 0;i < m_tempListCEdge.size(); i++)
				{
					if(m_tempListCEdge[i].flag==0){
						if ((m_tempListCEdge[i].startNode == my) && ((!(m_tempListCEdge[i].startNode == c1.startNode)) && (!(m_tempListCEdge[i].endNode == c1.endNode))))
						{
							//cout << "点 ： " << my.x << " "<<my.y<<" "<<my.z<<endl;

							result.push_back(m_tempListCEdge[i]);

							c1 = m_tempListCEdge[i];
							my = c1.endNode;
							break;
						}
					}
				}
			}
		}
		// 从主集合中删除已经找洞成功的边
		// 暂存集合
		vector<CEdge>m_tempCEdge;
		
		for (auto it = result.begin();it != result.end();it++)
		{
			CEdge e = *it;
			for (auto itt = m_tempList.begin();itt != m_tempList.end();itt++)
			{
				if (e.isEqual(*itt))
				{
					itt->flag = 1;
					m_countEdge--;
					break;
				}
			}
		}
		for (auto it = m_tempList.begin();it != m_tempList.end();)
		{
			CEdge e = *it;
			if (e.flag==1)
			{
				it++;
				//cout << "x=: " << e.startNode.x << "y=: " << e.startNode.y << "z= " << e.startNode.z << endl;
			}
			else
			{
				m_tempCEdge.push_back(e);
				it++;
			}
		}
		m_holeList.insert(pair<int, vector<CEdge>>(i++, result));
		m_tempList = m_tempCEdge;
	}
	return m_holeList;
}

double CAlgorithm::GetAngleRear(CEdge currentEdge, CEdge otherEdge)
{
	Point1 p2(currentEdge.startNode.x, currentEdge.startNode.y, currentEdge.startNode.z),
		p1(currentEdge.endNode.x, currentEdge.endNode.y, currentEdge.endNode.z),
		p3(otherEdge.endNode.x, otherEdge.endNode.y, otherEdge.endNode.z);
	double A = getDegAngle(p1, p2, p3);
	return A;
}

double CAlgorithm::getDegAngle(Point1 p1, Point1 p2, Point1 p3)
{
	Eigen::Vector3d v1 = p2 - p1;
	Eigen::Vector3d v2 = p3 - p1;
	//cout <<" norm: " <<v1.cross(v2).norm() << endl;
	//cout << " v1.transpose() * v2: " << v1.transpose() * v2 << endl;
	double radian_angle = atan2(v1.cross(v2).norm(), v1.transpose() * v2);
	if (v1.cross(v2).z() < 0) {
		radian_angle = 2 * M_PI - radian_angle;
	}
	return radian_angle * 180 / M_PI;
}

double CAlgorithm::GetAngle(CTriangles ct1, CTriangles ct2)
{
	// 通过角度计算二面角

	double angle = 0.0f;
	// 获取面的法矢
	vector<double>ct1N = getNormal(ct1.p0, ct1.p1, ct1.p2);
	vector<double>ct2N = getNormal(ct2.p0, ct2.p1, ct2.p2);
	if (ct1N.size() < 3 || ct2N.size() < 3)
		return -1;
	// 计算二面角
	Eigen::Vector3d v1(ct1N[0], ct1N[1], ct1N[2]);
	Eigen::Vector3d v2(ct2N[0], ct2N[1], ct2N[2]);
	//cout <<" norm: " <<v1.cross(v2).norm() << endl;
	//cout << " v1.transpose() * v2: " << v1.transpose() * v2 << endl;
	double radian_angle = atan2(v1.cross(v2).norm(), v1.transpose() * v2);
	/*if (v1.cross(v2).z() < 0) {
radian_angle = 2 * M_PI - radian_angle;
}*/
	angle = radian_angle * 180 / M_PI;

	if (angle < 90)
	{
		return 180 - angle;
	}
	else if (angle > 90 && angle < 180)
	{
		return angle;
	}
}

void CAlgorithm::GettingCandidatePoints(CEdge c1, vector<CEdge> active)
{
	for (int i = 0;i < active.size();i++)
	{
		CEdge e = active[i];
		if (!(e.isEqual(c1)))
		{
			if (c1.startNode == e.endNode)
			{
				frontPoint = e.startNode;
			}
			if (c1.endNode == e.startNode)
			{
				rearPoint = e.endNode;
			}
		}
	}
	std::cout << "候选点：" << frontPoint.x << " " << frontPoint.y << " " << frontPoint.z << std::endl;
	std::cout << "候选点：" << rearPoint.x << " " << rearPoint.y << " " << rearPoint.z << std::endl;
}

vector<double> CAlgorithm::getNormal(MyPoint p0, MyPoint p1, MyPoint p2)
{
	// 存放法矢
	vector<double>list;
	double v1x = p1.x - p0.x;
	double v1y = p1.y - p0.y;

	double v1z = p1.z - p0.z;
	double v2x = p2.x - p1.x;
	double v2y = p2.y - p1.y;
	double v2z = p2.z - p1.z;
	double x = v1y * v2z - v1z * v2y;
	double y = v1z * v2x - v1x * v2z;
	double z = v1x * v2y - v1y * v2x;
	double len = sqrt(x*x + y * y + z * z);
	if (len == 0)
	{
		return list;
	}
	else {
		list.push_back(x / len);
		list.push_back(y / len);
		list.push_back(z / len);
	}
	return list;
}

double CAlgorithm::GetArea(CTriangles Triang1)
{
	//int i = 0;
	double a, b, c, p, area;
	//计算该面的法向量  
	Vector3 m, n, q,
		pt1(Triang1.p1.x, Triang1.p1.y, Triang1.p1.z),
		pt2(Triang1.p2.x, Triang1.p2.y, Triang1.p2.z),
		pt0(Triang1.p0.x, Triang1.p0.y, Triang1.p0.z);
	m = pt1 - pt0;
	n = pt2 - pt1;
	//计算两个向量的叉乘
	q = crossProduct(m, n);

	a = distance(pt1, pt0);
	b = distance(pt2, pt1);
	c = distance(pt0, pt2);
	p = (a + b + c)*0.5f;
	area = sqrt(p*(p - a)*(p - b)*(p - c));
	return area;
}

// 计算模型体积与面积
void CAlgorithm::CalculateVolumeAndArea(map<int, MyPoint> &points, std::vector<CTriangles> &triangle, double &volume, double &area)
{
	// TODO: 在此处添加实现代码.
	double x1, y1, z1, x2, y2, z2, x3, y3, z3;
	double v321, v231, v312, v132, v213, v123;
	for (auto it = triangle.begin(); it != triangle.end(); it++)
	{
		x1 = it->p0.x;
		y1 = it->p0.y;
		z1 = it->p0.z;
		x2 = it->p1.x;
		y2 = it->p1.y;
		z2 = it->p1.z;
		x3 = it->p2.x;
		y3 = it->p2.y;
		z3 = it->p2.z;
		//计算体积
		v321 = x3 * y2 * z1;
		v231 = x2 * y3 * z1;
		v312 = x3 * y1 * z2;
		v132 = x1 * y3 * z2;
		v213 = x2 * y1 * z3;
		v123 = x1 * y2 * z3;
		volume += ((1.0f / 6.0f) * (-v321 + v231 + v312 - v132 - v213 + v123));

		//计算面积
		CAlgorithm calgorithm;
		area += calgorithm.GetArea(*it);
	}
}

// 去除离散三角形
void CAlgorithm::RemoveDiscreteTriangles(std::map<int, MyPoint> &points, std::vector<CTriangles> &triangles)
{
	// TODO: 在此处添加实现代码.

	std::vector<std::map<int, MyPoint>> model;
	while (!points.empty())
	{
		int pointSerailNumber = points.begin()->first;
		int index = 0;
		std::map<int, MyPoint> neighborPointAll; //所有的领域节点
		neighborPointAll.insert(pair<int, MyPoint>(pointSerailNumber, points[pointSerailNumber]));
		std::list<int> neighborPointN; // 第N环的节点
		neighborPointN.push_back(pointSerailNumber);

		//找到点pointSerailNumber的所有领域节点
		while (!neighborPointN.empty())
		{
			int ringSize = neighborPointN.size();// 当前环节点的个数
			for (int i = 0; i < ringSize; i++)
			{	
				index = neighborPointN.front();
				neighborPointN.pop_front();
				//寻找节点index的邻居节点
				for (auto it = points[index].m_TrianglesList.begin(); it != points[index].m_TrianglesList.end(); it++)
				{
					if (neighborPointAll.count(triangles[*it].mp0) == 0)
					{
						neighborPointN.push_back(triangles[*it].mp0);
						neighborPointAll.insert(pair<int, MyPoint>(triangles[*it].mp0, triangles[*it].p0));
					}
					if (neighborPointAll.count(triangles[*it].mp1) == 0)
					{
						neighborPointN.push_back(triangles[*it].mp1);
						neighborPointAll.insert(pair<int, MyPoint>(triangles[*it].mp1, triangles[*it].p1));
					}
					if (neighborPointAll.count(triangles[*it].mp2) == 0)
					{
						neighborPointN.push_back(triangles[*it].mp2);
						neighborPointAll.insert(pair<int, MyPoint>(triangles[*it].mp2, triangles[*it].p2));
					}
				}
			}
		}
		
		//从points中删除已经找到的领域点
		for (auto it = points.begin(); it != points.end(); )
		{
			if (neighborPointAll.count(it->first) == 0)
			{
				it++;
			}
			else
			{
				it = points.erase(it);
			}
		}
		model.push_back(neighborPointAll);
	}
	
	int max = 0;
	for (int i = 0; i < model.size(); i++)
	{
		if (model[i].size() > max)
		{
			max = model[i].size();
			points = model[i];
		}
	}

	for (auto it = triangles.begin(); it != triangles.end(); )
	{
		if ((points.count(it->mp0) == 0) && (points.count(it->mp1) == 0) && (points.count(it->mp2) == 0))
		{
			it = triangles.erase(it);
		}
		else
		{
			it++;
		}
	}
}
