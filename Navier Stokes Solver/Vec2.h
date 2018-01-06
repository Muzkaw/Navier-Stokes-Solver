//This file is part of Navier Stokes Solver (GNU GPL) - https://www.youtube.com/user/Muzkaw).

#pragma once

#include <cmath>
#include <algorithm>
#include <iostream>

#include <SFML/Graphics.hpp>

using namespace std;

template<typename T>

class Vec2
{
public:
	Vec2();
	Vec2(T const& _x, T const& _y);

	template<typename U>
	explicit Vec2(Vec2<U> const& u);

	sf::Vector2f sfVec2f()
	{
		return Vector2f(x, y);
	}

	T x, y;
};

template<typename T>
Vec2<T> operator-(Vec2<T> const& u);

template<typename T>
Vec2<T> operator+=(Vec2<T> &u, Vec2<T> const& v);
template<typename T>
Vec2<T> operator-=(Vec2<T> &u, Vec2<T> const& v);
template<typename T>
Vec2<T> operator*=(Vec2<T> &u, T const& k);
template<typename T>
Vec2<T> operator/=(Vec2<T> &u, T const& k);

template<typename T>
Vec2<T> operator+(Vec2<T> u, Vec2<T> const& v);
template<typename T>
Vec2<T> operator-(Vec2<T> u, Vec2<T> const& v);
template<typename T>
Vec2<T> operator*(Vec2<T> u, T const& k);
template<typename T>
Vec2<T> operator*(T const& k, Vec2<T> u);
template<typename T>
Vec2<T> operator/(Vec2<T> u, T const& k);

template<typename T>
bool operator==(Vec2<T> const& u, Vec2<T> const& v);
template<typename T>
bool operator!=(Vec2<T> const& u, Vec2<T> const& v);

template<typename T>
double norm(Vec2<T> const& u);
template<typename T>
Vec2<T> unitN(Vec2<T> const& u);
template<typename T>
Vec2<T> unitT(Vec2<T> const& u);

template<typename T>
ostream& operator<<(ostream &stream, Vec2<T> const& u);

template<typename T>
double dot(Vec2<T> const& u, Vec2<T> const& v);
template<typename T>
double cross(Vec2<T> const& u, Vec2<T> const& v);

template<typename T>
Vec2<T> clamp(Vec2<T> &u, Vec2<T> const& mini, Vec2<T> const& maxi);

#include "Vec2.cpp"

typedef Vec2<int> Vec2i;
typedef Vec2<float> Vec2f;
typedef Vec2<double> Vec2d;