/**********************************************
/***        Back To Rainbows
/***         
/***      By Angélique Lesage for LD26 contest
/***
/***            switch.c^pp
/**********************************************/

#include "Switch.hpp"
#include "Enum.hpp"



Switch::Switch(){}
Switch::Switch(Switch::S_Color c, float x, float y)
{
	state = false;
	play = false;
	frame = 0;

	pos[X] = x;
	pos[Y] = y;

	color = c;

	s_switch = IMG_Load("Pictures/switch.png");

	clipping.h = s_switch->h / 7;
	clipping.w = s_switch->w / 5;

	switch(color)
	{
	case RED:		clipping.y = 0;					break;
	case YELLOW:	clipping.y = clipping.h * 1;	break;
	case GREEN:		clipping.y = clipping.h * 2;	break;
	case BLUE:		clipping.y = clipping.h * 3;	break;
	case INDIGO:	clipping.y = clipping.h * 4;	break;
	case PURPLE:	clipping.y = clipping.h * 5;	break;
	case PINK:		clipping.y = clipping.h * 6;	break;
	}

	y_colide = pos[Y];
}

Switch::~Switch()	{  SDL_FreeSurface(s_switch);	}


void				Switch::setState(bool s) {  state = s; }
void				Switch::setFrame(int i)
{  
	frame = i;

	switch(frame)
	{
	case 0:	y_colide = pos[Y];		break;
	case 1: y_colide = pos[Y] + 6;	break;
	case 2: y_colide = pos[Y] + 12; break;
	case 3: y_colide = pos[Y] + 18; break;
	case 4: y_colide = pos[Y] + 23; break;
	}

}
void				Switch::setColide(bool c){  colide = c;}
void				Switch::setPlayed(bool p){  play = p;  }

	
Switch::S_Color		Switch::getColor()	{ return color; }
float				Switch::getPosX()	{ return pos[X]; }
float				Switch::getPosY()	{ return pos[Y]; }
float				Switch::getYColide(){ return y_colide;}
bool				Switch::getState()	{ return state; }
bool				Switch::getColide() { return colide; }
bool				Switch::played()	{ return play;  }
int					Switch::getFrame()	{ return frame; }

void				Switch::display(SDL_Surface *screen, float cam_x, float cam_y)
{
	clipping.x = clipping.w * frame;

	SDL_Rect r_pos;
	r_pos.x = pos[X] - cam_x;
	r_pos.y = pos[Y] - cam_y;

	SDL_BlitSurface(s_switch, &clipping, screen, &r_pos);
}

bool				Switch::onObject(float x, float y)
{
	if((x > pos[X] && x < pos[X] + 70) || (y > pos[Y] && y < pos[Y] + 70))
		return true;
	else
		return false;
}
