#include "stdafx.h"
#include "MedicalVisualization.h"
#include "FileOption.h"
using namespace std;
unsigned int unTriangles;
char* memwriter;
vector<MyPoint> pointList;
using namespace std;

FileOption::FileOption()
{
}


FileOption::~FileOption()
{
}

int FileOption::cpyint(const char*& p)
{
	int cpy;
	memwriter = (char*)&cpy;
	memcpy(memwriter, p, 4);
	p += 4;
	return cpy;
}
float FileOption::cpyfloat(const char*& p)
{
	float cpy;
	memwriter = (char*)&cpy;
	memcpy(memwriter, p, 4);
	p += 4;
	return cpy;
}
//读取二进制stl文件
void FileOption::Bin2ToStl()
{
	FILE * pFile;
	long lSize;
	char* buffer;
	size_t result;
	const char *cfilename = "bunny.stl";
	/* 若要一个byte不漏地读入整个文件，只能采用二进制方式打开  */
	fopen_s(&pFile, cfilename, "rb");
	if (pFile == NULL)
	{
		fputs("File error", stderr);
		exit(1);
	}

	/* 获取文件大小 */
	fseek(pFile, 0, SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);

	/* 分配内存存储整个文件 */
	buffer = (char*)malloc(sizeof(char)*lSize);
	if (buffer == NULL)
	{
		fputs("Memory error", stderr);
		exit(2);
	}

	/* 将文件拷贝到buffer中 */
	result = fread(buffer, 1, lSize, pFile);
	if (result != lSize)
	{
		fputs("Reading error", stderr);
		exit(3);
	}


	/* 结束演示，关闭文件并释放内存 */
	fclose(pFile);

	ios::sync_with_stdio(false);

	ReadBinary(buffer);
	//Repaithole(sortEdge);
	ios::sync_with_stdio(true);

	free(buffer);
	//return true;
	std::cout << "点的个数: " << pointList.size() << std::endl;
}

//读取二进制stl文件
bool FileOption::ReadBinary(const char * buffer)
{
	vector<CEdge>listBorder;
	const char* p = buffer;
	char name[80];
	int i, j;
	memcpy(name, p, 80);
	p += 80;
	unTriangles = cpyint(p);
	std::pair<std::map<MyPoint, MyPoint>::iterator, bool> ret;
	std::cout << "unTriangles " << unTriangles << std::endl;
	int index = 0;
	for (i = 0; i < unTriangles; i++)
	{
		p += 12;//跳过头部法向量
		j = 0;
		MyPoint p0(cpyfloat(p), cpyfloat(p), cpyfloat(p));
		p0.m_TrianglesList.push_back(i);
		//pointList.push_back(p0);
		ret = m_MapPoint.insert(std::pair<MyPoint, MyPoint>(p0, p0));
		if (ret.second == false) 
		{
			map<MyPoint, MyPoint>::iterator it = m_MapPoint.find(p0);
			it->second.AddTriangles(i);
			
		}
		j++;
		MyPoint p1(cpyfloat(p), cpyfloat(p), cpyfloat(p));
		p1.m_TrianglesList.push_back(i);
		ret = m_MapPoint.insert(std::pair<MyPoint, MyPoint>(p1, p1));
		if (ret.second == false)
		{
			map<MyPoint, MyPoint>::iterator it = m_MapPoint.find(p1);
			it->second.AddTriangles(i);
		}
		//pointList.push_back(p1);
		j++;
		MyPoint p2(cpyfloat(p), cpyfloat(p), cpyfloat(p));
		p2.m_TrianglesList.push_back(i);
		ret = m_MapPoint.insert(std::pair<MyPoint, MyPoint>(p2, p2));
		if (ret.second == false)
		{
			map<MyPoint, MyPoint>::iterator it = m_MapPoint.find(p2);
			it->second.AddTriangles(i);
		}
		//pointList.push_back(p2);
		// 定义边的信息

		CEdge e(p0, p1);
		e.index = index;
		CEdge e1(p1, p2);
		e1.index = index;

		CEdge e2(p2, p0);
		e2.index = index;

		m_allListCEdgeBorder.push_back(e);
		m_allListCEdgeBorder.push_back(e1);
		m_allListCEdgeBorder.push_back(e2);
		CTriangles b;
		b.p0 = p0;
		b.p1 = p1;
		b.p2 = p2;

		m_CTrianglesData.push_back(b);
		index++;
		p += 2;//跳过尾部标志
	}
	i = 0;
	for (map<MyPoint, MyPoint>::iterator it = m_MapPoint.begin(); it != m_MapPoint.end(); it++)
	{
		m_SortMapPoint.insert(pair<int, MyPoint>(i, it->second));
	}
	return false;
}

//asc文件的相关文件操作
//读取.asc文件
void FileOption::ReadAscFile(const char * cfilename)
{
	FILE *pfile;
	long  size;
	char *buffer;
	size_t result;
	//打开文件
	fopen_s(&pfile, cfilename, "rb");
	if (pfile == NULL)
	{
		fputs("file error", stderr);
		exit(1);

	}
	//获取文件大小
	fseek(pfile, 0, SEEK_END);
	size = ftell(pfile);

	rewind(pfile);
	//为文件分配内存
	buffer = (char*)malloc(sizeof(char)*size);
	if (buffer == NULL)
	{
		fputs("memory error", stderr);
		exit(2);
	}
	//将文件拷贝到buffer中
	result = fread(buffer, 1, size, pfile);
	if (result != size)
	{
		fputs("reading error", stderr);
		exit(3);
	}
	//关闭文件，释放内存
	fclose(pfile);
	ios::sync_with_stdio(false);
	//AscToPcd(buffer);
	//读取buffer中的点数据
	int i = 0;
	string us1, us2, us3;
	//float x, y, z; //点的坐标
	stringstream ss(buffer);
	ss.get();

	do {
		MyPoint a;
		ss >> a.x >> a.y >> a.z;
		a.R = 1;
		a.G = 1;
		a.B = 1;
		if (a.x == NULL)
			break;

		m_SortMapPoint.insert(std::pair<int, MyPoint>(i, a));
		//cout << a.x << " " << a.y << " " << a.z << endl;
		i++;
	} while (1);
	ios::sync_with_stdio(true);
	free(buffer);
}

//.asc文件转Pcd文件
string FileOption::AscToPcd()
{
	if (m_SortMapPoint.size() == 0)
		return 0;
	string fileName = "bunny.pcd";
	ofstream of(fileName.c_str());
	of.precision(std::numeric_limits<double>::digits10);
	//ofstream OpenFile("D:\\vs2017projects\\Task2\\testmap.ply");
	if (of.fail())
	{
		std::cout << "打开文件错误!" << std::endl;
	}
	of << "# .PCD v.5 - Point Cloud Data file format" << std::endl;
	of << "VERSION .5" << std::endl;
	of << "FIELDS x y z " << std::endl;
	of << "SIZE 4 4 4 " << std::endl;
	of << "TYPE F F F " << std::endl;
	of << "COUNT 1 1 1 " << std::endl;
	of << "WIDTH " << m_SortMapPoint.size() << std::endl;
	of << "HEIGHT 1" << std::endl;
	of << "POINTS " << m_SortMapPoint.size() << std::endl;
	of << "DATA ascii" << std::endl;
	// 读取点的信息
	for (auto iter = m_SortMapPoint.begin(); iter != m_SortMapPoint.end(); iter++)
	{
		of << iter->second.x << " " << iter->second.y << " " << iter->second.z << std::endl;
		//std::cout<< iter->second.x << " " << iter->second.y << " " << iter->second.z << std::endl;
	}
	return fileName;
}

//把划分好的三角面片另存为.ply文件
void FileOption::SaveAsPLY(pcl::PointCloud<pcl::PointXYZ>::Ptr cloudTriangles, pcl::PolygonMesh triangles)
{
	string fileName = "bunny.ply";
	ofstream of(fileName.c_str());
	of.precision(std::numeric_limits<double>::digits10);
	//ofstream OpenFile("D:\\vs2017projects\\Task2\\testmap.ply");
	if (of.fail())
	{
		std::cout << "打开文件错误!" << std::endl;
	}
	of << "ply" << std::endl;
	of << "format ascii 1.0" << std::endl;
	of << "comment generated by platoply" << std::endl;
	of << "element vertex " << triangles.cloud.width << std::endl;
	of << "property float32 x" << std::endl;
	of << "property float32 y" << std::endl;
	of << "property float32 z" << std::endl;
	of << "element face " << triangles.polygons.size() << std::endl;
	of << "property list uint8 int32 vertex_indices" << std::endl;
	of << "end_header" << std::endl;
	for (int it = 0; it < cloudTriangles->points.size(); it++)
	{
		of << " " << cloudTriangles->points[it].x << " " << cloudTriangles->points[it].y << " " << cloudTriangles->points[it].z << std::endl;
	}

	for (int it = 0; it < triangles.polygons.size(); it++)
	{
		of << 3 << " " << triangles.polygons[it].vertices[0] << " " << triangles.polygons[it].vertices[1] << " " << triangles.polygons[it].vertices[2] << std::endl;
	}
}
