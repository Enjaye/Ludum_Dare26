/**********************************************
/***        Back To Rainbows
/***         
/***      By Angélique Lesage for LD26 contest
/***
/***            camera.cpp
/**********************************************/

#include "Camera.hpp"
#include "Enum.hpp"

Camera::Camera()
{
	camera.x = camera.y = 0;
	camera.h = SCREEN_H;
	camera.w = SCREEN_W;
}


Camera::~Camera(){}

SDL_Rect*	Camera::getCamera()	{  return  &camera;	 }
float		Camera::getX()		{  return  camera.x; }
float		Camera::getY()		{  return  camera.y; }
float		Camera::getW()		{  return  camera.w; }
float		Camera::getH()      {  return  camera.h; }

void		Camera::setCenter(float sp_x, float sp_y, float lvlW, float lvlH)
{
	
	camera.x = (sp_x + 19) - SCREEN_W / 2;
	camera.y = (sp_y + 30) - SCREEN_H / 2;

	if( camera.x < 0 )
    {
        camera.x = 0;
    }
    if( camera.y < 0 )
    {
        camera.y = 0;
    }
    if( camera.x > lvlW - camera.w )
    {
        camera.x = lvlW - camera.w;
    }
    if( camera.y > lvlH - camera.h )
    {
        camera.y = lvlH - camera.h;
    }
}

void		Camera::setX( float nx)	{  camera.x = nx; }
void		Camera::setY( float ny) {  camera.y = ny; }