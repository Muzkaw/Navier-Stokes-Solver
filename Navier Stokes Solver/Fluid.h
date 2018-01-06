//This file is part of Navier Stokes Solver (GNU GPL) - https://www.youtube.com/user/Muzkaw).

#pragma once

#include "Field.h"
#include "Wall.h"
#include <sstream>
#include <iomanip>

using namespace std;

class Fluid
{
public:
	Fluid(int const& _width, int const& _height, double const& Lwidth);

	void update(double const& dt);

	void setBnd();

	Field<double> getp() const;
	Field<double> getw() const;
	Field<double> getdivv() const;
	Field<Vec2d> getgradp() const;
	Field<Vec2d> getv() const;
	Field<Wall> getwall() const;

	void updateWall();

	string getState(Vec2<int> const& el);

	void setWallZone(Vec2d const& pos, double const& size, bnd const& bnd_type);

private:
	int width;
	int height;
	double dx;

	Field<double> p, d, w, divv;
	Field<Vec2<double>> v, gradp, rotw;
	Field<Wall> wall;

	double vel0;
};

