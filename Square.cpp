/**********************************************
/***        Back To Rainbows
/***         
/***      By Angélique Lesage for LD26 contest
/***
/***            square.cpp
/**********************************************/

#include "Square.hpp"
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <iostream>
#include <stdio.h>

#include "Enum.hpp"

Square::Square()
{
    s_sprite = IMG_Load("Pictures/sprite.png");
    c_sprite.h = s_sprite->h;
    c_sprite.w = s_sprite->w / 21;
    c_sprite.y =0;
    c_sprite.x = 0;

    pos[X] = 100;
    pos[Y] = SCREEN_H - 200;

	offset_x = 100;
	offset_y = 400;

	velocity_x = 0;
	velocity_y = -30;
	velocity_s = -30;
	gravity = 2;
	speed = 350;

	n_saut = 0;

	jump = false;
	p_jump = false;
	fall = false;
}

Square::~Square()
{
    SDL_FreeSurface(s_sprite);
}

/*** Setters ***/

void    Square::setPos(float x, float y)
{
	offset_x = x;
	offset_y = y;
}

void	Square::setSpeed(float s)
{
	speed = s;
	
	/*if(s > 1.0)
		s = 1.0;
	else if(s < 0.1)
		s = 0.1;*/
}

void	Square::setVelocityX(float v){	velocity_x += v;}
void	Square::setVelocityY(float v){	velocity_y = v;}

void	Square::setJump(bool j)
{
	jump = j;
}
void	Square::pauseJump(bool j)	{  p_jump = j; }

void	Square::setJumpBase()			{   if(!jump) jump_base = offset_y;	}
void	Square::setJumpBase(float base)	{   if(!jump) jump_base = base;	}
void	Square::resetJump()
{
	fall = false;
	jump = false;
	velocity_y = velocity_s;
}
void	Square::resetJump(float v)
{
	fall = false;
	jump = false;
	velocity_y = v;
	n_saut = 0;
}

void	Square::setFall(bool f)		{ fall = f;}
void	Square::setNJump(int n)		{ n_saut = n; }
void	Square::setLvlH(int h)		{ lvlH = h; }
void	Square::setLvlW(int w)		{ lvlW = w; }

/*** Getter ***/

float   Square::getX()  {   return offset_x;  }
float   Square::getY()  {   return offset_y;  }
float	Square::getW()	{   return c_sprite.w; }
float	Square::getH()  {   return c_sprite.h; }

float	Square::getSpeed()	{	return speed;	}
float	Square::getVelocityX()	{  return velocity_x;  }
bool	Square::jumping()	{   return jump;	}
int		Square::getNJump()	{   return n_saut;  }


/*** Other ***/


void	Square::move()
{
	offset_x += velocity_x;

	if( offset_x + c_sprite.w > lvlW ) 
        offset_x -= velocity_x;
	else if(offset_x < 0)
		offset_x = 0;

	if(jump)
	{
		offset_y += velocity_y;

		velocity_y += gravity;
		
		if(offset_y < 0)
		{
			velocity_y = 0;
			offset_y = 0;
		}

		if(velocity_y >= 0)
		{
			fall = true;
			jump = false;
		}
		
	}

	else if(fall)
	{
		offset_y += velocity_y;

		velocity_y += gravity;

		if(offset_y >= lvlH - c_sprite.h)
		{
			fall = false;
			velocity_y = velocity_s;
			offset_y = lvlH - c_sprite.h;
			n_saut = 0;
		}
	}
}

void    Square::display(SDL_Surface *screen, float cam_x, float cam_y)
{
	SDL_Rect    r_pos;

    r_pos.x = offset_x - cam_x;
    r_pos.y = offset_y - cam_y;

    SDL_BlitSurface(s_sprite, &c_sprite, screen, &r_pos);

    (c_sprite.x == (s_sprite->w - c_sprite.w)) ? c_sprite.x = 0 : c_sprite.x += c_sprite.w;
}
