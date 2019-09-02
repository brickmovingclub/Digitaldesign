#pragma once
#include "MyPoint.h"
#include "CEdge.h"
#include <vector>

// ��Ƭ��Ϣ
class CTriangles
{
public:
	
	MyPoint p0;
	MyPoint p1;
	MyPoint p2;
	// �ߵ���Ϣ
	CEdge edge1;
	CEdge edge2;
	CEdge edge3;
	//���λ��
	int mp0, mp1, mp2;
	// ������Ƭ������������ 1 ��ʾ�۽ǣ� 0��ʾ���
	vector<double>list;

	int angle = 0;


	// �жϵ��Ƿ���������Ƭ��,???????ƽ�����ά�кβ�ͬ
	void ToString()
	{
		std::cout << "��ǰ������Ƭ " << std::endl;
		std::cout << " " << p0.x << " " << p0.y << " " << p0.z << std::endl;
		std::cout << " " << p1.x << " " << p1.y << " " << p1.z << std::endl;
		std::cout << " " << p2.x << " " << p2.y << " " << p2.z << std::endl;
		std::cout << std::endl;
	}
	CTriangles();
	CTriangles(MyPoint p0, MyPoint p1, MyPoint p2);
	~CTriangles();

	// ����������Ƭ�ķ�����
	//void GetAngle();
	//void Normal();
};

