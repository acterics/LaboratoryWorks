#include "VParabola.h"
#include "VPoint.h"

/*
	Constructors
*/

VParabola::VParabola()
{
	site	= nullptr;
	isLeaf	= false;
	cEvent	= nullptr;
	edge	= nullptr;
	parent	= nullptr;
}

VParabola::VParabola(VPoint * s)
{
	site	= s; 
	isLeaf	= true;
	cEvent	= nullptr;
	edge	= nullptr;
	parent	= nullptr;
}

VParabola::~VParabola()
{
}

void VParabola::deleteParabola()
{
	
	if (!this)
		return;
	if(_left)
		return _left->deleteParabola();
	if(_right)
		return _right->deleteParabola();
	delete this;
}

/*
	Tree operations (described in the header file)
*/

VParabola * VParabola::GetLeft			(VParabola * p)
{
	return GetLeftChild(GetLeftParent(p));
}


VParabola * VParabola::GetRight			(VParabola * p)
{
	return GetRightChild(GetRightParent(p));
}

VParabola * VParabola::GetLeftParent	(VParabola * p)
{
	VParabola * par		= p->parent;
	VParabola * pLast	= p;
	while(par->Left() == pLast) 
	{ 
		if(!par->parent) return 0;
		pLast = par; 
		par = par->parent; 
	}
	return par;
}

VParabola * VParabola::GetRightParent	(VParabola * p)
{
	VParabola * par		= p->parent;
	VParabola * pLast	= p;
	while(par->Right() == pLast) 
	{ 
		if(!par->parent) return 0;
		pLast = par; par = par->parent; 
	}
	return par;
}

VParabola * VParabola::GetLeftChild		(VParabola * p)
{
	if(!p) return 0;
	VParabola * par = p->Left();
	while(!par->isLeaf) par = par->Right();
	return par;
}

VParabola * VParabola::GetRightChild	(VParabola * p)
{
	if(!p) return 0;
	VParabola * par = p->Right();
	while(!par->isLeaf) par = par->Left();
	return par;
}
