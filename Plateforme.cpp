/**********************************************
/***        Back To Rainbows
/***         
/***      By Angélique Lesage for LD26 contest
/***
/***            Plateforme.cpp
/**********************************************/

#include "Plateforme.hpp"
#include "Enum.hpp"

#include <time.h>

Plateforme::Plateforme(){}

Plateforme::Plateforme(int nb_color, float x, float y)
{

	plateforme = IMG_Load("Pictures/plateforme.png");

	clipping.x = clipping.y = 0;
	clipping.h = plateforme->h;
	clipping.w = 70;

	/*** à vérifier pas sûre du tout ***/
	int i_color = rand()%(nb_color*3) + 1;

	switch(i_color)
	{
	case 1 : color = RED1;	 		break;
	case 2 : color = RED2;	 		break;
	case 3 : color = RED3;			break;
	case 4 : color = YELLOW1;		break;
	case 5 : color = YELLOW2;		break;
	case 6 : color = YELLOW3;	    break;
	case 7 : color = GREEN1;	    break;
	case 8 : color = GREEN2;	    break;
	case 9 : color = GREEN3;	    break;
	case 10: color = BLUE1;	    	break;
	case 11: color = BLUE2;	    	break;
	case 12: color = BLUE3;	    	break;
	case 13: color = INDIGO1;	    break;
	case 14: color = INDIGO2;	    break;
	case 15: color = INDIGO3;	    break;
	case 16: color = PURPLE1;	    break;
	case 17: color = PURPLE2;	    break;
	case 18: color = PURPLE3;	    break;
	case 19: color = PINK1;	    	break;
	case 20: color = PINK2;	    	break;
	case 21: color = PINK3;	    	break;

	}


	pos[X] = x; pos[Y] = y;

	active = false;
}

Plateforme::~Plateforme(){   SDL_FreeSurface(plateforme);	}

Plateforme::Color   Plateforme::getColor()	{  return color;  }
float				Plateforme::getPosX()   {  return pos[X]; }
float				Plateforme::getPosY()	{  return pos[Y]; }

void				Plateforme::setActive(bool a)
{
	active = a;
	switch(color)
	{
	case RED1:		clipping.x = 70;	  break;
	case RED2:		clipping.x = 70*2;    break;
	case RED3:		clipping.x = 70*3;	  break;
	case YELLOW1:	clipping.x = 70*4;	  break;
	case YELLOW2:	clipping.x = 70*5;	  break;
	case YELLOW3:	clipping.x = 70*6;    break;
	case GREEN1:	clipping.x = 70*7;    break;
	case GREEN2:	clipping.x = 70*8;    break;
	case GREEN3:	clipping.x = 70*9;    break;
	case BLUE1:	    clipping.x = 70*10;	  break;
	case BLUE2:	    clipping.x = 70*11;	  break;
	case BLUE3:	    clipping.x = 70*12;	  break;
	case INDIGO1:	clipping.x = 70*13;   break;
	case INDIGO2:	clipping.x = 70*14;   break;
	case INDIGO3:	clipping.x = 70*15;   break;
	case PURPLE1:	clipping.x = 70*16;   break;
	case PURPLE2:	clipping.x = 70*17;   break;
	case PURPLE3:	clipping.x = 70*18;   break;
	case PINK1:	    clipping.x = 70*19;	  break;
	case PINK2:	    clipping.x = 70*20;	  break;
	case PINK3:	    clipping.x = 70*21;	  break;
	}
}

void				Plateforme::display(SDL_Surface *screen, float cam_x, float cam_y)
{
	SDL_Rect r_pos;

	r_pos.x = pos[X] - cam_x;
	r_pos.y = pos[Y] - cam_y;

	SDL_BlitSurface(plateforme, &clipping, screen, &r_pos);		

}

bool				Plateforme::onObject(float x, float y)
{
	if((x > pos[X] && x < pos[X] + 70) || (y > pos[Y] && y < pos[Y] + 70))
		return true;
	else
		return false;
}

