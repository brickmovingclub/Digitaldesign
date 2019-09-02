#include "stdafx.h"
#include "CEdge.h"



CEdge::CEdge()
{
}

CEdge::CEdge(MyPoint startNode, MyPoint endNode)
{
	this->startNode = startNode;
	this->endNode = endNode;
}


CEdge::~CEdge()
{
}
