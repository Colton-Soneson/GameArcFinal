#pragma once

#include "GraphicsSystem.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>


using namespace std;

class Event;
class EventSystem;

enum EightDirectional { E_TOP, E_TOP_RIGHT, E_RIGHT, E_DOWN_RIGHT, E_DOWN, E_DOWN_LEFT, E_LEFT, E_TOP_LEFT };	//this is for general use

enum Keys
{
	F_KEY = sf::Keyboard::F,
	S_KEY = sf::Keyboard::S,
	ENT_KEY = sf::Keyboard::Enter,
	ESC_KEY = sf::Keyboard::Escape,
	SPACE_KEY = sf::Keyboard::Space,
	W_KEY = sf::Keyboard::W,
	A_KEY = sf::Keyboard::A,
	D_KEY = sf::Keyboard::D,
	UP_ARROW = sf::Keyboard::Up,
	DOWN_ARROW = sf::Keyboard::Down,
	LEFT_ARROW = sf::Keyboard::Left,
	RIGHT_ARROW = sf::Keyboard::Right,
	UP_LEFT_ARROW = sf::Keyboard::KeyCount + 1,
	UP_RIGHT_ARROW = sf::Keyboard::KeyCount + 2,
	DOWN_LEFT_ARROW = sf::Keyboard::KeyCount + 3,
	DOWN_RIGHT_ARROW = sf::Keyboard::KeyCount + 4,


};

enum MouseButtons
{
	L_MOUSE = sf::Mouse::Button::Left,
	R_MOUSE = sf::Mouse::Button::Right,
	M_MOUSE = sf::Mouse::Button::Middle
};

class InputSystem : public Trackable
{
	//getting keystates
	//getting mouse states
	//graphics system

public:
	InputSystem();
	~InputSystem();

	void init();
	void cleanup();

	void update(sf::RenderWindow* window);

	void setPressWithRelease(bool active) { mPressWithRelease = active; };

	Vector2D getMousePosition(sf::RenderWindow* window);	//passes the accessible vector
	int getMouseState();
	vector<int> getKeyState();		//passes out the enum value of the key

private:

	//ALLEGRO_MOUSE_STATE mMouseState;

	//ALLEGRO_KEYBOARD_STATE mKeyboardState;

	int mPreviousMouseState;	//the mouse event previously pressed

	int mPreviousKeyboardDown;	//the event that was previously pressed down

	Vector2D mPreviousMousePos;

	bool mPressWithRelease; //option to make the buttons press with release
};