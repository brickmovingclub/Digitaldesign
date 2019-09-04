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
	// �ж�ĳһ�����Ƿ�����������
	bool isIn = 0;
	// �ߵĳ���
	double len;
	// �����ڵ�������Ƭ����Ϣ
	int surfaceIndex;
	// �洢�����Ϣ
	int flag = 0;
	int index = 0;
	void ToString()
	{
		std::cout << "��ǰ�ߣ� " << std::endl;
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

