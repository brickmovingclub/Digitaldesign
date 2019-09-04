#pragma once
//边的集合

class FileOption
{
public:
	FileOption();
	~FileOption();
	//存储的面片信息
	vector<CTriangles> m_CTrianglesData;
	map<MyPoint, MyPoint> m_MapPoint;
	map<int, MyPoint>  m_SortMapPoint;
	list<CEdge>m_allListCEdgeBorder;	
	
	//功能函数
	//读取ply格式文件
	bool ReadPlyFile(const char *cfilename);
	//读取ASCLL码STL文件
	bool ReadAscllStlFile(const char *cfilename);
	bool ReadAscllStl(const char *buffer);//读stl文件
	//读取二进制stl文件
	int cpyint(const char*& p);
	float cpyfloat(const char*& p);
	void Bin2ToStl();
	bool ReadBinary(const char * buffer);

	//读取.asc文件
	void ReadAscFile(const char *cfilename); 
	//.asc文件转Pcd文件
	string AscToPcd();

	//把划分好的三角面片另存为.ply文件
	void SaveAsPLY(pcl::PointCloud<pcl::PointXYZ>::Ptr cloudTriangles, pcl::PolygonMesh triangles); 
	//另存为ply格式文件
	void SavePly();

};

