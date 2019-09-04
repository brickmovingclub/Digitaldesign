#pragma once
//�ߵļ���

class FileOption
{
public:
	FileOption();
	~FileOption();
	//�洢����Ƭ��Ϣ
	vector<CTriangles> m_CTrianglesData;
	map<MyPoint, MyPoint> m_MapPoint;
	map<int, MyPoint>  m_SortMapPoint;
	list<CEdge>m_allListCEdgeBorder;	
	
	//���ܺ���
	//��ȡply��ʽ�ļ�
	bool ReadPlyFile(const char *cfilename);
	//��ȡASCLL��STL�ļ�
	bool ReadAscllStlFile(const char *cfilename);
	bool ReadAscllStl(const char *buffer);//��stl�ļ�
	//��ȡ������stl�ļ�
	int cpyint(const char*& p);
	float cpyfloat(const char*& p);
	void Bin2ToStl();
	bool ReadBinary(const char * buffer);

	//��ȡ.asc�ļ�
	void ReadAscFile(const char *cfilename); 
	//.asc�ļ�תPcd�ļ�
	string AscToPcd();

	//�ѻ��ֺõ�������Ƭ���Ϊ.ply�ļ�
	void SaveAsPLY(pcl::PointCloud<pcl::PointXYZ>::Ptr cloudTriangles, pcl::PolygonMesh triangles); 
	//���Ϊply��ʽ�ļ�
	void SavePly();

};

