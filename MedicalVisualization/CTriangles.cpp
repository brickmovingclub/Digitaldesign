#include "stdafx.h"
#include "CTriangles.h"

CTriangles::CTriangles()
{
}

CTriangles::CTriangles(MyPoint p0, MyPoint p1, MyPoint p2)
{
	this->p0 = p0;
	this->p1 = p1;
	this->p2 = p2;
}

CTriangles::~CTriangles()
{

}
