/**********************************************
/***        Back To Rainbows
/***         
/***      By Angélique Lesage for LD26 contest
/***
/***           square.hpp
/**********************************************/


#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <SDL/SDL.h>
#include "Timer.hpp"

class Square
{
protected:

    SDL_Surface     *s_sprite;
    SDL_Rect        c_sprite, camera;

	Timer			anim;

	int				frame, n_saut;
	int				lvlH, lvlW;

    float           pos[2];
	float			speed;
	float			velocity_x, velocity_y, velocity_s, gravity;
	float			offset_x, offset_y;
	float			jump_base;
	bool			jump, p_jump, fall;

public:

    Square();
    ~Square();

    /*** Setters ***/

    void    setPos(float x, float y);
	void	setSpeed(float s);
	void	setVelocityX(float v);
	void	setVelocityY(float v);
	void	setJump(bool j);
	void	pauseJump(bool j);
	void	setJumpBase();
	void	setJumpBase(float base);
	void	setFall(bool f);
	void	resetJump();
	void    resetJump(float v);
	void	setNJump(int n);
	void	setLvlH(int h);
	void	setLvlW(int w);

    /*** Getter ***/

    float   getX();
    float   getY();
	float	getSpeed();
	float	getH();
	float	getW();
	float	getVelocityX();
	bool	jumping();
	int		getNJump();

    /*** Other ***/

    void    move();
    void    display(SDL_Surface *screen, float cam_x, float cam_y);

};

#endif // SQUARE_HPP
