/**********************************************
/***        Back To Rainbows
/***         
/***      By Angélique Lesage for LD26 contest
/***
/***            Camera.cpp
/**********************************************/

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SDL/SDL.h>

class Camera
{
public:
	Camera();
	~Camera();

	SDL_Rect	*getCamera();
	float		getX();
	float		getY();
	float		getW();
	float		getH();

	void		setCenter(float sp_x, float sp_y, float lvlW, float lvlH);
	void		setX( float nx);
	void		setY( float ny);

private:
	SDL_Rect camera;
};



#endif