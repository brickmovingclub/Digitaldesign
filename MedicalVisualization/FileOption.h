#pragma once
//�ߵļ���
list<CEdge>listCEdge;
class FileOption
{
public:
	FileOption();
	~FileOption();
	//�洢����Ƭ��Ϣ
	vector<CTriangles> m_CTrianglesData;
	map<int, MyPoint>  m_MapPoint;;
	
	
	//���ܺ���
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

};

