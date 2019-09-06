#pragma once
//边的集合
//#include "Vector3.h"
class CTriangles;
class FileOption
{
public:
	FileOption();
	~FileOption();
	//存储的面片信息
	vector<CTriangles> m_CTrianglesData;
	map<MyPoint, MyPoint> m_MapPoint;
	map<int, MyPoint>  m_SortMapPoint;
	vector<CEdge>m_allListCEdgeBorder;
	//法向量
	map<int, Vector3> normal;

	
	//功能函数
	//读取ply格式文件
	bool ReadPlyFile(const char *cfilename);
	bool ReadPly(const char *buffer);
	//读取ASCLL码STL文件
	bool ReadAscllStlFile(const char *cfilename);
	bool ReadAscllStl(const char *buffer);//读stl文件
	//读取二进制stl文件
	void Bin2ToStl();
	int cpyint(const char*& p);
	float cpyfloat(const char*& p);
	bool ReadBinary(const char * buffer);

	//读取.asc文件
	void ReadAscFile(const char *cfilename); 
	//.asc文件转Pcd文件
	string AscToPcd();

	//把划分好的三角面片另存为.ply文件
	void SaveAsPLY(pcl::PointCloud<pcl::PointXYZ>::Ptr cloudTriangles, pcl::PolygonMesh triangles); 
	//另存为ply格式文件
	void SavePly(const char * cfilename);
	//另存为stl格式文件
	void SaveAsStl(const char * cfilename);

	

};

