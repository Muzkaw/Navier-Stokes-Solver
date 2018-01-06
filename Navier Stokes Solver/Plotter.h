//This file is part of Navier Stokes Solver (GNU GPL) - https://www.youtube.com/user/Muzkaw).

#pragma once

#include <SFML/Graphics.hpp>
#include "Field.h"
#include "Wall.h"
#include "HSVColor.h"

using namespace std;
using namespace sf;

enum Style {Rainbow, MonoColor, BiColor, Vector, StreamLines};

class Plotter
{
public:
	Plotter(RenderWindow *_window, int const& _col, int const& _row, double const& _scale);

	void drawScalarField(Field<double> const& F, int const& style, double const& max, double const& value1, double const& value2 = 0, double const& threshold = 0);
	
	template<typename T>
	void drawVectorField(Field<Vec2<T>> const& F, int const& style, double const& max, double const& value, int const& dx = 0);

	void drawWallField(Field<Wall> const& F);

private:
	RenderWindow *window;

	Image image;
	Texture texture;
	Sprite sprite;
	VertexArray VA;

	double scale;
};

template<typename T>
void Plotter::drawVectorField(Field<Vec2<T>> const& F, int const& style, double const& max, double const& value, int const& dx)
{
	switch (style)
	{
	case Rainbow:
		for (int i(0); i < F.getCol(); i++)
			for (int j(0); j < F.getRow(); j++)
				image.setPixel(i, j, HSVColor(value - (norm(F(i, j)) / max)*value, 100, 100).RGB());
		texture.loadFromImage(image);
		sprite.setTexture(texture, true);
		window->draw(sprite);
		break;
	case Vector:
		VA.clear();
		for (int i(0); i < F.getCol(); i += dx)
		{
			for (int j(0); j < F.getRow(); j += dx)
			{
				VA.append(Vertex(Vector2f(scale*(i+0.5), scale*(j+0.5)), HSVColor(value, 0.5, 0.5).RGB()));
				VA.append(Vertex(Vector2f(scale*(i + 0.5), scale*(j + 0.5)) + Vector2f(F(i, j).x/max, F(i, j).y/max)*100.f, HSVColor(value, 0.5, 0.5).RGB()));
			}
		}
		window->draw(VA);
		break;

	case StreamLines:
		VA.clear();
		Vec2d pos;
		int it;

		for (int j(0); j < F.getRow(); j += dx)
		{
			pos = Vec2d(0, j);
			VA.append(Vertex((pos*scale).sfVec2f(), Color::Transparent));
			VA.append(Vertex((pos*scale).sfVec2f(), HSVColor(value, 0.5, 0.5).RGB()));

			it = 0;
			while(pos.x < F.getCol() && it < 400)
			{
				pos += bilerp(F, pos)/max;
				VA.append(Vertex((pos*scale).sfVec2f() , HSVColor(value, 0.5, 0.5).RGB()));
				VA.append(VA[VA.getVertexCount() - 1]);
				it++;
			}
			VA.append(Vertex(VA[VA.getVertexCount() - 1].position,Color::Transparent));
		}
		
		window->draw(VA);
		break;
	}
}