//This file is part of Navier Stokes Solver (GNU GPL) - https://www.youtube.com/user/Muzkaw).

#include "HSVColor.h"

HSVColor::HSVColor()
{
	h = 0;
	s = 0;
	v = 0;
}
HSVColor::HSVColor(float const& hue, float const& saturation, float const& value)
{
	h = min(max(hue, 0.f), 360.f);
	s = min(max(saturation, 0.f), 1.f);
	v = min(max(value, 0.f), 1.f);
}

Color HSVColor::RGB()
{
	float r, g, b;
	int hi = (int)(h / 60.f);
	float f = h / 60.f - hi;
	float l = v*(1 - s);
	float m = v*(1 - f*s);
	float n = v*(1 - (1 - f)*s);

	switch (hi)
	{
	case 0: r = v; g = n; b = l; break;
	case 1: r = m; g = v; b = l; break;
	case 2: r = l; g = v; b = n; break;
	case 3: r = l; g = m; b = v; break;
	case 4: r = n; g = l; b = v; break;
	case 5: r = v; g = l; b = m; break;
	}

	return Color(255.f*r, 255.f*g, 255.f*b);
}
