#pragma once
#include <string>
using namespace std;
class CAlgorithm
{
public:
	CAlgorithm();
	~CAlgorithm();
// pcd数据读取
	void ReadPclFile(string m_fileName);

//  K阶领域显示
	void KOrderDomain();

// 叶子节点显示
	void ShowLeafNodes();

// 三维重建
	pcl::PolygonMesh ThreeDimensionalReconstruction(string m_fileName);

// 孔洞修补
	void HoleRepair();
};

