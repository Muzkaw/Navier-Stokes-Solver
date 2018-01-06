//This file is part of Navier Stokes Solver (GNU GPL) - https://www.youtube.com/user/Muzkaw).

#include "Plotter.h"

Plotter::Plotter(RenderWindow *_window, int const& _col, int const& _row, double const& _scale)
{
	window = _window;

	image.create(_col, _row, Color::Red);
	texture.loadFromImage(image);
	sprite.setTexture(texture, true);
	sprite.setScale(_scale, _scale);
	VA.setPrimitiveType(Lines);

	scale = _scale;
}

void Plotter::drawScalarField(Field<double> const& F, int const& style, double const& max, double const& value1, double const& value2, double const& threshold)
{
	switch (style)
	{
	case Rainbow:
		for (int i(0); i < F.getCol(); i++)
			for (int j(0); j < F.getRow(); j++)
				image.setPixel(i, j, HSVColor(value1 - (F(i, j) / max)*value1, 1, 1).RGB());
		break;

	case MonoColor:
		for (int i(0); i < F.getCol(); i++)
			for (int j(0); j < F.getRow(); j++)
				image.setPixel(i, j, HSVColor(value1, 0, F(i, j) / max).RGB());
		break;

	case BiColor:
		for (int i(0); i < F.getCol(); i++)
			for (int j(0); j < F.getRow(); j++)
				if (F(i, j) > threshold) image.setPixel(i, j, HSVColor(value1, 1, (F(i, j)-threshold) / max).RGB());
				else image.setPixel(i, j, HSVColor(value2, 1, -(F(i, j)-threshold) / max).RGB());
				break;
	}

	texture.loadFromImage(image);
	sprite.setTexture(texture, true);
	window->draw(sprite);
}

void Plotter::drawWallField(Field<Wall> const& F)
{
	for (int i(0); i < F.getCol(); i++)
		for (int j(0); j < F.getRow(); j++)
			if(F(i,j).bnd == FLUID) image.setPixel(i, j, Color::Transparent);
			else image.setPixel(i, j, HSVColor(F(i, j).bnd / 4.1 * 360, 1, 1).RGB());

	texture.loadFromImage(image);
	sprite.setTexture(texture, true);
	window->draw(sprite);
}