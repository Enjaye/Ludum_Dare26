/**********************************************
/***        Back To Rainbows
/***         
/***      By Angélique Lesage for LD26 contest
/***
/***            Level.hpp
/**********************************************/

#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include "Switch.hpp"
#include "Plateforme.hpp"
#include "Point.hpp"

class Level
{
public:
	Level();
	~Level();

	/*** Level creation function ***/
	void	Level0();
	void	LevelGen(int n_couleur, int w_min, int w_max, int h_min, int h_max);
	void	createCube(int n, int c);
	void	createSwitch(int n);
	void	createPoint(int n);

	/***  level ressource managment ***/

	std::vector<Point*>			getPoints();
	std::vector<Plateforme*>	getPlateformes();
	std::vector<Switch*>		getSwitchs();
	
	int		getHeight();
	int		getWidth();
	float	getStartX();
	float	getStartY();


protected:

	std::vector<Point*>			pts;
	std::vector<Plateforme*>	pf;
	std::vector<Switch*>		sw;

	int		width, height;
	float	start[2];
};


#endif