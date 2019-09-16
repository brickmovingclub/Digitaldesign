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
	// 存储候选点
	MyPoint frontPoint;
	MyPoint rearPoint;
// pcd数据读取
	pcl::PointCloud<pcl::PointXYZ>::Ptr ReadPclFile(string m_fileName);

//  K阶领域显示
	static std::set<MyPoint> KOrderDomain(int pointSerailNumber, int n, std::map<int, MyPoint> points, std::vector<CTriangles> triangles);

// 叶子节点显示
	static void ShowLeafNodes(pcl::PointCloud<pcl::PointXYZ>::Ptr m_cloud, std::vector<Eigen::Vector3f> &min, std::vector<Eigen::Vector3f> &max);

// 三维重建
	string ThreeDimensionalReconstruction();

// 孔洞修补
	vector<CTriangles> HoleRepair(vector<CEdge>m_borderEdgeList, vector<CTriangles> m_CTrianglesData);

// 孔洞边界获取
	map<int, vector<CEdge>> GetHole(vector<CEdge>m_borderEdgeList);
// 计算两条边的夹角
	double GetAngleRear(CEdge currentEdge, CEdge otherEdge);
	double getDegAngle(Point1 p1, Point1 p2, Point1 p3);
// 获取二面角
	double GetAngle(CTriangles ct1, CTriangles ct2);
// 获取候选点
	void GettingCandidatePoints(CEdge c1, vector<CEdge>active);
// 获取法矢
	vector<double> getNormal(MyPoint p0, MyPoint p1, MyPoint p2);
// 面积计算
	double GetArea(CTriangles Triang1);

// 计算模型体积与面积
	static void CalculateVolumeAndArea(map<int, MyPoint> &points, std::vector<CTriangles> &triangle, double &volume, double &area);

	// 去除离散三角形
	static void RemoveDiscreteTriangles(std::map<int, MyPoint> &points, std::vector<CTriangles> &triangles);
};

