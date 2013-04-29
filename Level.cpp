/**********************************************
/***        Back To Rainbows
/***         
/***      By Angélique Lesage for LD26 contest
/***
/***            Level.cpp
/**********************************************/

#include "Level.hpp"
#include "Enum.hpp"
#include <iostream>

Level::Level() {}
Level::~Level(){}

/*** Level creation function ***/
/** Introduction Level : Always the same **/
void	Level::Level0()
{
	height = 730; width = 1985;
	start[X] = 50;
	start[Y] = GROUND - 60;

	float x = 1084, y = 614;

	/**first ligne pyramide**/
	for(int i = 0; i < 11; i++)
		pf.push_back(new Plateforme(7, x + (i*70), y));

	y -= 70; x += 70;
	
	for(int i = 0; i < 9; i++)
		pf.push_back(new Plateforme(7, x + (i*70), y));

	y -= 70; x += 70;

	for(int i = 0; i < 7; i++)
		pf.push_back(new Plateforme(7, x + (i*70), y));

	y -= 70; x += 70;

	for(int i = 0; i < 5; i++)
		pf.push_back(new Plateforme(7, x + (i*70), y));

	y -= 70; x += 70;

	for(int i = 0; i < 3; i++)
		pf.push_back(new Plateforme(7, x + (i*70), y));

	pf.push_back(new Plateforme(7, x+70, y-70));

	/*** switch ***/
	sw.push_back(new Switch(Switch::RED,	pf.at(0)->getPosX() - 70, GROUND - 35));
	sw.push_back(new Switch(Switch::YELLOW, pf.at(0)->getPosX() + 5,  pf.at(0)->getPosY() - 35));
	sw.push_back(new Switch(Switch::GREEN,	pf.at(11)->getPosX() + 5, pf.at(11)->getPosY() - 35));
	sw.push_back(new Switch(Switch::BLUE,	pf.at(20)->getPosX() + 5, pf.at(20)->getPosY() - 35));
	sw.push_back(new Switch(Switch::INDIGO, pf.at(27)->getPosX() + 5, pf.at(27)->getPosY() - 35));
	sw.push_back(new Switch(Switch::PURPLE, pf.at(32)->getPosX() + 5, pf.at(32)->getPosY() - 35));
	sw.push_back(new Switch(Switch::PINK,	pf.at(35)->getPosX() + 5, pf.at(35)->getPosY() - 35));
	
	/*** item ***/
	pts.push_back(new Point(100 , GROUND - 30));
	pts.push_back(new Point(300 , GROUND - 30));
	pts.push_back(new Point(350 , GROUND - 30));
	pts.push_back(new Point(600 , GROUND - 30));
	pts.push_back(new Point(640 , GROUND - 60));
	pts.push_back(new Point(680 , GROUND - 90));
	pts.push_back(new Point(720 , GROUND - 60));	
	pts.push_back(new Point(760 , GROUND - 30));
	
}

void	Level::LevelGen(int n_couleur, int w_min, int w_max, int h_min, int h_max)
{
	int		nb_cube, min_cube, max_cube, nb_points, min_points, max_points, free_place = 0;
	float	pos[2];
	bool	create = false;

	pts.clear();
	pf.clear();
	sw.clear();

	height = rand()%(h_max - h_min) + h_min;
	width  = rand()%(w_max - w_min) + w_min;

	std::cout << "Height : "<< height << ", Width : "<< width << std::endl;

	/*** Calcul for number of cube **/

	nb_cube = (height * width) / 4900; //maximum number of plateforme that could fit in the window, of course, i'll turn it down, let's take
	//between 35% and 60% of this number to get our final cube numbers
	min_cube = (nb_cube * 5) / 100;
	max_cube = (nb_cube * 10) / 100;

	nb_cube = rand()%(max_cube - min_cube) + min_cube;

	std::cout << "nombre cube :" << nb_cube << std::endl;

	createCube(nb_cube, n_couleur);
/*******  End of Cube Creation !! ****/
	std::cout << "Creation des cubes finies : " << pf.size() << std::endl;


	createSwitch(n_couleur);
/***** END of Switch creation !!! ****/
	std::cout << "Switches created " << std::endl;


	createPoint(n_couleur);
	std::cout << "all points created " << pts.size() << std::endl;
/***** Nearly done with it, only thing left is the Hero start position !
	   we just check if we're not on a cube nor a switch nor beneath ground ***/

	create = false;

	do
	{
		pos[X] = 0;
		pos[Y] = 0;

		while(pos[X] + 38 > width)
			pos[X] = rand()%(width);

		while(pos[Y] + 60 > GROUND)
			pos[Y] = rand()%(height);

		bool ok = true;

		do
		{
			/*** First, test if not on a plateforme ***/
			for(int x = 0; x <= 38; x++)
					for(int y = 0; y <= 60; y++)
						for(int k = 0; k < pf.size(); k++)
							if(pf.at(k)->onObject(pos[X] + x, pos[Y] + y))
								ok = false;

				/*** second, test if not touching a switch ***/
				for(int x = 0; x <= 38; x++)
					for(int y = 0; y <= 60; y++)
						for(int k = 0; k < sw.size(); k++)
							if(sw.at(k)->onObject(pos[X] + x, pos[Y] + y))
								ok = false;
			
			/*** it's okay we can create the start poin ***/
				start[X] = pos[X];
				start[Y] = pos[Y];

				create = true;
				ok	= false;
		}while(ok);

	}while(!create);

	std::cout << "player's coordinate ok" << std::endl;
	/**** AND WE'RE DONE ***/

}

void	Level::createCube(int n, int c)
{
	float pos[2];
	bool  create;
	int	  free_place;

	/*** Position for the cube ***/
	pos[X] = rand()%(width);
	pos[Y] = rand()%(height);

	pf.push_back(new Plateforme(c, pos[X], pos[Y]));
	std::cout << pf.at(0)->getPosX() << ", " << pf.at(0)->getPosY() << std::endl;

	for( int i = 0; i < n-1 ; i++) //n - 1 cause we've already created cube 0
	{
		create = false;
		std::cout << "size pf a la boucle " << i << " : " << pf.size() << std::endl;
		
		if(pf.size() > n)
			i = n+1;

		do
		{
			pos[X] = rand()%(width);
			pos[Y] = rand()%(height);

			//std::cout << "Try for " << i+1 << "with [" << pos[X] <<"," << pos[Y] << std::endl;

			for( int j = 0; j < pf.size(); j++)
			{
				if(pf.at(j)->onObject(pos[X], pos[Y]))
				{
					free_place = 0;
					/*** we're on a cube, lets test if its four sides are occupied or not ***/
					if(!pf.at(j)->onObject(pos[X] - 70, pos[Y]) && pos[X] - 70 > 0)
					{
						free_place+=1; //space left is free
					}

					if(!pf.at(j)->onObject(pos[X] + 70, pos[Y]) && pos[X] + 70 < width)
					{
						free_place+=2; //space right is free
					}

					if(!pf.at(j)->onObject(pos[X], pos[Y] - 70) && pos[Y] - 70 > 0)
					{
						free_place+=4;
					}

					if(!pf.at(j)->onObject(pos[X], pos[Y] + 70) && pos[Y] + 70 < height)
					{
						free_place+=8; //space down is free
						
					}

					/*** Now, we know which side of the cube are free, if we have several choice, we'll "throw a dice" other wise, we'll take the
					only one that is free, and in the case none are free, we'll go back with new coordinate **/
					/*** use of flags simplify the test : you already know wich sides are free thanks to value ***/
					int d;

					switch(free_place)
					{
					case 1:	 pf.push_back(new Plateforme(c, pos[X] - 70, pos[Y]));	create = true; break;
					case 2:	 pf.push_back(new Plateforme(c, pos[X] + 70, pos[Y]));	create = true; break;
					case 4:	 pf.push_back(new Plateforme(c, pos[X], pos[Y] - 70));	create = true; break;
					case 8:  pf.push_back(new Plateforme(c, pos[X], pos[Y] + 70));	create = true; break;
					/**** Two free places ****/
					case 3:  //left and right
						d = rand()%6;
						if(d%2 == 0)
							pf.push_back(new Plateforme(c, pos[X] - 70, pos[Y])); 
						else
							pf.push_back(new Plateforme(c, pos[X] + 70, pos[Y]));

						create = true;
					break;

					case 5: //left and up
						d = rand()%6;
						if(d%2 == 0)
							pf.push_back(new Plateforme(c, pos[X] - 70, pos[Y])); 
						else
							pf.push_back(new Plateforme(c, pos[X], pos[Y] - 70));

						create = true;
					break;

					case 6: //right and up
						d = rand()%6;
						if(d%2 == 0)
							pf.push_back(new Plateforme(c, pos[X] + 70, pos[Y])); 
						else
							pf.push_back(new Plateforme(c, pos[X], pos[Y] - 70));

						create = true;
					break;

					case 9: //left and down
						d = rand()%6;
						if(d%2 == 0)
							pf.push_back(new Plateforme(c, pos[X] - 70, pos[Y])); 
						else
							pf.push_back(new Plateforme(c, pos[X], pos[Y] + 70));

						create = true;
					break;

					case 10: // right and down
						d = rand()%6;
						if(d%2 == 0)
							pf.push_back(new Plateforme(c, pos[X] + 70, pos[Y])); 
						else
							pf.push_back(new Plateforme(c, pos[X], pos[Y] + 70));

						create = true;
					break;

					case 12: //up and down
						d = rand()%6;
						if(d%2 == 0)
							pf.push_back(new Plateforme(c, pos[X], pos[Y] - 70)); 
						else
							pf.push_back(new Plateforme(c, pos[X], pos[Y] + 70));

						create = true;
					break;

					/*** 3 possibilies ***/
					case 7: //left and right and up
						d = rand()%6;
						if(d%3 == 0)
							pf.push_back(new Plateforme(c, pos[X] - 70, pos[Y]));
						else if(d%2 == 0)
							pf.push_back(new Plateforme(c, pos[X] + 70, pos[Y]));
						else
							pf.push_back(new Plateforme(c, pos[X], pos[Y] - 70));

						create = true;
					break;

					case 11: //left and right and down
						d = rand()%6;
						if(d%3 == 0)
							pf.push_back(new Plateforme(c, pos[X] - 70, pos[Y]));
						else if(d%2 == 0)
							pf.push_back(new Plateforme(c, pos[X] + 70, pos[Y]));
						else
							pf.push_back(new Plateforme(c, pos[X], pos[Y] + 70));

						create = true;
					break;

					case 13: //left and up and down
						d = rand()%6;
						if(d%3 == 0)
							pf.push_back(new Plateforme(c, pos[X] - 70, pos[Y]));
						else if(d%2 == 0)
							pf.push_back(new Plateforme(c, pos[X], pos[Y] + 70));
						else
							pf.push_back(new Plateforme(c, pos[X], pos[Y] - 70));

						create = true;
					break;

					case 14: //right and up and down
						d = rand()%6;
						if(d%3 == 0)
							pf.push_back(new Plateforme(c, pos[X] + 70, pos[Y]));
						else if(d%2 == 0)
							pf.push_back(new Plateforme(c, pos[X], pos[Y] + 70));
						else
							pf.push_back(new Plateforme(c, pos[X], pos[Y] - 70));

						create = true;
					break;

					}//Fin switch free place

				}			
			}// end for which is testing if we're already on a cube or not

			/*** We're not on a cube right now, before proceding to the creation, let's be sure there's no other cube on the way of 
				the new one ***/
			bool ok = true;
			do
			{
				for(int i = 0; i <= 70; i++)
					for(int j = 0; j <= 70; j++)
						for(int k = 0; k < pf.size(); k++)
							if(pf.at(k)->onObject(pos[X] + i, pos[Y] + j))
								ok = false;
	
			
				if(ok)
				{
					pf.push_back(new Plateforme(c, pos[X], pos[Y]));
					std::cout<<"PLateforme " << i << " crée avec x" <<  std::endl;
					create = true;
				}
			}while(ok);
		}while(!create);
	}
}

void	Level::createSwitch(int n)
{
	/******* Now, let's go for the switches this is how i'm going to process:
	first, get a random id of a cube. Test if there's no other cube ONLY ON THE TOP this time (no more crappy long test, only for the top
	if i wanted to do it properly, i could create a nice reccursive function to reach the top of a pile of cube but :
	1 ~ there are really really few chance to have more than 2 cube on each other, i think 
	2 ~ lazyy let's try this and put all nice code if I got time until the end of the ludum ***/
	bool create = false;

	std::cout << "Nombre couleur : "<< n << std::endl;
	for(int i = 0; i < n; i++)
	{
		/*create = false;
		do
		{*/
			int id = rand()%pf.size();
			std::cout << "id :" << id << std::endl;
			// to be sure to have enough space to be on the switch with the "hero", one condition is recquired :
			// No cube between the top of pf.at(id) and 100pixels upper ( switch is 35px tall and hero 60, rounded up to 100
			// to verify it, we're going through a 3step test :
			// 1 - absolutly no cube on the space that will be occupied by the switch, so the 70 * 35 rectangle on top of the cube
			// 2 - if it's ok, we test two different box, each of 35 * 65. if one of the box is occupied at some point, the other one has
			//    to be free, other wise , there's not enough space for the char to reach the switch
			bool ok = true;
			switch(i)
					{
					case 0:		sw.push_back(new Switch(Switch::RED,	pf.at(id)->getPosX() + 5, pf.at(id)->getPosY() - 35)); break;
					case 1:		sw.push_back(new Switch(Switch::YELLOW, pf.at(id)->getPosX() + 5, pf.at(id)->getPosY() - 35)); break;
					case 2:		sw.push_back(new Switch(Switch::GREEN,	pf.at(id)->getPosX() + 5, pf.at(id)->getPosY() - 35)); break;
					case 3:		sw.push_back(new Switch(Switch::BLUE,	pf.at(id)->getPosX() + 5, pf.at(id)->getPosY() - 35)); break;
					case 4:		sw.push_back(new Switch(Switch::INDIGO, pf.at(id)->getPosX() + 5, pf.at(id)->getPosY() - 35)); break;
					case 5:		sw.push_back(new Switch(Switch::PURPLE, pf.at(id)->getPosX() + 5, pf.at(id)->getPosY() - 35)); break;
					case 6:		sw.push_back(new Switch(Switch::PINK,	pf.at(id)->getPosX() + 5, pf.at(id)->getPosY() - 35)); break;
					}

		
	}

}

void	Level::createPoint(int n)
{
	bool create;
	float pos[2];
	/***** now let's add some points to collect ****/
/***** for points, here's are the criteria :
       - Not on a cube, nor a switch, not a point
	   - Not cube in [point.y + h, 65] to be sure the player can access it

	   to get the number of point to charge, let's calcul it in function of cube ratio on the screen.
	   Eventhough they're not really taking place (as the player can walk throught them) we don't want the 
	   level to be over charged with item.
	   first, trying with 25-35% of lefting space
	   
***/
	
	int nb_points = ((height * width) / 1000); //number of cube that can be hold in the level minus the number of actual cube
	//free_space is the area where we could hold item
	int min_points  = (nb_points * 2) / 100;
	int max_points  = (nb_points * 4) / 100;
	std::cout << nb_points << std::endl;

	if(max_points != min_points)
		nb_points   = rand()%(max_points - min_points) + min_points;
	else
		nb_points	= rand()%(min_points);

	std::cout<<"Nb points " << nb_points << std::endl;
	for(int i = 0; i < nb_points; i++)
	{
		create = false;
	
			pos[X] = rand()%(width);
			pos[Y] = rand()%(height);

			


			bool ok = true;
			
		
				/*** if we're still in the loop at this point, we can add our point ***/
				pts.push_back(new Point(pos[X], pos[Y]));
				create = true;
				ok = false;

	}// end of points loop
}



/***  level ressource managment ***/

std::vector<Point*>			Level::getPoints()		{ return pts; }
std::vector<Plateforme*>	Level::getPlateformes() { return pf;  }
std::vector<Switch*>		Level::getSwitchs()		{ return sw;  }

int		Level::getHeight()	{ return height; }
int		Level::getWidth()   { return width;  }
float   Level::getStartX()	{ return start[X];}
float	Level::getStartY()  { return start[Y];}
