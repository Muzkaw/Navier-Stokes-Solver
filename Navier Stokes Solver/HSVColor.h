//This file is part of Navier Stokes Solver (GNU GPL) - https://www.youtube.com/user/Muzkaw).

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

struct HSVColor
{
	HSVColor();
	HSVColor(float const& hue, float const& saturation, float const& value);

	Color RGB();

	float h;
	float s;
	float v;
};