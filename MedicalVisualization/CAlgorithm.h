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
	void ReadPclFile(string m_fileName);

//  K��������ʾ
	void KOrderDomain();

// Ҷ�ӽڵ���ʾ
	void ShowLeafNodes();

// ��ά�ؽ�
	pcl::PolygonMesh ThreeDimensionalReconstruction(string m_fileName);

// �׶��޲�
	void HoleRepair(vector<CEdge>m_borderEdgeList);

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

};

