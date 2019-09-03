#pragma once
#include "CTriangles.h"
class MyPoint
{
public:
	MyPoint();
	MyPoint(float a1, float b1, float c1);
	~MyPoint();
	//Ьиад

	float x, y, z, R, G, B;
	
	bool operator< (const MyPoint &a)const
	{
		return (x < a.x) || ((x == a.x) && (y < a.y)) || ((x == a.x) && (y == a.y) && (z < a.z));
	}
	bool operator== (const MyPoint &a)const
	{

		if ((a.x==x)&&(a.y==y)&&(a.z==z))
		{
			return true;
		}
		else
			return false;

	}
};

