#pragma once
#include "MyPoint.h"
#include <iostream>

using namespace std;
class CEdge
{
public:

	CEdge();
	CEdge(MyPoint startNode, MyPoint endNode);
	~CEdge();
	MyPoint startNode;
	MyPoint endNode;
	// 判断某一个点是否在这条边中
	bool isIn = 0;
	// 边的长度
	double len;
	// 边所在的三角面片的信息
	int surfaceIndex;
	// 存储面的信息
	int flag = 0;
	int index = 0;
	void ToString()
	{
		std::cout << "当前边： " << std::endl;
		std::cout << " " << startNode.x << " " << startNode.y << " " << startNode.z << std::endl;
		std::cout << " " << endNode.x << " " << endNode.y << " " << endNode.z << std::endl;
		std::cout << std::endl;

	}
	bool operator==(const CEdge& c1)
	{
		if ((startNode == c1.startNode&&endNode == c1.endNode) || (startNode == c1.endNode&&endNode == c1.startNode))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool isEqual(CEdge c1)
	{
		if (startNode == c1.startNode&&endNode == c1.endNode)
		{
			return true;
		}
		else
			return false;
	}

};

