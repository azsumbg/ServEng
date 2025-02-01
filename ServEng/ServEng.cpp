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

// BASE_OBJECT *********************

dll::BASE_OBJECT::BASE_OBJECT(uint16_t _what, float _wherex, float _wherey) :PROTON(_wherex, _wherey)
{
	type = _what;

	switch (type)
	{
	case fish1:
		SetNewDims(60.0f, 40.0f);
		dir = dirs::left;
		strenght = 5;
		max_frames = 19;
		frame_delay = 4;
		speed = 0.6f;
		break;

	case fish2:
		SetNewDims(65.0f, 33.0f);
		dir = dirs::left;
		strenght = 8;
		max_frames = 5;
		frame_delay = 14;
		speed = 0.7f;
		break;

	case fish3:
		SetNewDims(65.0f, 40.0f);
		dir = dirs::left;
		strenght = 10;
		max_frames = 11;
		frame_delay = 6;
		speed = 0.5f;
		break;

	case fish4:
		SetNewDims(59.0f, 45.0f);
		dir = dirs::left;
		strenght = 12;
		max_frames = 39;
		frame_delay = 2;
		speed = 0.4f;
		break;

	case fish5:
		SetNewDims(65.0f, 70.0f);
		dir = dirs::left;
		strenght = 15;
		max_frames = 7;
		frame_delay = 10;
		speed = 0.3f;
		break;

	case fish6:
		SetNewDims(75.0f, 65.0f);
		dir = dirs::left;
		strenght = 18;
		max_frames = 15;
		frame_delay = 5;
		speed = 0.4f;
		break;

	case fish7:
		SetNewDims(80.0f, 52.0f);
		dir = dirs::left;
		strenght = 20;
		max_frames = 3;
		frame_delay = 25;
		speed = 0.4f;
		break;

	case fish8:
		SetNewDims(85.0f, 45.0f);
		dir = dirs::left;
		strenght = 22;
		max_frames = 7;
		frame_delay = 10;
		speed = 0.3f;
		break;

	case fish9:
		SetNewDims(90.0f, 35.0f);
		dir = dirs::left;
		strenght = 25;
		max_frames = 7;
		frame_delay = 10;
		speed = 0.7f;
		break;

	case hero:
		SetNewDims(85.0f, 55.0f);
		dir = dirs::right;
		strenght = 10;
		max_frames = 24;
		frame_delay = 3;
		speed = 0.8f;
		break;

		/////////////////////////////////////////////

	case bubbles:
		SetNewDims(100.0f, 69.0f);
		dir = dirs::up;
		strenght = 0;
		max_frames = 39;
		frame_delay = 2;
		speed = 0.8f;
		break;

	case grass:
		SetNewDims(100.0f, 157.0f);
		dir = dirs::up;
		strenght = 0;
		max_frames = 5;
		frame_delay = 14;
		speed = 0.3f;
		break;

	case jelly1:
		SetNewDims(60.0f, 52.0f);
		dir = dirs::up;
		strenght = 0;
		max_frames = 46;
		frame_delay = 2;
		speed = 0.7f;
		break;

	case jelly2:
		SetNewDims(70.0f, 70.0f);
		dir = dirs::down;
		strenght = 0;
		max_frames = 4;
		frame_delay = 16;
		speed = 0.7f;
		break;
	}
}
void dll::BASE_OBJECT::SetPathInfo(float _ex, float _ey)
{
	move_sx = start.x;
	move_sy = start.y;
	move_ex = _ex;
	move_ey = _ey;

	hor_line = false;
	vert_line = false;

	if ((move_ex > move_sx && move_ex - (move_sx + width) == 0) || (move_ex < move_sx && move_sx - (move_ex + width) == 0)
		|| move_ex == move_sx)
	{
		vert_line = true;
		return;
	}
	if ((move_ey > move_sy && move_ey - (move_sx + height) == 0) || (move_ey < move_sy && move_sy - (move_ey + height) == 0)
		|| move_ey == move_sy)
	{
		hor_line = true;
		return;
	}
	
	slope = (move_ey - move_sy) / (move_ex / move_sx);
	intercept = move_sy - move_sx * slope;
}
int dll::BASE_OBJECT::GetFrame()
{
	--frame_delay;
	if (frame_delay <= 0)
	{
		switch (type)
		{
		case fish1:
			frame_delay = 4;
			break;

		case fish2:
			frame_delay = 14;
			break;

		case fish3:
			frame_delay = 6;
			break;

		case fish4:
			frame_delay = 2;
			break;

		case fish5:
			frame_delay = 10;
			break;

		case fish6:
			frame_delay = 5;
			break;

		case fish7:
			frame_delay = 25;
			break;

		case fish8:
			frame_delay = 10;
			break;

		case fish9:
			frame_delay = 10;
			break;

		case hero:
			frame_delay = 3;
			break;

			/////////////////////////////////////////////

		case bubbles:
			frame_delay = 2;
			break;

		case grass:
			speed = 0.3f;
			break;

		case jelly1:
			frame_delay = 2;
			break;

		case jelly2:
			frame_delay = 16;
			break;
		}

		++frame;
		if (frame > max_frames)frame = 0;
	}

	return frame;
}
uint16_t dll::BASE_OBJECT::GetType() const
{
	return type;
}

////////////////////////////////////




// FACTORY ****************************

SERVENG_API dll::BASE_OBJECT* dll::ObjectFactory(uint16_t what, float first_x, float first_y)
{
	dll::Object ret{ nullptr };

	if (what != hero && what != bubbles && what != grass && what != jelly1 && what != jelly2)
		ret = new EVILS(what, first_x, first_y);
	else if(what == hero)ret = new HERO(what, first_x, first_y);
	else if (what == bubbles || what == grass || what == jelly1 || what == jelly2)ret = new ASSETS(what, first_x, first_y);
	
	return ret;
}