//This file is part of Navier Stokes Solver (GNU GPL) - https://www.youtube.com/user/Muzkaw).

#include "Fluid.h"

Fluid::Fluid(int const& _width, int const& _height, double const& Lwidth)
{
	width = _width;
	height = _height;
	dx = Lwidth / (double)width;

	p = Field<double>(width, height, 0, dx);
	d = Field<double>(width, height, 0, dx);
	w = Field<double>(width, height, 0, dx);
	divv = Field<double>(width, height, 0, dx);

	vel0 = 0.3;

	v = Field<Vec2d>(width, height, Vec2d(0, 0), dx);
	gradp = Field<Vec2d>(width, height, Vec2d(0, 0), dx);
	rotw = Field<Vec2d>(width, height, Vec2d(0, 0), dx);

	wall = Field<Wall>(width, height, Wall(), dx);

	for (int i(0); i < width; i++)
	{
		wall(i, 0).bnd = NSLP;
		wall(i, height - 1).bnd = NSLP;
	}
	for (int j(1); j < height-1; j++)
	{
		wall(0, j).bnd = IN;
		wall(1, j).bnd = IN;
		wall(width - 1, j).bnd = OUT;
	}

	updateWall();

	for (int i(0); i < width; i++)
		for (int j(0); j < height; j++)
			if (wall(i, j).bnd == FLUID) v(i, j) = Vec2d(vel0, 0);
}
void Fluid::update(double const& dt)
{
	rot(w, v);
	//gradT(rotw, w);

	advect(v, d, wall, dt);
	setBnd();
	
	double nu = 0.0000001;
	relaxation(v, v, wall, dx*dx / (nu*dt), 4 + dx*dx / (nu*dt),10);
	setBnd();

	div(divv, v);

	relaxation(p, divv,wall, -dx*dx, 4, 50);
	setBnd();

	grad(gradp, p);
	v -= gradp;

	setBnd();	
}

void Fluid::setBnd()
{
	for (int i(0); i < width; i++)
	{
		for (int j(0); j < height; j++)
		{
			if (wall(i, j).bnd == NSLP)
			{
				if (wall(i, j).loc == CORNER)
				{
					v(i, j) = Vec2d(0, 0);

				}
				else if (wall(i, j).loc == EDGE)
				{
					v(i, j) = -v(i + (1 - wall(i, j).E) - (1 - wall(i, j).W), j + (1 - wall(i, j).N) - (1 - wall(i, j).S));
					p(i, j) = p(i + (1 - wall(i, j).E) - (1 - wall(i, j).W), j + (1 - wall(i, j).N) - (1 - wall(i, j).S));
				}
				else if (wall(i, j).loc == CENTER)
				{
					v(i, j) = Vec2d(0, 0);
				}
			}
			if (wall(i, j).bnd == IN)
			{
				v(i, j) = Vec2d(vel0, 0);
			}
			if (wall(i, j).bnd == OUT)
			{
				v(i, j) = v(i + (1 - wall(i, j).E) - (1 - wall(i, j).W), j + (1 - wall(i, j).N) - (1 - wall(i, j).S));
			}
		}
	}
}


void Fluid::updateWall()
{
	for (int i(0); i < width; i++)
	{
		for (int j(0); j < height; j++)
		{
			if (j + 1 > height - 1) wall(i, j).N = 1;
			else if (wall(i, j + 1).bnd == NSLP) wall(i, j).N = 1;
			else wall(i, j).N = 0;

			if (j - 1 < 0) wall(i, j).S = 1;
			else if (wall(i, j - 1).bnd == NSLP) wall(i, j).S = 1;
			else wall(i, j).S = 0;

			if (i + 1 > width - 1) wall(i, j).E = 1;
			else if (wall(i + 1, j).bnd == NSLP) wall(i, j).E = 1;
			else wall(i, j).E = 0;

			if (i - 1 < 0) wall(i, j).W = 1;
			else if (wall(i - 1, j).bnd == NSLP) wall(i, j).W = 1;
			else wall(i, j).W = 0;
		}
	}
	
	for (int i(0); i < width; i++)
		for (int j(0); j < height; j++)
			wall(i, j).updateLoc();
}

Field<double> Fluid::getp() const
{
	return p;
}
Field<double> Fluid::getw() const
{
	return w;
}
Field<double> Fluid::getdivv() const
{
	return divv;
}
Field<Vec2d> Fluid::getgradp() const
{
	return gradp;
}
Field<Vec2d> Fluid::getv() const
{
	return v;
}
Field<Wall> Fluid::getwall() const
{
	return wall;
}
string Fluid::getState(Vec2<int> const& el)
{
	stringstream ss;
	ss << fixed << setprecision(2);
	string result;

	if (el.x >= 0 && el.x < width && el.y >= 0 && el.y < height)
		ss << "X = " << el.x*dx * 1000 << " ; " << el.y*dx * 1000 << endl <<
		"p = " << p(el) * 1000000 << endl <<
		"V = " << v(el).x * 1000 << " ; " << v(el).y * 1000 << " - " << norm(v(el)) * 1000 << endl <<
		"w = " << w(el) * 1000 << endl << endl <<
		"bnd = "<< wall(el).bnd << " loc = "<<wall(el).loc << " neigh = "<<wall(el).neighbor << endl <<
		"N"<<wall(el).N<< "S" << wall(el).S << "E" << wall(el).E << "W" << wall(el).W;

	result = ss.str();
	return result;
}

void Fluid::setWallZone(Vec2d const& pos, double const& size, bnd const& bnd_type)
{
	for (int i(pos.x - size); i < pos.x + size; i++)
		for (int j(pos.y - size); j < pos.y + size; j++)
			if (norm(Vec2d(i, j)- pos) < size )
				wall(i, j).bnd = bnd_type;
	updateWall();
}