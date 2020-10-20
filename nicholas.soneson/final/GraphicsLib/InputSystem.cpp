#include "InputSystem.h"
#include "EventSystem.h"
#include "Event.h"
#include "MoveEvent.h"

using namespace std;

InputSystem::InputSystem()
{
	mPreviousKeyboardDown = -1;
	mPreviousMouseState = -1;
	mPreviousMousePos.setX(0.0f);
	mPreviousMousePos.setY(0.0f);
	mPressWithRelease = false;
}

InputSystem::~InputSystem()
{
	cleanup();
}

void InputSystem::init()
{
	//al_install_mouse();
	//al_install_keyboard();
}

void InputSystem::cleanup()
{
	//al_uninstall_keyboard();
	//al_uninstall_mouse();
}


void InputSystem::update(sf::RenderWindow* window)
{	

	vector<int> keyCodes = getKeyState();

	while (keyCodes.size() > 0)
	{

		int keyCode = keyCodes.back();

		if (!mPressWithRelease)
		{
			if (keyCode == F_KEY)
			{
				EventSystem::getInstance()->fireEvent(F_KEY_EVENT);
			}

			if (keyCode == S_KEY)
			{
				EventSystem::getInstance()->fireEvent(S_KEY_EVENT);
			}

			if (keyCode == ESC_KEY)
			{
				EventSystem::getInstance()->fireEvent(ESCAPE_EVENT);
			}

			if (keyCode == ENT_KEY)
			{
				EventSystem::getInstance()->fireEvent(ENTER_EVENT);
			}

			if (keyCode == SPACE_KEY)
			{
				EventSystem::getInstance()->fireEvent(SPACE_EVENT);
			}

			//NEW KEYS

			if (keyCode == W_KEY)
			{
				EventSystem::getInstance()->fireEvent(W_KEY_EVENT);
			}

			if (keyCode == A_KEY)
			{
				EventSystem::getInstance()->fireEvent(A_KEY_EVENT);
			}

			if (keyCode == D_KEY)
			{
				EventSystem::getInstance()->fireEvent(D_KEY_EVENT);
			}

			//---------ARROWS------------
			if (keyCode == UP_ARROW)
			{
				EventSystem::getInstance()->fireEvent(UP_ARROW_EVENT);
			}

			if (keyCode == DOWN_ARROW)
			{
				EventSystem::getInstance()->fireEvent(DOWN_ARROW_EVENT);
			}

			if (keyCode == LEFT_ARROW)
			{
				EventSystem::getInstance()->fireEvent(LEFT_ARROW_EVENT);
			}

			if (keyCode == RIGHT_ARROW)
			{
				EventSystem::getInstance()->fireEvent(RIGHT_ARROW_EVENT);
			}

			//------SPECIAL ARROWS----------
			if (keyCode == UP_RIGHT_ARROW)
			{
				EventSystem::getInstance()->fireEvent(UP_RIGHT_EVENT);
			}

			if (keyCode == UP_LEFT_ARROW)
			{
				EventSystem::getInstance()->fireEvent(UP_LEFT_EVENT);
			}

			if (keyCode == DOWN_RIGHT_ARROW)
			{
				EventSystem::getInstance()->fireEvent(DOWN_RIGHT_EVENT);
			}

			if (keyCode == DOWN_LEFT_ARROW)
			{
				EventSystem::getInstance()->fireEvent(DOWN_LEFT_EVENT);
			}

			keyCodes.pop_back();

		}
		else
		{
			if (keyCode != mPreviousKeyboardDown && keyCode == F_KEY)
			{
				EventSystem::getInstance()->fireEvent(F_KEY_EVENT);
			}

			if (keyCode != mPreviousKeyboardDown && keyCode == S_KEY)
			{
				EventSystem::getInstance()->fireEvent(S_KEY_EVENT);
			}

			if (keyCode != mPreviousKeyboardDown && keyCode == ESC_KEY)
			{
				EventSystem::getInstance()->fireEvent(ESCAPE_EVENT);
			}

			if (keyCode != mPreviousKeyboardDown && keyCode == ENT_KEY)
			{
				EventSystem::getInstance()->fireEvent(ENTER_EVENT);
			}

			if (keyCode != mPreviousKeyboardDown && keyCode == SPACE_KEY)
			{
				EventSystem::getInstance()->fireEvent(SPACE_EVENT);
			}

			//NEW KEYS

			if (keyCode != mPreviousKeyboardDown && keyCode == W_KEY)
			{
				EventSystem::getInstance()->fireEvent(W_KEY_EVENT);
			}

			if (keyCode != mPreviousKeyboardDown && keyCode == A_KEY)
			{
				EventSystem::getInstance()->fireEvent(A_KEY_EVENT);
			}

			if (keyCode != mPreviousKeyboardDown && keyCode == D_KEY)
			{
				EventSystem::getInstance()->fireEvent(D_KEY_EVENT);
			}

			//---------ARROWS------------
			if (keyCode != mPreviousKeyboardDown && keyCode == UP_ARROW)
			{
				EventSystem::getInstance()->fireEvent(UP_ARROW_EVENT);
			}

			if (keyCode != mPreviousKeyboardDown && keyCode == DOWN_ARROW)
			{
				EventSystem::getInstance()->fireEvent(DOWN_ARROW_EVENT);
			}

			if (keyCode != mPreviousKeyboardDown && keyCode == LEFT_ARROW)
			{
				EventSystem::getInstance()->fireEvent(LEFT_ARROW_EVENT);
			}

			if (keyCode != mPreviousKeyboardDown && keyCode == RIGHT_ARROW)
			{
				EventSystem::getInstance()->fireEvent(RIGHT_ARROW_EVENT);
			}

			//------SPECIAL ARROWS----------
			if (keyCode != mPreviousKeyboardDown && keyCode == UP_RIGHT_ARROW)
			{
				EventSystem::getInstance()->fireEvent(UP_RIGHT_EVENT);
			}

			if (keyCode != mPreviousKeyboardDown && keyCode == UP_LEFT_ARROW)
			{
				EventSystem::getInstance()->fireEvent(UP_LEFT_EVENT);
			}

			if (keyCode != mPreviousKeyboardDown && keyCode == DOWN_RIGHT_ARROW)
			{
				EventSystem::getInstance()->fireEvent(DOWN_RIGHT_EVENT);
			}

			if (keyCode != mPreviousKeyboardDown && keyCode == DOWN_LEFT_ARROW)
			{
				EventSystem::getInstance()->fireEvent(DOWN_LEFT_EVENT);
			}

			mPreviousKeyboardDown = keyCode;

			keyCodes.pop_back();

		}


		

	}




	/*
	if (getMouseState() != mPreviousMouseState && getMouseState() == L_MOUSE)
	{
		EventSystem::getInstance()->fireEvent(MoveEvent(Vector2D(getMousePosition(window).getX(), getMousePosition(window).getY())));
		EventSystem::getInstance()->fireEvent(PRIMARY_MOUSE_EVENT);
	}

	if (getMouseState() != mPreviousMouseState && getMouseState() == R_MOUSE)
	{
		EventSystem::getInstance()->fireEvent(MoveEvent(Vector2D(getMousePosition(window).getX(),getMousePosition(window).getY())));
		EventSystem::getInstance()->fireEvent(SECONDARY_MOUSE_EVENT);
	}
	*/

	

	//this is for position of mouse, NOT EXACTLY SURE HOW TO GET THE POSITION OUT OF THIS



	
	mPreviousMouseState = getMouseState();

	mPreviousMousePos.setX(getMousePosition(window).getX());
	mPreviousMousePos.setY(getMousePosition(window).getY());
}


//I know checking with a for loop is inefficient, but this way we get every key possibly pressed
vector<int> InputSystem::getKeyState()
{
	//al_get_keyboard_state(&mKeyboardState);

	//int KC = -1;	If this is pressed this remains the same

	vector<int> KC;
	//KC.push_back(-1);

	/*
	for (int keyCode = 0; keyCode < sf::Keyboard::KeyCount; keyCode++)
	{
		

		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keyCode))
		{
			KC.push_back(keyCode);
		}
	}
	*/

	//WASD / ARROWS
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		KC.push_back(W_KEY);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		KC.push_back(S_KEY);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		KC.push_back(A_KEY);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		KC.push_back(D_KEY);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		KC.push_back(UP_ARROW);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		KC.push_back(DOWN_ARROW);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		KC.push_back(LEFT_ARROW);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		KC.push_back(RIGHT_ARROW);
	}

	//special diagonals
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		KC.push_back(UP_LEFT_ARROW);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		KC.push_back(UP_RIGHT_ARROW);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		KC.push_back(DOWN_LEFT_ARROW);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		KC.push_back(DOWN_RIGHT_ARROW);
	}

	//Misc
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		KC.push_back(F_KEY);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		KC.push_back(ENT_KEY);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		KC.push_back(ESC_KEY);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		KC.push_back(SPACE_KEY);
	}

	//this is for the PressedWithReleaseChoice to work

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::F) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		KC.push_back(-1);
	}

	return KC;

}

Vector2D InputSystem::getMousePosition(sf::RenderWindow* window)
{
	//returns vector2D of mouse pos

	//al_get_mouse_state(&mMouseState);

	//Vector2D mousePos(mMouseState.x, mMouseState.y);

	//find a way to do getPosition(window)
	Vector2D mousePos(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);

	//cout << "X: " << sf::Mouse::getPosition(*window).x << "Y:  " << sf::Mouse::getPosition(*window).y << endl;

	return mousePos;
}

int InputSystem::getMouseState()
{
	//al_get_mouse_state(&mMouseState);

	//I had to look up the button numbers, there are no consts made

	/*
	//primary button is one
	if (al_mouse_button_down(&mMouseState, 1))
	{
		return 1;
	}
	else if (al_mouse_button_down(&mMouseState, 2))	 //secondary button is two
	{
		return 2;
	}
	else if (al_mouse_button_down(&mMouseState, 4))		//MM click is four
	{
		return 4;
	}
	else
	{
		return -1; //nothing pressed
	}
	*/

	int MB = -1;

	//there are a max of six mouse buttons in SFML
	for (int i = 0; i < 6; i++)
	{
		if (sf::Mouse::isButtonPressed((sf::Mouse::Button)i))
		{
			MB = i;
		}
	}

	return MB;
}