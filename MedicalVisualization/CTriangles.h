#pragma once
#include "MyPoint.h"
#include "CEdge.h"
#include <vector>

// 面片信息
class CTriangles
{
public:
	
	MyPoint p0;
	MyPoint p1;
	MyPoint p2;
	// 边的信息
	CEdge edge1;
	CEdge edge2;
	CEdge edge3;
	//点的位置
	int mp0, mp1, mp2;
	// 三角面片的三角形性质 1 表示钝角， 0表示锐角
	vector<double>list;

	int angle = 0;


	// 判断点是否在三角面片中,???????平面和三维有何不同
	void ToString()
	{
		std::cout << "当前三角面片 " << std::endl;
		std::cout << " " << p0.x << " " << p0.y << " " << p0.z << std::endl;
		std::cout << " " << p1.x << " " << p1.y << " " << p1.z << std::endl;
		std::cout << " " << p2.x << " " << p2.y << " " << p2.z << std::endl;
		std::cout << std::endl;
	}
	CTriangles();
	CTriangles(MyPoint p0, MyPoint p1, MyPoint p2);
	~CTriangles();

	// 计算三角面片的法向量
	//void GetAngle();
	//void Normal();
};

