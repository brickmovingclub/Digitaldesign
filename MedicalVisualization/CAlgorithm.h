#pragma once
#include <string>
using namespace std;
class CAlgorithm
{
public:
	CAlgorithm();
	~CAlgorithm();
// pcd���ݶ�ȡ
	void ReadPclFile(string m_fileName);

//  K��������ʾ
	void KOrderDomain();

// Ҷ�ӽڵ���ʾ
	void ShowLeafNodes();

// ��ά�ؽ�
	pcl::PolygonMesh ThreeDimensionalReconstruction(string m_fileName);

// �׶��޲�
	void HoleRepair();
};

