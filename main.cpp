/**********************************************
/***        Back To Rainbows
/***         
/***      By Angélique Lesage for LD26 contest
/***
/***            main.cpp
/**********************************************/


#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <vector>
#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>

#include "Enum.hpp"
#include "Square.hpp"
#include "Timer.hpp"
#include "Plateforme.hpp"
#include "Switch.hpp"
#include "Point.hpp"
#include "Level.hpp"
#include "Camera.hpp"

using namespace std;

static SDL_Surface* screen, *source, *t_timeAttack, *t_help, *t_score;
static SDL_Event event;
static SDL_Color color = { 255, 255, 255 };
static SDL_Rect r_help, r_titre, r_play, r_timeAttack, r_quit, r_pause, r_reset, r_score;
static Mix_Chunk *jump, *s_switch, *item;
static Timer fps;
static TTF_Font *font_t = NULL, *font = NULL;

static	Square	square;
static	Level	gestionLvl;
static	Camera  camera;

static int alpha = 0, selection = 0, sub_selection = 0, timeattack = 0;

static	vector<Plateforme*> pf;
static	vector<Switch*>		sw;
static	vector<Point*>		pts;

static  bool	finish = false, win;
static  int		nb_interrupteur = 0, score = 0;

/*** Initialisation **/
void init()
{
	srand(time(NULL));

    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        exit(1);
    }

	SDL_WM_SetCaption("Back To Rainbows", NULL);
	 if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0)
    {
        if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) != 0)
        {
            if(Mix_OpenAudio(11025, MIX_DEFAULT_FORMAT, 1, 1024) == -1)
				Mix_GetError();
        }
    }
    Mix_AllocateChannels(10);

	if(TTF_Init() == -1)
	{
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}

    atexit(SDL_Quit);

    screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 16,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        exit(1);
    }

	cout << "Std cout works" <<endl;

	jump	 = Mix_LoadWAV("Sound/jump.wav");
	s_switch = Mix_LoadWAV("Sound/switch.wav");
	item	 = Mix_LoadWAV("Sound/item1.wav");

	Mix_Volume(1, MIX_MAX_VOLUME/2);

	font = TTF_OpenFont("neuropol.ttf", 50);
	font_t = TTF_OpenFont("neuropol.ttf", 60);

	r_score.x = 10;
	r_score.y = 10;

	r_timeAttack.x = 820;
	r_timeAttack.y = 10;
}

/*** Main Loop function **/
void handle_event()
{
	 if( event.type == SDL_KEYDOWN )
			{
				//mise à jour de la velocité
				switch( event.key.keysym.sym )
				{
					case SDLK_RIGHT:	square.setVelocityX (square.getSpeed() / FRAME_PER_SC);	 break;
					case SDLK_LEFT:		square.setVelocityX (-square.getSpeed() / FRAME_PER_SC); break;
					case SDLK_SPACE:
						if(square.getNJump() < 2)
						{
							square.setJumpBase();
							square.setVelocityY(-30);
							square.setJump(true);
							square.setNJump(square.getNJump() + 1);
							Mix_PlayChannel(1, jump, 0);
						}
					break;

					case SDLK_DOWN:		
						if(square.getY() + square.getH() < gestionLvl.getHeight())
							square.setPos(square.getX(), square.getY() + 1);
					break;
					
					case SDLK_r:
						   gestionLvl.LevelGen(7, SCREEN_W, SCREEN_W *5, SCREEN_H, SCREEN_H *5);

							pf  = gestionLvl.getPlateformes();
							sw  = gestionLvl.getSwitchs();
							pts = gestionLvl.getPoints();

							square.setPos(gestionLvl.getStartX(), gestionLvl.getStartY());
							square.setLvlH(gestionLvl.getHeight());
							square.setLvlW(gestionLvl.getWidth());
							finish = false;
						
					break;
					
					default: break;
				}
			}
			//si une touche est relachée
			else if( event.type == SDL_KEYUP )
			{
				//Mise à jour de la velocité
				switch( event.key.keysym.sym )
				{
					case SDLK_RIGHT:	square.setVelocityX (-square.getSpeed() / FRAME_PER_SC); break;
					case SDLK_LEFT:		square.setVelocityX (square.getSpeed() / FRAME_PER_SC); break;
					default: break;
				}
			}

}

void colide_switch()
{
	/**** Détection de colision interrupteur **/
		for(int i = 0; i < sw.size(); i++)
		{
			sw.at(i)->setColide(false);

			if((( square.getX() < sw.at(i)->getPosX() + 5 && ( square.getX() + square.getW() ) > sw.at(i)->getPosX() + 5) ||
				( square.getX() > sw.at(i)->getPosX() + 5 && ( square.getX() + square.getW() ) < sw.at(i)->getPosX() + 50 ) ||
				( square.getX() < ( sw.at(i)->getPosX() + 50 ) && ( square.getX() + square.getW() ) > sw.at(i)->getPosX() + 50 ) ) &&
				( square.getY() + square.getH() >= sw.at(i)->getYColide()) && (square.getY() < sw.at(i)->getYColide()))
			{
				square.setPos(square.getX(), (sw.at(i)->getYColide() - square.getH()));
				square.resetJump(0.0);
				sw.at(i)->setColide(true);
			}
			else if( square.getY() + square.getH() <  gestionLvl.getHeight())
			{
				square.setFall(true);
			}

			if(sw.at(i)->getColide())
			{
				if(sw.at(i)->getFrame() < 4)
				{
					sw.at(i)->setFrame(sw.at(i)->getFrame() + 1);
					square.setPos(square.getX(), (sw.at(i)->getYColide() - square.getH()));
				}
				else
				{
					sw.at(i)->setState(true);
					if(!sw.at(i)->played())
					{
						score+= 1000;
						nb_interrupteur++;
						Mix_PlayChannel(2, s_switch, 0);
						sw.at(i)->setPlayed(true);
						cout << nb_interrupteur << endl;

						if(nb_interrupteur >= 7)
						{
							finish = true;
							win = true;
							cout<< "Fini !" << endl;
						}

					}

					for(int j = 0; j < pf.size(); j++)
					{
						switch(sw.at(i)->getColor())
						{
						case Switch::RED:
							if(pf.at(j)->getColor() == Plateforme::RED1  || 
							   pf.at(j)->getColor() == Plateforme::RED2  || 
							   pf.at(j)->getColor() == Plateforme::RED3)
							{
								pf.at(j)->setActive(true);
							}
						break;

						case Switch::YELLOW:
							if(pf.at(j)->getColor() == Plateforme::YELLOW1  || 
							   pf.at(j)->getColor() == Plateforme::YELLOW2  || 
							   pf.at(j)->getColor() == Plateforme::YELLOW3)
							{
								pf.at(j)->setActive(true);
							}
						break;

						case Switch::GREEN:
							if(pf.at(j)->getColor() == Plateforme::GREEN1  || 
							   pf.at(j)->getColor() == Plateforme::GREEN2  || 
							   pf.at(j)->getColor() == Plateforme::GREEN3)
							{
								pf.at(j)->setActive(true);
							}
						break;

						case Switch::BLUE:
							if(pf.at(j)->getColor() == Plateforme::BLUE1  || 
							   pf.at(j)->getColor() == Plateforme::BLUE2  || 
							   pf.at(j)->getColor() == Plateforme::BLUE3)
							{
								pf.at(j)->setActive(true);
							}
						break;

						case Switch::INDIGO:
							if(pf.at(j)->getColor() == Plateforme::INDIGO1  || 
							   pf.at(j)->getColor() == Plateforme::INDIGO2  || 
							   pf.at(j)->getColor() == Plateforme::INDIGO3)
							{
								pf.at(j)->setActive(true);
							}
						break;

						case Switch::PURPLE:
							if(pf.at(j)->getColor() == Plateforme::PURPLE1  || 
							   pf.at(j)->getColor() == Plateforme::PURPLE2  || 
							   pf.at(j)->getColor() == Plateforme::PURPLE3)
							{
								pf.at(j)->setActive(true);
							}
						break;

						case Switch::PINK:
							if(pf.at(j)->getColor() == Plateforme::PINK1  || 
							   pf.at(j)->getColor() == Plateforme::PINK2  || 
							   pf.at(j)->getColor() == Plateforme::PINK3)
							{
								pf.at(j)->setActive(true);
							}
						break;
						}

					}

				}
			}
		}
}

void colide_plate()
{
	/**** Détection de colision plateformes **/
		for(int i = 0; i < pf.size(); i++)
		{

			/*if( square.getX() + square.getW()  > pf.at(i)->getPosX() && square.getX() + square.getW() < pf.at(i)->getPosX() + 70
				&& square.getY() + square.getH() > pf.at(i)->getPosY())
			{
				square.setPos(pf.at(i)->getPosX() - square.getW(), square.getY());
			}
		    else if ( square.getX() < pf.at(i)->getPosX() + 70 && square.getX() > pf.at(i)->getPosX()
				&& square.getY() + square.getH() > pf.at(i)->getPosY())
			{
				square.setPos(pf.at(i)->getPosX() + 70, square.getY());
			}*/
			/** en dessous de la boite**/
			if((( square.getX() < pf.at(i)->getPosX() && ( square.getX() + square.getW() ) > pf.at(i)->getPosX()) ||
				( square.getX() > pf.at(i)->getPosX() && ( square.getX() + square.getW() ) < pf.at(i)->getPosX() + 70 ) ||
				( square.getX() < ( pf.at(i)->getPosX() + 70 ) && ( square.getX() + square.getW() ) > pf.at(i)->getPosX() + 70 ) ) &&
				( square.getY() <= pf.at(i)->getPosY() + 70) && (square.getY() > pf.at(i)->getPosY()))
			{
				square.setVelocityY(0);
				square.setPos(square.getX(), (pf.at(i)->getPosY() + 70));
				//square.setJump(false);
				square.setFall(true);
			}
			/** Au dessus de la boite **/
			else if((( square.getX() < pf.at(i)->getPosX() && ( square.getX() + square.getW() ) > pf.at(i)->getPosX()) ||
				( square.getX() > pf.at(i)->getPosX() && ( square.getX() + square.getW() ) < pf.at(i)->getPosX() + 70 ) ||
				( square.getX() < ( pf.at(i)->getPosX() + 70 ) && ( square.getX() + square.getW() ) > pf.at(i)->getPosX() + 70 ) ) &&
				( square.getY() + square.getH() >= pf.at(i)->getPosY()) && (square.getY() < pf.at(i)->getPosY()))
			{
				square.setPos(square.getX(), (pf.at(i)->getPosY() - square.getH()));
				square.resetJump(0.0);
			}
			/** dans le vide **/			
			else if( square.getY() + square.getH() < gestionLvl.getHeight()/*** hauteur sol ***/ )
			{
				square.setFall(true);
			}
			
		}
}

void colide_points()
{
	for(int i = 0; i < pts.size(); i++)
		{
			if( (square.getY() + square.getH() > pts.at(i)->getY()) &&	(square.getY() < pts.at(i)->getY() + 25) &&
				(square.getX() + square.getW() > pts.at(i)->getX()) && (square.getX() < pts.at(i)->getX() + 25))
			{
				pts.at(i)->setVelocityY(pts.at(i)->getSpeed() / FRAME_PER_SC);

				if(!pts.at(i)->played())
				{
					score+= 100;
					Mix_PlayChannel(3, item, 0);
					pts.at(i)->setPlayed(true);
				}
			}

		}
}

void display()
{
	SDL_Rect pos;
	pos.x = 0;
	pos.y = 0;

	
	SDL_BlitSurface(source, camera.getCamera(), screen, &pos);

	for(int i = 0; i < sw.size(); i++)
			sw.at(i)->display(screen, camera.getX(), camera.getY());

		for(int i = 0; i < pf.size(); i++)
			pf.at(i)->display(screen, camera.getX(), camera.getY());

		/*** Colision avec les points ***/
		

		for(int i = 0; i < pts.size(); i++)
		{
			if(pts.at(i)->getVelocityY() > 0)
				pts.at(i)->move();

			pts.at(i)->display(screen, camera.getX(), camera.getY());
		}

		for(int i = 0; i < pts.size(); i++)
		{
			if(pts.size() > 1 && pts.at(i)->getCollected())
				pts.erase(pts.begin()+i);
		}


		
        square.display(screen, camera.getX(), camera.getY());

		 //draw current score
		string str_score;
		ostringstream oss_score;
		oss_score << score;
		str_score = oss_score.str();

	
    t_score = TTF_RenderText_Blended(font, const_cast<char*>(str_score.c_str()), color);

    SDL_BlitSurface(t_score, NULL, screen, &r_score);

	if(finish && win)
	{
		cout << "You win" << endl;
		SDL_Rect r_pos;
		t_help = TTF_RenderText_Blended(font, "You win\n press R to play again", color);

		r_pos.x = SCREEN_W / 2 - t_help->w / 2;
		r_pos.y = SCREEN_H / 2 - t_help->h / 2;
		
		
		SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
		SDL_BlitSurface(t_help, NULL, screen, &r_pos);
	}
	else if (finish && !win)
	{
		cout << "You Loose" << endl;
		SDL_Rect r_pos;
		t_help = TTF_RenderText_Blended(font, "You loose\n press R to play again", color);

		r_pos.x = SCREEN_W / 2 - t_help->w / 2;
		r_pos.y = SCREEN_H / 2 - t_help->h / 2;
		
		
		SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
		SDL_BlitSurface(t_help, NULL, screen, &r_pos);
	}

        //Mise à jour de l'ecran
        if( SDL_Flip( screen ) == -1 )
        {
            exit(2);
        }
}

int main ( int argc, char** argv )
{
	init();	

	source = SDL_CreateRGBSurface(SDL_SWSURFACE, gestionLvl.getWidth(), gestionLvl.getHeight(), 16,0,0,0,0);

	gestionLvl.LevelGen(7, SCREEN_W, SCREEN_W *5, SCREEN_H, SCREEN_H *5);

	pf  = gestionLvl.getPlateformes();
	sw  = gestionLvl.getSwitchs();
	pts = gestionLvl.getPoints();

	square.setPos(gestionLvl.getStartX(), gestionLvl.getStartY());
	square.setLvlH(gestionLvl.getHeight());
	square.setLvlW(gestionLvl.getWidth());
/*** Main Loop ***/

    bool done = false;

    while (!done)
    {
		fps.start();


        while (SDL_PollEvent(&event))
        {
			handle_event();
           //Si l'utilisateur a cliqué sur le X de la fenêtre
            if( event.type == SDL_QUIT )
            {
                //On quitte le programme
                done = true;
            }
        }

		square.move();
		camera.setCenter(square.getX(), square.getY(), gestionLvl.getWidth(), gestionLvl.getHeight());

		colide_switch();
		colide_plate();
		colide_points();
		
		display();

        //On rend la main tant qu'on en a pas besoin
        while( fps.get_ticks() < 1000 / FRAME_PER_SC )
        {
            //Attente...
        }

		SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
    }

	if(SDL_GetTicks() > 300000)
	{
		finish = true;
		win = false;
	}



	Mix_FreeChunk(jump);
	Mix_FreeChunk(s_switch);
	Mix_FreeChunk(item);

	SDL_FreeSurface(screen);
	SDL_FreeSurface(source);
	SDL_FreeSurface(t_timeAttack);
	SDL_FreeSurface(t_help);

	Mix_CloseAudio();

	TTF_CloseFont(font_t);
	TTF_CloseFont(font);

	TTF_Quit();
    printf("Exited cleanly\n");
    return 0;
}