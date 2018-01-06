//This file is part of Navier Stokes Solver (GNU GPL) - https://www.youtube.com/user/Muzkaw).

#pragma once

#include <vector>
#include "Wall.h"
#include "Vec2.h"

using namespace std;

template<typename T>

class Field
{
public:
	Field();
	Field(int const& _col, int const& _row, T const& val0, double const &_dx);

	void resize(int const& _col, int const& _row, T const& val0);

	T& operator() (int i, int j);
	T operator() (int i, int j) const;
	T& operator() (Vec2<int> el);
	T operator() (Vec2<int> el) const;

	int getRow() const;
	int getCol() const;
	void setDx(double const& _scale);
	double getDx() const;

private:
	vector<T> c;
	int col;
	int row;
	double dx;
};

template<typename T>
Field<T> operator-=(Field<T> &m1, Field<T> const& m2);

template<typename T>
void rot(Field<T> &rotF, Field<Vec2<T>> const& F);
template<typename T>
void grad(Field<Vec2<T>> &gradF, Field<T> const& F);
template<typename T>
void div(Field<T> &divF, Field<Vec2<T>> const& F);
template<typename T>
void gradT(Field<Vec2<T>> &gradF, Field<T> const& F);

template<typename T>
T bilerp(Field<T> const& F, Vec2d const& X);

template<typename T>
void advect(Field<Vec2<T>> &v, Field<T> &d, Field<Wall> const& wall, double const& dt);

template<typename T>
void relaxation(Field<T> &x, Field<T> const& b, Field<Wall> const& wall, double const& alpha, double const& beta, int const& kmax);

#include "Field.cpp"