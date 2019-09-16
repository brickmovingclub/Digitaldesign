#pragma once
#include <string>
typedef Eigen::Vector3d Point1;

using namespace std;
class CAlgorithm
{
public:
	CAlgorithm();
	~CAlgorithm();

	vector<CTriangles> Triangleslist;
	// �洢��ѡ��
	MyPoint frontPoint;
	MyPoint rearPoint;
// pcd���ݶ�ȡ
	pcl::PointCloud<pcl::PointXYZ>::Ptr ReadPclFile(string m_fileName);

//  K��������ʾ
	static std::set<MyPoint> KOrderDomain(int pointSerailNumber, int n, std::map<int, MyPoint> points, std::vector<CTriangles> triangles);

// Ҷ�ӽڵ���ʾ
	static void ShowLeafNodes(pcl::PointCloud<pcl::PointXYZ>::Ptr m_cloud, std::vector<Eigen::Vector3f> &min, std::vector<Eigen::Vector3f> &max);

// ��ά�ؽ�
	string ThreeDimensionalReconstruction();

// �׶��޲�
	vector<CTriangles> HoleRepair(vector<CEdge>m_borderEdgeList, vector<CTriangles> m_CTrianglesData);

// �׶��߽��ȡ
	map<int, vector<CEdge>> GetHole(vector<CEdge>m_borderEdgeList);
// ���������ߵļн�
	double GetAngleRear(CEdge currentEdge, CEdge otherEdge);
	double getDegAngle(Point1 p1, Point1 p2, Point1 p3);
// ��ȡ�����
	double GetAngle(CTriangles ct1, CTriangles ct2);
// ��ȡ��ѡ��
	void GettingCandidatePoints(CEdge c1, vector<CEdge>active);
// ��ȡ��ʸ
	vector<double> getNormal(MyPoint p0, MyPoint p1, MyPoint p2);
// �������
	double GetArea(CTriangles Triang1);

// ����ģ����������
	static void CalculateVolumeAndArea(map<int, MyPoint> &points, std::vector<CTriangles> &triangle, double &volume, double &area);

	// ȥ����ɢ������
	static void RemoveDiscreteTriangles(std::map<int, MyPoint> &points, std::vector<CTriangles> &triangles);
};

