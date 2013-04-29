/**********************************************
/***        Back To Rainbows
/***         
/***      By Angélique Lesage for LD26 contest
/***
/***            point.hpp
/**********************************************/

#ifndef POINT_HPP
#define POINT_HPP

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Timer.hpp"

class Point
{
protected :

	SDL_Surface		*point;
	SDL_Rect		clip;

	float			pos[2];

	Timer			anim;

	int				alpha;

	float			speed;
	float			velocity_y;
	float			offset_x, offset_y;

	bool			collected, play;

public :

	Point();
	Point(float x, float y);
	~Point();

	 /*** Setters ***/

	void	setVelocityY(float v);
	void	setPlayed(bool p);

    /*** Getter ***/

    float   getX();
    float   getY();
	float	getSpeed();
	float	getVelocityY();
	bool	getCollected();
	bool	played();

    /*** Other ***/

    void    move();
    void    display(SDL_Surface *screen, float cam_x, float cam_y);
	bool	onObject(float x, float y);

};


#endif