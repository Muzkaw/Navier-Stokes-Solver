/*********************************************************************

This file is part of Navier Stokes Solver (GNU GPL) - https://www.youtube.com/user/Muzkaw).

Navier Stokes Solver is free software : you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Navier Stokes Solver is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Navier Stokes Solver. If not, see <http://www.gnu.org/licenses/>.

Navier Stokes Solver codded by Muzkaw : https://www.youtube.com/user/Muzkaw
You need to link SFML 2.0 or above to run the program

********************************************************************/

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Fluid.h"
#include "Plotter.h"
#include "InputManager.h"

using namespace std;
using namespace sf;

int main()
{
	int width(200), height(100);
	double scale = 5;

	ContextSettings aa; aa.antialiasingLevel = 4;
	RenderWindow window(VideoMode(width*scale, height*scale+200), "Navier Stokes Solver", sf::Style::Default, aa);
	InputManager in(&window);
	
	Fluid fluid(width, height, 0.2);
	Plotter plot(&window, width, height, scale);

	Font font; font.loadFromFile("consola.ttf");
	Text text("", font, 10); text.setFillColor(Color::White); text.setPosition(10, height*scale + 10);
	
	while (window.isOpen())
	{
		in.update();

		if(in.isButtonPressed(Mouse::Middle)) fluid.setWallZone(in.mousePos()/scale, 40/scale, NSLP);
		if (in.isButtonPressed(Mouse::Middle) && in.isKeyPressed(Keyboard::LControl)) fluid.setWallZone(in.mousePos() / scale, 4, FLUID);

		fluid.update(0.005);

		text.setString(fluid.getState(Vec2i((int)(in.mousePos().x / scale), (int)(in.mousePos().y/scale))));

		window.clear();
		//plot.drawScalarField(fluid.getp(), BiColor, 0.0001, 0, 240);
		plot.drawScalarField(fluid.getw(), BiColor, 100, 0, 120);
		//plot.drawScalarField(fluid.getdivv(), BiColor, 4, 0, 120);
		//plot.drawVectorField(fluid.getv(), Rainbow, 0.5, 240, 5);
		//plot.drawVectorField(fluid.getgradp(), Rainbow, 0.05, 240, 1);

		plot.drawWallField(fluid.getwall());

		//plot.drawVectorField(fluid.getgradp(), Vector, 0.2, 80, 1);
		//plot.drawVectorField(fluid.getv(), Vector, 1.5, 80, 4);
		plot.drawVectorField(fluid.getv(), StreamLines, 0.5, 80, 2);

		window.draw(text);

		window.display();
	}

	system("pause") ;
}