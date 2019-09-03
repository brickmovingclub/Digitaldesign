#include "stdafx.h"
#include "MyPoint.h"


MyPoint::MyPoint(float a1, float b1, float c1)
{
	this->x = a1;
	this->y = b1;
	this->z = c1;
}


MyPoint::~MyPoint()
{
}

void MyPoint::AddTriangles(int i)
{
	m_TrianglesList.push_back(i);
}


MyPoint::MyPoint()
{
}
