//This file is part of Navier Stokes Solver (GNU GPL) - https://www.youtube.com/user/Muzkaw).

#pragma once

#include <SFML/Graphics.hpp>
#include "Vec2.h"

using namespace std;
using namespace sf;

/*
The input manager is a class to help manage events, time, keyboard and mouse inputs
*/

class InputManager
{
public:
	InputManager(RenderWindow *_window);
	~InputManager();

	void update();

	bool isKeyPressed(Keyboard::Key key);
	bool isKeyPressedOnce(Keyboard::Key key);

	bool isButtonPressed(Mouse::Button button);
	bool isButtonPressedOnce(Mouse::Button button);

	Vec2d prevMousePos();
	Vec2d mousePos();
	Vec2d deltaMouse();
	int ticks();

	double dt();
	double t();

	RenderWindow* getWindowPointer();

private:
	RenderWindow* window;

	vector<bool> keyPressed;
	vector<bool> keyReleased;
	vector<bool> buttonPressed;
	vector<bool> buttonReleased;

	Vec2d previousMousePosition;
	Vec2d mousePosition;

	int scrollTicks;

	Clock time;
	Clock deltaTime;
	double DT;
};

