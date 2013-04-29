
/**********************************************
/***        Back To Rainbows
/***         
/***      By Angélique Lesage for LD26 contest
/***
/***            point.cpp
/**********************************************/

#include "Point.hpp"
#include "Enum.hpp"

Point::Point(){}

Point::Point(float x, float y)
{
	point = IMG_Load("Pictures/item.png");
	offset_x = pos[X] = x;
	offset_y = pos[Y] = y;

	clip.h = point->h;
    clip.w = point->w / 21;
    clip.y =0;
    clip.x = 0;

	velocity_y = 0;
	speed = 20;

	alpha = 255;

	collected = false;
	play = false;
}


Point::~Point() { SDL_FreeSurface(point); }



 /*** Setters ***/

void	Point::setVelocityY(float v) { velocity_y += v; }
void	Point::setPlayed(bool p)	 { play = p;}


   /*** Getter ***/

float   Point::getX()			{ return offset_x;  }
float   Point::getY()			{ return offset_y;  }
float	Point::getSpeed()		{ return speed;     }
float	Point::getVelocityY()	{ return velocity_y;}
bool	Point::getCollected()	{ return collected; }
bool	Point::played()			{ return play;      }

/*** Other ***/

void    Point::move()
{
	offset_y -= velocity_y;
	speed	+=	15;
	velocity_y = speed / FRAME_PER_SC;
	SDL_SetAlpha(point, SDL_SRCALPHA, alpha);
	alpha -= 15;
	if(alpha < 0)
	{
		alpha = 0;
		collected = true;
	}
}

void    Point::display(SDL_Surface *screen, float cam_x, float cam_y)
{
	SDL_Rect r_pos;
	r_pos.x = offset_x - cam_x;
	r_pos.y = offset_y - cam_y;

	SDL_BlitSurface(point, &clip, screen, &r_pos);

	(clip.x == (point->w - clip.w)) ? clip.x = 0 : clip.x += clip.w;
}

bool	Point::onObject(float x, float y)
{
	if((x > pos[X] && x < pos[X] + 70) || (y > pos[Y] && y < pos[Y] + 70))
		return true;
	else
		return false;
}