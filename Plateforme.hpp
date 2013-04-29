/**********************************************
/***        Back To Rainbows
/***         
/***      By Angélique Lesage for LD26 contest
/***
/***            plateforme.hpp
/**********************************************/

#ifndef PLATEFORME_HPP
#define PLATEFORME_HPP

#include <SDL/SDL_image.h>
#include <SDL/SDL.h>

class Plateforme
{

public:

	Plateforme();
	Plateforme(int nb_color, float x, float y);
	~Plateforme();

	enum Color
	{
		RED1, RED2, RED3,
		YELLOW1, YELLOW2, YELLOW3,
		GREEN1, GREEN2, GREEN3,
		BLUE1, BLUE2, BLUE3,
		INDIGO1, INDIGO2, INDIGO3,
		PURPLE1, PURPLE2, PURPLE3,
		PINK1, PINK2, PINK3
	};

	void				setActive(bool a);
	void				display(SDL_Surface *screen, float cam_x, float cam_y);

	Plateforme::Color	getColor();
	float				getPosX();
	float				getPosY();
	bool				onObject(float x, float y);

protected:

	SDL_Surface			*plateforme;
	SDL_Rect			clipping;
	float				pos[2];
	Plateforme::Color	color;
	bool				active;
	int					num_couleur;


};

#endif