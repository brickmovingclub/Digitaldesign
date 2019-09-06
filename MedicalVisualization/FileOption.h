#pragma once
//�ߵļ���
//#include "Vector3.h"
class CTriangles;
class FileOption
{
public:
	FileOption();
	~FileOption();
	//�洢����Ƭ��Ϣ
	vector<CTriangles> m_CTrianglesData;
	map<MyPoint, MyPoint> m_MapPoint;
	map<int, MyPoint>  m_SortMapPoint;
	vector<CEdge>m_allListCEdgeBorder;
	//������
	map<int, Vector3> normal;

	
	//���ܺ���
	//��ȡply��ʽ�ļ�
	bool ReadPlyFile(const char *cfilename);
	bool ReadPly(const char *buffer);
	//��ȡASCLL��STL�ļ�
	bool ReadAscllStlFile(const char *cfilename);
	bool ReadAscllStl(const char *buffer);//��stl�ļ�
	//��ȡ������stl�ļ�
	void Bin2ToStl();
	int cpyint(const char*& p);
	float cpyfloat(const char*& p);
	bool ReadBinary(const char * buffer);

	//��ȡ.asc�ļ�
	void ReadAscFile(const char *cfilename); 
	//.asc�ļ�תPcd�ļ�
	string AscToPcd();

	//�ѻ��ֺõ�������Ƭ���Ϊ.ply�ļ�
	void SaveAsPLY(pcl::PointCloud<pcl::PointXYZ>::Ptr cloudTriangles, pcl::PolygonMesh triangles); 
	//���Ϊply��ʽ�ļ�
	void SavePly(const char * cfilename);
	//���Ϊstl��ʽ�ļ�
	void SaveAsStl(const char * cfilename);

	

};

