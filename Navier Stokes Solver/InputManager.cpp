//This file is part of Navier Stokes Solver (GNU GPL) - https://www.youtube.com/user/Muzkaw).

#include "InputManager.h"

InputManager::InputManager(RenderWindow *_window)
{
	window = _window;

	for (int i(0); i < Keyboard::KeyCount; i++) keyPressed.push_back(false);
	for (int i(0); i < Keyboard::KeyCount; i++) keyReleased.push_back(false);
	for (int i(0); i < Mouse::ButtonCount; i++) buttonPressed.push_back(false);
	for (int i(0); i < Mouse::ButtonCount; i++) buttonReleased.push_back(false);

	DT = 0.01;
	time.restart();

	mousePosition = Vec2d(0, 0);
}
InputManager::~InputManager()
{
	window = 0;
}

void InputManager::update()
{
	for (int i(0); i < keyPressed.size(); i++) keyPressed[i] = false;
	for (int i(0); i < keyReleased.size(); i++) keyReleased[i] = false;
	for (int i(0); i < buttonPressed.size(); i++) buttonPressed[i] = false;
	for (int i(0); i < buttonReleased.size(); i++) buttonReleased[i] = false;
	scrollTicks = 0;

	Event event;
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case Event::KeyPressed: keyPressed[event.key.code] = true;	break;
		case Event::KeyReleased: keyReleased[event.key.code] = true;	break;
		case Event::MouseButtonPressed: buttonPressed[event.mouseButton.button] = true; break;
		case Event::MouseButtonReleased: buttonReleased[event.mouseButton.button] = true; break;
		case Event::MouseWheelMoved: scrollTicks = event.mouseWheel.delta; break;
		}
	}

	previousMousePosition = mousePosition;
	Vector2f buf = window->mapPixelToCoords(Mouse::getPosition(*window));
	mousePosition = Vec2d(buf.x, buf.y);

	DT = deltaTime.restart().asSeconds();
}
bool InputManager::isKeyPressed(Keyboard::Key key)
{
	return Keyboard::isKeyPressed(key);
}
bool InputManager::isKeyPressedOnce(Keyboard::Key key)
{
	return keyPressed[key];
}
bool InputManager::isButtonPressed(Mouse::Button button)
{
	return Mouse::isButtonPressed(button);
}
bool InputManager::isButtonPressedOnce(Mouse::Button button)
{
	return buttonPressed[button];
}

Vec2d InputManager::prevMousePos()
{
	return previousMousePosition;
}
Vec2d InputManager::mousePos()
{
	return mousePosition;
}
Vec2d InputManager::deltaMouse()
{
	return mousePosition - previousMousePosition;
}
int InputManager::ticks()
{
	return scrollTicks;
}

double InputManager::dt()
{
	return DT;
}
double InputManager::t()
{
	return time.getElapsedTime().asSeconds();
}
RenderWindow* InputManager::getWindowPointer()
{
	return window;
}
