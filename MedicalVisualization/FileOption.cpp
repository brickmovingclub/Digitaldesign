#include "stdafx.h"
//#include "MedicalVisualization.h"
#include "Vector3.h"
#include "CTriangles.h"

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
//读取ply格式文件
bool FileOption::ReadPlyFile(const char *cfilename)
{
	FILE *pfile;//创建一个文件的对象
	long size;//文件的大小
	char *buffer;
	size_t result;
	//打开文件
	fopen_s(&pfile, cfilename, "rb");
	if (pfile == NULL) //判断文件是否为空，如果为空，提示文件错误
	{
		fputs("file error", stderr);
		exit(1);

	}
	//获取文件大小
	fseek(pfile, 0, SEEK_END);
	size = ftell(pfile);
	rewind(pfile);
	//为文件分配内存空间
	buffer = (char *)malloc(sizeof(char)*size);
	if (buffer == NULL) //判断是否为文件分配了内存空间
	{
		fputs("memory error", stderr);
		exit(2);
	}
	//将文件拷贝到申请的内存buffer中去
	result = fread(buffer, 1, size, pfile);
	if (result != size) //判断是否成功拷贝了文件
	{
		fputs("reading error", stderr);
		exit(3);
	}
	fclose(pfile);//关闭文件，释放内存
	ios::sync_with_stdio(false);
	ReadPly(buffer);//读取ply文件里的信息
	ios::sync_with_stdio(false);
	free(buffer);//释放buffer的内存；
	return true;
}

bool FileOption::ReadPly(const char * buffer)
{
	
	float x, y, z;
	int i, j;
	CTriangles a;
	MyPoint b;
	string name, useless;
	int num;
	stringstream ss(buffer);
	ss.get();
	for (i = 0; i <= 9; i++) //先跳过ply前面9行没有用的信息
	{
		getline(ss, useless);
	}
	i = 0;
	do
	{

		ss >> x >> y >> z;
		if (x == 3)
		{
			break;
		}

		b.x = x;
		b.y = y;
		b.z = z;
		m_SortMapPoint.insert(std::pair<int, MyPoint>(i, b));
		i++;

	} while (1);
	i = 0;
	useless = x;
	a.mp0= y;
	a.mp1 = z;
	ss >> a.mp2;
	a.p0 = m_SortMapPoint[a.mp0];
	m_SortMapPoint[a.mp0].AddTriangles(i);
	a.p1 = m_SortMapPoint[a.mp1];
	m_SortMapPoint[a.mp1].AddTriangles(i);
	a.p2 = m_SortMapPoint[a.mp2];
	m_SortMapPoint[a.mp2].AddTriangles(i);
	CEdge e(a.p0, a.p1);
	CEdge e1(a.p1, a.p2);
	CEdge e2(a.p2, a.p0);
	m_allListCEdgeBorder.push_back(e);
	m_allListCEdgeBorder.push_back(e1);
	m_allListCEdgeBorder.push_back(e2);
	m_CTrianglesData.push_back(a);
	do
	{
		ss >> num>> a.mp0 >> a.mp1 >> a.mp2;
		if (num == NULL)
		{
			break;
		}
		i++;
		a.p0 = m_SortMapPoint[a.mp0];
		m_SortMapPoint[a.mp0].AddTriangles(i);
		a.p1 = m_SortMapPoint[a.mp1];
		m_SortMapPoint[a.mp1].AddTriangles(i);
		a.p2 = m_SortMapPoint[a.mp2];
		m_SortMapPoint[a.mp2].AddTriangles(i);
		CEdge e(a.p0, a.p1);
		CEdge e1(a.p1, a.p2);
		CEdge e2(a.p2, a.p0);
		m_allListCEdgeBorder.push_back(e);
		m_allListCEdgeBorder.push_back(e1);
		m_allListCEdgeBorder.push_back(e2);
		m_CTrianglesData.push_back(a);

	} while (1);

	

	return true;
}

//功能函数
//读取ASCLL码STL文件
bool FileOption::ReadAscllStlFile(const char * cfilename)
{
	string title;
	string headStr;
	string SecondStr;
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
	ifstream in(cfilename);
	//in.get();
	//getline(in, title);
	getline(in, headStr);
	getline(in, SecondStr);
	if (headStr.empty())
		return false;
	int noempty = 0;
	while (SecondStr[noempty] == ' ')
		noempty++;

	if ((headStr[0] == 's') && (SecondStr[noempty] == 'f'))
	{
		std::cout << "ASCII File." << std::endl;
		ReadAscllStl(buffer);
	}
	else
	{
		std::cout << "Binary File." << std::endl;
		ReadBinary(buffer);
	}
	ios::sync_with_stdio(true);
	free(buffer);
	return true;
}

bool FileOption::ReadAscllStl(const char * buffer)
{
	float x, y, z;
	int i, j;
	j = 0;
	std::pair<std::map<MyPoint, MyPoint>::iterator, bool> ret;
	CTriangles a;
	MyPoint b;
	string name, useless;
	stringstream ss(buffer);
	ss.get();
	getline(ss, useless);
	do
	{
		ss >> useless;
		if (useless != "facet")
			break;
		getline(ss, useless);
		getline(ss, useless);
		for (i = 0; i < 3; i++)
		{
			ss >> useless >> x >> y >> z;

			//存面片数据
			if (i == 0)
			{

				a.p0.x = x;
				a.p0.y = y;
				a.p0.z = z;
				
				
			}
			else 	if (i == 1)
			{

				a.p1.x = x;
				a.p1.y = y;
				a.p1.z = z;
			
			}
			else 	if (i == 2)
			{

				a.p2.x = x;
				a.p2.y = y;
				a.p2.z = z;
				
			}
			b.x = x;
			b.y = y;
			b.z = z;
			//存节点数据
			//判断map容器中是否已经存在现在要存入的数据
			//pointlist1.insert(std::pair<mypoint, int>(b, 0));	//获取map.insert的返回值
			b.m_TrianglesList.push_back(j);
			//pointList.push_back(p0);
			ret = m_MapPoint.insert(std::pair<MyPoint, MyPoint>(b, b));
			if (ret.second == false)
			{
				map<MyPoint, MyPoint>::iterator it = m_MapPoint.find(b);
				it->second.AddTriangles(j);

			}
			b.m_TrianglesList.clear();

			//cout << pointlist.begin()->first.x << endl;
		}
		CEdge e(a.p0, a.p1);
		CEdge e1(a.p1, a.p2);
		CEdge e2(a.p2, a.p0);
		m_allListCEdgeBorder.push_back(e);
		m_allListCEdgeBorder.push_back(e1);
		m_allListCEdgeBorder.push_back(e2);
		m_CTrianglesData.push_back(a);
		j++;
		// 存一个面片的数据

		getline(ss, useless);
		getline(ss, useless);
		getline(ss, useless);
	} while (1);
	i = 0;
	std::cout <<"边的数量：" <<m_allListCEdgeBorder.size() << std::endl;
	i = 0;
	map<MyPoint, int> m_mapPoint;
	for (map<MyPoint, MyPoint>::iterator it = m_MapPoint.begin(); it != m_MapPoint.end(); it++)
	{
		m_SortMapPoint.insert(pair<int, MyPoint>(i, it->second));
		m_mapPoint.insert(pair<MyPoint, int>(it->second, i));
		i++;
	}
	map<MyPoint, int>::iterator v;
	for (auto it = m_CTrianglesData.begin(); it != m_CTrianglesData.end(); it++) 
	{
		v = m_mapPoint.find(it->p0);
		it->mp0 = v->second;
		v = m_mapPoint.find(it->p1);
		it->mp1 = v->second;
		v = m_mapPoint.find(it->p2);
		it->mp2 = v->second;
	}
	
	
	return true;
}

void FileOption::Bin2ToStl()
{
}

//二进制stl读取
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
	map<MyPoint, int> m_mapPoint;
	for (map<MyPoint, MyPoint>::iterator it = m_MapPoint.begin(); it != m_MapPoint.end(); it++)
	{
		m_SortMapPoint.insert(pair<int, MyPoint>(i, it->second));
		m_mapPoint.insert(pair<MyPoint, int>(it->second, i));
		i++;
	}
	map<MyPoint, int>::iterator v;
	for (auto it = m_CTrianglesData.begin(); it != m_CTrianglesData.end(); it++)
	{
		v = m_mapPoint.find(it->p0);
		it->mp0 = v->second;
		v = m_mapPoint.find(it->p1);
		it->mp1 = v->second;
		v = m_mapPoint.find(it->p2);
		it->mp2 = v->second;
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
//另存为ply格式文件
void FileOption::SavePly(const char * cfilename)
{
	map<MyPoint, int>pointlist;
	map<MyPoint, int>pointlist1;
	int i = 0;
	for (vector<CTriangles>::iterator itr = m_CTrianglesData.begin(); itr != m_CTrianglesData.end(); itr++)
	{
		MyPoint mypoint;
		mypoint.x = itr->p0.x;
		mypoint.y = itr->p0.y;
		mypoint.z = itr->p0.z;
		pointlist.insert(std::pair<MyPoint, int>(mypoint, i));
		mypoint.x = itr->p1.x;
		mypoint.y = itr->p1.y;
		mypoint.z = itr->p1.z;
		pointlist.insert(std::pair<MyPoint, int>(mypoint, i));
		mypoint.x = itr->p2.x;
		mypoint.y = itr->p2.y;
		mypoint.z = itr->p2.z;
		pointlist.insert(std::pair<MyPoint, int>(mypoint, i));

	}
	for (map<MyPoint, int>::iterator itr = pointlist.begin(); itr != pointlist.end(); itr++)
	{
		pointlist1.insert(std::pair<MyPoint, int>(itr->first, i));
		i++;
	}
	map<MyPoint, int>::iterator v;
	for (vector<CTriangles>::iterator itr = m_CTrianglesData.begin(); itr != m_CTrianglesData.end(); itr++)
	{
		MyPoint findpoint;
		findpoint.x = itr->p0.x;;
		findpoint.y = itr->p0.y;
		findpoint.z = itr->p0.z;
		v = pointlist1.find(findpoint);
		itr->mp0 = v->second;
		//
		findpoint.x = itr->p1.x;
		findpoint.y = itr->p1.y;
		findpoint.z = itr->p1.z;
		v = pointlist1.find(findpoint);
		itr->mp1 = v->second;
		//
		findpoint.x = itr->p2.x;
		findpoint.y = itr->p2.y;
		findpoint.z = itr->p2.z;
		v = pointlist1.find(findpoint);
		itr->mp2 = v->second;
	}
	//
	//string fileName = cfilename;
	ofstream of(cfilename);
	of.precision(std::numeric_limits<double>::digits10);
	//ofstream OpenFile("D:\\vs2017projects\\Task2\\testmap.ply");
	if (of.fail())
	{
		std::cout << "打开文件错误!" << std::endl;
	}
	of << "ply" << std::endl;
	of << "format ascii 1.0" << std::endl;
	of << "comment generated by platoply" << std::endl;
	of << "element vertex " << pointlist1.size() << std::endl;
	of << "property float32 x" << std::endl;
	of << "property float32 y" << std::endl;
	of << "property float32 z" << std::endl;
	of << "element face " << m_CTrianglesData.size() << std::endl;
	of << "property list uint8 int32 vertex_indices" << std::endl;
	of << "end_header" << std::endl;
	for (map<MyPoint, int>::iterator itr = pointlist1.begin(); itr != pointlist1.end(); itr++)
	{
		of << " " << itr->first.x << " " << itr->first.y << " " << itr->first.z << std::endl;
	}
	for (vector<CTriangles>::iterator itr = m_CTrianglesData.begin(); itr != m_CTrianglesData.end(); itr++)
	{
		of << 3 << " " << itr->mp0 << " " << itr->mp1 << " " << itr->mp2 << std::endl;
	}
}
//另存为stl格式文件
void FileOption::SaveAsStl(const char * cfilename)
{
	int i = 0;
	for (vector<CTriangles>::iterator  it = m_CTrianglesData.begin(); it != m_CTrianglesData.end(); it++)
	{
		Vector3 pt0(it->p0.x, it->p0.y, it->p0.z ), pt1(it->p1.x, it->p1.y, it->p1.z), pt2(it->p2.x, it->p2.y, it->p2.z);
		//计算该面的法向量
		Vector3 m, n, q;
		m = pt1 - pt0;
		n = pt2 - pt1;
		//计算两个向量的叉乘
		q = crossProduct(m, n);
		normal.insert(std::pair<int, Vector3>(i, q));
		i++;
	}
	std::ofstream fileout(cfilename);
	if (fileout.is_open())
	{
		int i = 0;
		fileout << "solid STL generated by MeshLab\n";
		for (vector<CTriangles>::iterator it = m_CTrianglesData.begin(); it != m_CTrianglesData.end(); it++)
		{
			fileout << "  facet normal ";
			fileout << normal[i].x << " " << normal[i].y << " " << normal[i].z << "\n";
			fileout << "    outer loop\n";
			fileout << "      vertex  " << it->p0.x << " " << it->p0.y<< " " << it->p0.z << std::endl;
			fileout << "      vertex  " << it->p1.x << " " << it->p1.y << " " << it->p1.z << std::endl;
			fileout << "      vertex  " << it->p2.x << " " << it->p2.y << " " << it->p2.z << std::endl;
			fileout << "    endloop\n";
			fileout << "    endfact\n";
			i++;
		}
		fileout.close();
	}
}



