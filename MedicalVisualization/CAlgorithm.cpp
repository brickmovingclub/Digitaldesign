#include "stdafx.h"
#include "CAlgorithm.h"

using namespace std;
// ��������
pcl::PointCloud<pcl::PointXYZ>::Ptr cloudTriangles(new pcl::PointCloud<pcl::PointXYZ>);
pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

CAlgorithm::CAlgorithm()
{

}

CAlgorithm::~CAlgorithm()
{
}

// ��ȡPCD�ļ���ʽ����
pcl::PointCloud<pcl::PointXYZ>::Ptr CAlgorithm::ReadPclFile(string m_fileName)
{
	pcl::io::loadPCDFile<pcl::PointXYZ>(m_fileName, *cloud);

	if (pcl::io::loadPCDFile<pcl::PointXYZ>(m_fileName, *cloud) == -1)
	{
		std::cout << "Cloud reading failed��" << std::endl;
		return cloud;
	}
	return cloud;
}

//  K��������ʾ
std::set<MyPoint> CAlgorithm::KOrderDomain(int pointSerailNumber, int n, std::map<int, MyPoint> points, std::vector<CTriangles> triangles)
{
	int index = 0;
	std::set<MyPoint> neighborPointAll; //���еĽڵ�
	neighborPointAll.insert(points[pointSerailNumber]);
	std::list<int> neighborPointN; // ��N���Ľڵ�
	neighborPointN.push_back(pointSerailNumber);
	for (int ring = 0; ring < n; ring++)
	{
		// ��ring���Ľڵ�
		int ringSize = neighborPointN.size();// ��ǰ���ڵ�ĸ���
		for (int i = 0; i < ringSize && !neighborPointN.empty(); i++)
		{
			//�ҵ���ı��
			index = neighborPointN.front();
			neighborPointN.pop_front();
			//Ѱ�ҽڵ�index���ھӽڵ�
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

// Ҷ�ӽڵ���ʾ
void CAlgorithm::ShowLeafNodes(pcl::PointCloud<pcl::PointXYZ>::Ptr m_cloud, std::vector<Eigen::Vector3f> &min, std::vector<Eigen::Vector3f> &max)
{
	float resolu = 1.0f;
	pcl::octree::OctreePointCloudSearch<pcl::PointXYZ> tree(resolu);
	tree.setInputCloud(m_cloud);
	tree.addPointsFromInputCloud();
	std::cout << "Ҷ�ӽڵ������" << tree.getLeafCount() << std::endl;

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

// ��ά�ؽ�
string CAlgorithm::ThreeDimensionalReconstruction()
{
	pcl::PolygonMesh triangles;//����������������ڴ洢���

	//Normal ������
	pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> n;
	pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
	pcl::search::KdTree < pcl::PointXYZ >::Ptr tree(new pcl::search::KdTree < pcl::PointXYZ >);
	tree->setInputCloud(cloud);
	n.setInputCloud(cloud);
	n.setSearchMethod(tree);
	n.setKSearch(10);
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
	gp3.setMaximumNearestNeighbors(50);//��������������ڵ���������
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
		//���Ӷ�����Ϣ
	std::vector<int> parts = gp3.getPartIDs();
	std::vector<int> states = gp3.getPointStates();
	return "bunny.vtk";
}

// �׶��޲�
vector<CTriangles> CAlgorithm::HoleRepair(vector<CEdge>m_borderEdgeList, vector<CTriangles> m_CTrianglesData) 
{
	std::cout <<"֮ǰ��Ĵ�С��" <<m_CTrianglesData.size() << std::endl;
	// ��ȡ�׶���
	map<int, vector<CEdge>>m_holeList;
	// �����Ŀ׶���
	map<int, vector<CEdge>>m_sortHoleList;
	// �����߼���
	map<int, vector<CEdge>>m_resultCEdgeList;
	// ��ѡ��

	int m_count = 0;
	m_holeList = GetHole(m_borderEdgeList);

	
	// ����֮ǰ��ÿһ������list��������
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
						//cout << "�� �� " << my.x << " "<<my.y<<" "<<my.z<<endl;

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
	// �����㷨
	std::cout << "�׶��ĸ��� " << m_sortHoleList.size() << std::endl;

	for (auto it = m_sortHoleList.begin();it != m_sortHoleList.end();it++)
	{
		vector<CEdge>m_activeCEdgeList=it->second;
		vector<CEdge>m_listResult;
		if (m_activeCEdgeList.size() >= 2)
		{
			// ��ǰ��
				// ��ǰ��
			CEdge  currentEdge(m_activeCEdgeList[0].startNode, m_activeCEdgeList[1].endNode);
			m_listResult.push_back(currentEdge);
			// ��ǰ��
			CTriangles ct(m_activeCEdgeList[0].startNode, m_activeCEdgeList[0].endNode, m_activeCEdgeList[1].endNode);
			m_CTrianglesData.push_back(ct);
			// ɾ����С�ǵı�
			m_activeCEdgeList.erase(m_activeCEdgeList.begin());

			m_activeCEdgeList.erase(m_activeCEdgeList.begin());
			int i = 0;
			do
			{
				// ��ȡ��ѡ��
				GettingCandidatePoints(currentEdge, m_activeCEdgeList);
				// ��������
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
				// ���ӷ�����

				if (A > B)
				{
					currentEdge.ToString();

					std::cout << "A: " << A << std::endl;
					currentEdge.startNode = frontPoint;
					currentEdge.endNode = currentEdge.endNode;
					ct = ctFront;
					std::cout << "���ɺ�ıߣ� " << std::endl;
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
					std::cout << "���ɺ�ıߣ� " << std::endl;
					m_CTrianglesData.push_back(ctRear);

					currentEdge.ToString();

				}
				else
				{
					// ������������������
					double areaFront = GetArea(ctFront);
					double areaRear = GetArea(ctRear);
					if (areaFront > areaRear)
					{
						std::cout << "A: " << A << std::endl;
						currentEdge.startNode = frontPoint;
						currentEdge.endNode = currentEdge.endNode;
						ct = ctFront;
						std::cout << "���ɺ�ıߣ� " << std::endl;
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
						std::cout << "���ɺ�ıߣ� " << std::endl;

						currentEdge.ToString();
						m_CTrianglesData.push_back(ctRear);

					}

				}

				m_listResult.push_back(currentEdge);
				// ɾ��ͷ��������
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
			std::cout << "��ǰ��Ĵ�С��" << m_CTrianglesData.size() << std::endl;
		}
	}
	return m_CTrianglesData;
}

// ��ȡ�׶��߽�
map<int, vector<CEdge>> CAlgorithm::GetHole(vector<CEdge>m_borderEdgeList)
{
	// ��ȡ�׶���
	map<int, vector<CEdge>>m_holeList;
	// �ݴ�׶��ߵļ���
	vector<CEdge>m_tempList;
	// ��ȡ�׶���
	for (auto it = m_borderEdgeList.begin();it != m_borderEdgeList.end();it++)
	{
		CEdge e = *it;
		if (count(m_borderEdgeList.begin(), m_borderEdgeList.end(), e) == 1)
		{
			m_tempList.push_back(e);
		}
	}
	// ��ȡÿ���׶�
	int i = 0;
	int m_countEdge = m_tempList.size();
	while (m_countEdge>0)
	{
		// ����
		vector<CEdge>m_tempListCEdge=m_tempList;
		// �ݴ�
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
							//cout << "�� �� " << my.x << " "<<my.y<<" "<<my.z<<endl;

							result.push_back(m_tempListCEdge[i]);

							c1 = m_tempListCEdge[i];
							my = c1.endNode;
							break;
						}
					}
				}
			}
		}
		// ����������ɾ���Ѿ��Ҷ��ɹ��ı�
		// �ݴ漯��
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
	// ͨ���Ƕȼ�������

	double angle = 0.0f;
	// ��ȡ��ķ�ʸ
	vector<double>ct1N = getNormal(ct1.p0, ct1.p1, ct1.p2);
	vector<double>ct2N = getNormal(ct2.p0, ct2.p1, ct2.p2);
	if (ct1N.size() < 3 || ct2N.size() < 3)
		return -1;
	// ��������
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
	std::cout << "��ѡ�㣺" << frontPoint.x << " " << frontPoint.y << " " << frontPoint.z << std::endl;
	std::cout << "��ѡ�㣺" << rearPoint.x << " " << rearPoint.y << " " << rearPoint.z << std::endl;
}

vector<double> CAlgorithm::getNormal(MyPoint p0, MyPoint p1, MyPoint p2)
{
	// ��ŷ�ʸ
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
	//�������ķ�����  
	Vector3 m, n, q,
		pt1(Triang1.p1.x, Triang1.p1.y, Triang1.p1.z),
		pt2(Triang1.p2.x, Triang1.p2.y, Triang1.p2.z),
		pt0(Triang1.p0.x, Triang1.p0.y, Triang1.p0.z);
	m = pt1 - pt0;
	n = pt2 - pt1;
	//�������������Ĳ��
	q = crossProduct(m, n);

	a = distance(pt1, pt0);
	b = distance(pt2, pt1);
	c = distance(pt0, pt2);
	p = (a + b + c)*0.5f;
	area = sqrt(p*(p - a)*(p - b)*(p - c));
	return area;
}

// ����ģ����������
void CAlgorithm::CalculateVolumeAndArea(map<int, MyPoint> &points, std::vector<CTriangles> &triangle, double &volume, double &area)
{
	// TODO: �ڴ˴����ʵ�ִ���.
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
		//�������
		v321 = x3 * y2 * z1;
		v231 = x2 * y3 * z1;
		v312 = x3 * y1 * z2;
		v132 = x1 * y3 * z2;
		v213 = x2 * y1 * z3;
		v123 = x1 * y2 * z3;
		volume += ((1.0f / 6.0f) * (-v321 + v231 + v312 - v132 - v213 + v123));

		//�������
		CAlgorithm calgorithm;
		area += calgorithm.GetArea(*it);
	}
}

// ȥ����ɢ������
void CAlgorithm::RemoveDiscreteTriangles(std::map<int, MyPoint> &points, std::vector<CTriangles> &triangles)
{
	// TODO: �ڴ˴����ʵ�ִ���.

	std::vector<std::map<int, MyPoint>> model;
	while (!points.empty())
	{
		int pointSerailNumber = points.begin()->first;
		int index = 0;
		std::map<int, MyPoint> neighborPointAll; //���е�����ڵ�
		neighborPointAll.insert(pair<int, MyPoint>(pointSerailNumber, points[pointSerailNumber]));
		std::list<int> neighborPointN; // ��N���Ľڵ�
		neighborPointN.push_back(pointSerailNumber);

		//�ҵ���pointSerailNumber����������ڵ�
		while (!neighborPointN.empty())
		{
			int ringSize = neighborPointN.size();// ��ǰ���ڵ�ĸ���
			for (int i = 0; i < ringSize; i++)
			{	
				index = neighborPointN.front();
				neighborPointN.pop_front();
				//Ѱ�ҽڵ�index���ھӽڵ�
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
		
		//��points��ɾ���Ѿ��ҵ��������
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
