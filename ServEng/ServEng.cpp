#include "pch.h"
#include "ServEng.h"

// RANDiT ***************************

dll::RANDiT::RANDiT()
{
	sq = new std::seed_seq{ rd(),rd(), rd(), rd(), rd(), rd(), rd() };
	twister = new std::mt19937(*sq);
}
dll::RANDiT::~RANDiT()
{
	if (sq)delete sq;
	if (twister)delete twister;
}

int dll::RANDiT::operator() (int min, int max)
{
	std::uniform_int_distribution distrib{ min,max };

	return distrib(*twister);
}

/////////////////////////////////////

//PROTON ***************************

dll::PROTON::PROTON(float _init_x, float _init_y, float _init_width, float _init_height)
{
	start.x = _init_x;
	start.y = _init_y;
	width = _init_width;
	height = _init_height;

	end.x = start.x + width;
	end.y = start.y + height;

	center.x = start.x + width / 2.0f;
	center.y = start.y + height / 2.0f;
}
dll::PROTON::PROTON(float _init_x, float _init_y, float _init_width, float _init_height, PROTON*& heap_pointer)
{
	mPtr = new PROTON(_init_x, _init_y, _init_width, _init_height);
	heap_pointer = mPtr;
}

dll::PROTON::~PROTON()
{
	if (mPtr)delete mPtr;
}

dll::PROTON* dll::PROTON::GetThis() const
{
	return mPtr;
}
float dll::PROTON::GetWidth() const
{
	return width;
}
float dll::PROTON::GetHeight() const
{
	return height;
}

void dll::PROTON::SetEdges()
{
	end.x = start.x + width;
	end.y = start.y + height;

	center.x = start.x + width / 2.0f;
	center.y = start.y + height / 2.0f;
}
void dll::PROTON::SetWidth(float _new_width)
{
	width = _new_width;
	SetEdges();
}
void dll::PROTON::SetHeight(float _new_height)
{
	height = _new_height;
	SetEdges();
}
void dll::PROTON::SetNewDims(float _new_width, float _new_height)
{
	width = _new_width;
	height = _new_height;
	SetEdges();
}

/////////////////////////////////////