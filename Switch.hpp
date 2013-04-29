/**********************************************
/***        Back To Rainbows
/***         
/***      By Angélique Lesage for LD26 contest
/***
/***            switch.hpp
/**********************************************/

#ifndef SWITCH_HPP
#define SWITCH_HPP

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

class Switch
{
public:

	enum S_Color
	{
		RED,
		YELLOW,
		GREEN,
		BLUE,
		INDIGO,
		PURPLE,
		PINK,
	};

	Switch();
	Switch(Switch::S_Color c, float x, float y);
	~Switch();

	void				setState(bool s);
	void				setFrame(int i);
	void				setColide(bool c);
	void				setPlayed(bool p);
	
	Switch::S_Color		getColor();
	float				getPosX();
	float				getPosY();
	float				getYColide();
	bool				getState();
	bool				getColide();
	bool				played();
	int					getFrame();

	void				display(SDL_Surface *screen, float cam_x, float cam_y);
	bool				onObject(float x, float y);


protected:

	SDL_Surface		*s_switch;
	SDL_Rect		clipping;

	Switch::S_Color	color;

	float			pos[2];
	float			y_colide;

	bool			state, colide, play;
	int				frame;

};


#endif