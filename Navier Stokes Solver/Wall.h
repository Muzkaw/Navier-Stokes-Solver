//This file is part of Navier Stokes Solver (GNU GPL) - https://www.youtube.com/user/Muzkaw).

#pragma once

#include <iostream>

using namespace std;

enum bnd { FLUID, NSLP, SLP, IN, OUT };
enum loc { CENTER, EDGE, CORNER , ERR = 20 } ;

class Wall
{
public:
	Wall() : bnd(FLUID), N(0), S(0), E(0), W(0), neighbor(0), loc(CENTER) {}

	bnd bnd;
	loc loc;
	int N, S, E, W;
	int neighbor;
	

	void updateLoc()
	{
		neighbor = N+S+E+W;

		switch (neighbor)
		{
		case 2:
			if (N*S == 1 || E*W == 1) loc = EDGE;
			else loc = CORNER;
			break;
		case 3:
			loc = EDGE;
			break;
		case 4:
			loc = CENTER;
			break;
		default:
			loc = ERR;
			break;
		}
	}
};